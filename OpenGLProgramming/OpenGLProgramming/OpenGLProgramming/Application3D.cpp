#include "Application3D.h"



Application3D::Application3D()
{

}


Application3D::~Application3D()
{
}

bool Application3D::startup()
{
	//Initialize primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//The GLM lookAt() Method builds a view transform, which is an inverseion of a transform that has a translation of (10,10,10)
	m_view = glm::lookAt(glm::vec3(20), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f,
		m_windowWidth / (float)m_windowHeight, 0.1f, 1000.f);


	//Loads the Frag and Vert textures from file
	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/phong.frag");

	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./textures/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./textures/textured.frag");

	//Checks if it can link the Shader
	if (m_shader.link() == false)
	{
		printf("Shader Error: %s/n", m_shader.getLastError());
	}

	if (m_texturedShader.link() == false)
	{
		printf("Texture Error: %s/n", m_texturedShader.getLastError());
	}

	if (m_phongShader.link() == false)
	{
		printf("Texture Error: %s/n", m_phongShader.getLastError());
	}

	//Checks if it can load the Mesh
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		return false;
	}

	if (m_bunnyMesh.load("./stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
	}

	if (m_dragonMesh.load("./stanford/Dragon.obj") == false)
	{
		printf("Dragon Mesh Error!\n");
	}

	m_quadMesh.initialiseQuad();


	//Sets the lights colour
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	//Bunnys size
	//m_bunnyTransform =
	//{
	//	0.5f, 0, 0, 0,
	//	0, 0.5f, 0, 0,
	//	0, 0, 0.5f, 0,
	//	0, 0, 0, 1
	//};

	//Dragons size
	m_dragonTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0, 1.0f
	};

	///Quads size
	/*m_quadTransform =
	{
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};*/


	return true;
}

bool Application3D::initialise(int windowH, int windowW, std::string windowTitle, bool isFullScreen)
{
	if (glfwInit() == false)	///if the initialiser is false
	{
		return false;
	}

	auto monitor = glfwGetPrimaryMonitor();	///Sets the primary window to the monitor

	GLFWwindow* window = glfwCreateWindow(windowW, windowH, windowTitle.c_str(), (isFullScreen ? monitor : nullptr), nullptr);	///Creates the window

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	///Brings the screen to the front
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;									///return 3
	}

	///pushes in variables
	m_windowHeight = windowW;
	m_window = window;

	return true;
}

bool Application3D::update()
{
	//Query time since application started
	float time = glfwGetTime();

	//Rotates the light
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2),
		glm::sin(time * 2), 0));

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	///Informs OpenGL to wipe the back-buffer colors clean | Informs it to clear the distance to the closest pixels.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	if (glfwWindowShouldClose(m_window) == false &&
		glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glfwPollEvents();			///Makes sure all operating system messages and events are handled correctly
		return true;
	}
	else
	{
		return false;
	}
}

void Application3D::shutdown()
{
	aie::Gizmos::destroy();		///Removes all shapes and lines
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application3D::draw()
{
	aie::Gizmos::clear();
	aie::Gizmos::addTransform(glm::mat4(1));

	///Colours
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);


	aie::Gizmos::draw(m_projection * m_view);	///Draws the view of the camera

	///Draws the grid
	for (int i = 0; i < 21; i++)
	{
		///Draws the Lines
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	m_projection = glm::perspective(glm::pi<float>() * 0.25f,
		m_windowWidth / (float)m_windowHeight, 0.1f, 1000.0f);

	//Binds the shaders
	m_shader.bind();							
	m_texturedShader.bind();
	m_phongShader.bind();						

	//Binds texture location
	m_texturedShader.bindUniform("diffuseTexture", 0);

	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	auto pvm = m_projection * m_view * m_dragonTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	m_dragonMesh.draw();						//Draws the dragon Mesh

	m_phongShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_dragonTransform)));

	m_quadMesh.draw();						///Draws the Quad Mesh
	//m_bunnyMesh.draw();						///Draws the bunny Mesh



	aie::Gizmos::draw(m_projection * m_view);						///Draw 3D gizmos
	aie::Gizmos::draw2D((float)getWindowW(), (float)getWindowH());	///Draw 2D Gizmos using orthogonal projection matrix

	glfwSwapBuffers(m_window);					///This updates the monitors display by swapping the rendered back buffer.
}