#include "Application3D.h"



Application3D::Application3D()
{
	/*if (glfwInit() == false)	///if the initialiser is false
	{
		return;
	}

	///The rest of our code goes in here

	window = glfwCreateWindow(windowW, windowH, "OpenGL Window",
		nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return;
	}

	///Brings the screen to the front
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;									///return 3
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n");

	glClearColor(0.25f, 0.25f, 0.25f, 1);	///Sets the screen color
	glEnable(GL_DEPTH_TEST);				///Enables the depth buffer


	getWindowHeight = windowH;
	getWindowWidth = windowW;

	aie::Gizmos::create(10000, 10000, 10000, 10000);

	///The GLM lookAt() Method builds a view transform, which is an inverseion of a transform that has a translation of (10,10,10)
	view = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::pi<float>() * 0.25f,
								  getWindowW() / (float)getWindowH(), 0.1f, 1000.f);

	///Load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");

	///Load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s/n", m_shader.getLastError());
	}

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
	}

	bunnyTransform = 
	{
		1.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0, 1
	};*/

}


Application3D::~Application3D()
{
}

bool Application3D::startup()
{

	glClearColor(0.25f, 0.25f, 0.25f, 1);	///Sets the screen color
	//glEnable(GL_DEPTH_TEST);				///Enables the depth buffer

	///Initialize primitive counts
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	///The GLM lookAt() Method builds a view transform, which is an inverseion of a transform that has a translation of (10,10,10)
	m_view = glm::lookAt(glm::vec3(20), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f,
		m_windowWidth / (float)m_windowHeight, 0.1f, 1000.f);

	///Load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");

	///Load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s/n", m_shader.getLastError());
	}

	if (m_bunnyMesh.load("./stanford/Bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
	}

	m_quadMesh.initialiseQuad();

	m_bunnyTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0, 1
	};

	m_quadTransform =
	{
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};


	return true;
}

bool Application3D::initialise(int windowH, int windowW, std::string windowTitle, bool isFullScreen)
{
	if (glfwInit() == false)	///if the initialiser is false
	{
		return false;
	}

	auto monitor = glfwGetPrimaryMonitor();

	GLFWwindow* window = glfwCreateWindow(windowW, windowH, windowTitle.c_str(), (isFullScreen ? monitor : nullptr), nullptr);

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

	m_windowHeight = windowW;
	m_window = window;

	return true;
}

bool Application3D::update()
{
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
	///Informs OpenGL to wipe the back-buffer colors clean | Informs it to clear the distance to the closest pixels.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	aie::Gizmos::clear();

	aie::Gizmos::addTransform(glm::mat4(1));


	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	aie::Gizmos::draw(m_projection * m_view);

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

	m_shader.bind();

	auto pvm = m_projection * m_view * m_bunnyTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	m_quadMesh.draw();

	m_bunnyMesh.draw();

	///Draw 3D gizmos
	aie::Gizmos::draw(m_projection * m_view);

	///Draw 2D Gizmos using orthogonal projection matrix
	aie::Gizmos::draw2D((float)getWindowW(), (float)getWindowH());

	glfwSwapBuffers(m_window);	///This updates the monitors display by swapping the rendered back buffer.
}