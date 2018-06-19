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
	m_view = glm::lookAt(glm::vec3(15), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.25f,
		m_windowWidth / (float)m_windowHeight, 0.1f, 1000.f);


	//Loads the Frag and Vert textures from file
	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/phong.frag");

	/*m_shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/simple.frag");*/

	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
		"./textures/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./textures/textured.frag");

	m_normalShader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/normalmap.vert");
	m_normalShader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shaders/normalmap.frag");

	//Checks if it can link the Shader
	//if (m_shader.link() == false)
	//{
	//	printf("Shader Error: %s/n", m_shader.getLastError());
	//}
	if (m_texturedShader.link() == false)
	{
		printf("Texture Error: %s/n", m_texturedShader.getLastError());
	}
	if (m_phongShader.link() == false)
	{
		printf("Texture Error: %s/n", m_phongShader.getLastError());
	}
	if (m_normalShader.link() == false)
	{
		printf("Normal Error: %s/n", m_normalShader.getLastError());
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
	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("SoulSpear Mesh Error!\n");
	}

	//-------------------------RENDER TARGET DATA-------------------------//
	//Checks if Render Taget has been initialised
	/*if (m_renderTarget.initialise(1, getWindowH(), getWindowW()) == false)
	{
		printf("Render Target Error!\n");
		return false;
	}*/
	//-------------------------RENDER TARGET DATA-------------------------//

	m_quadMesh.initialiseQuad();


	//Sets the lights colour
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	m_secondaryLight.diffuse = { 1.38f, 0.43f, 2.26f };
	m_secondaryLight.specular = { 1, 1, 0 };
	
	//We create the spot light and direction light
	m_spotLight.position = glm::vec4(-4, 0, 10, 1);
	m_spotLight.intensities = glm::vec3(2, 2, 2);
	m_spotLight.attenuation = 0.1f;
	m_spotLight.ambientCoefficient = 0.0f;
	m_spotLight.coneAngle = 15.0f;
	m_spotLight.coneDirection = glm::vec3(0, 0, -1);

	m_directionLight.position = glm::vec4(1, 0.8, 0.6, 0);
	m_directionLight.intensities = glm::vec3(0.4, 0.3, 0.1);
	m_directionLight.ambientCoefficient = 0.06f;

	//we push the lights into the array
	gLights.push_back(m_spotLight);
	gLights.push_back(m_directionLight);

	//Bunnys size
	m_bunnyTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0,	1
	};
	//Bunnys Position
	m_bunnyTransform[3] = glm::vec4{ -1, 1, 1, 1 };

	//Dragons size
	/*m_dragonTransform =
	{
		0.5f, 0, 0, 0,
		0, 0.5f, 0, 0,
		0, 0, 0.5f, 0,
		0, 0, 0, 1.0f
	};*/

	//Spears Size
	m_spearTransform =
	{
		1.0f, 0, 0, 0,
		0, 1.0f, 0, 0,
		0, 0, 1.0f, 0,
		0, 0, 0, 1.0f
	};
	//Spears Position
	m_spearTransform[3] = glm::vec4{ 5, 5, 5, 1 };

	//Quads size
	m_quadTransform =
	{
		10.0f, 0, 0, 0,
		0, 10.0f, 0, 0,
		0, 0, 10.0f, 0,
		0, 0, 0, 1
	};
	//m_quadTransform[3] = glm::vec4{ 1, 1, 1, 1 };


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

	m_secondaryLight.direction = glm::normalize(glm::vec3(glm::cos(time * 2),
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

	//-------------------------RENDER TARGET DATA-------------------------//
	//Bind our Render Target
	//m_renderTarget.bind();
	//clearScreen();
	//-------------------------RENDER TARGET DATA-------------------------//

	//Binds the shaders
	//m_shader.bind();

	m_texturedShader.bind();

	auto pvm = m_projection * m_view * m_quadTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	m_texturedShader.bindUniform("diffuseTexture", 0);

	//Binds the grid texture to a specified location
	m_gridTexture.bind(0);

	m_quadMesh.draw();						//Draws the Quad Mesh

	//----------------------------------------BUNNYDRAW----------------------------------------//
	m_phongShader.bind();	
	
	//Bind list
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_secondaryLight.diffuse);
	m_phongShader.bindUniform("Is", m_secondaryLight.specular);
	m_phongShader.bindUniform("lightDirection", m_secondaryLight.direction);
	m_phongShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_view)[3]));

	//Bind transform
	pvm = m_projection * m_view * m_bunnyTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	
	//Binds transform for lighting
	m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);
	m_phongShader.bindUniform("NormalMatrix", 
		glm::inverseTranspose(glm::mat3(m_bunnyTransform)));

	m_bunnyMesh.draw();						//Draws the Bunny Mesh
	//----------------------------------------BUNNYDRAW----------------------------------------//


	//----------------------------------------SPEARDRAW----------------------------------------//
	m_normalShader.bind();

	//Normal Shader Binding
	m_normalShader.bindUniform("Ia", m_ambientLight);
	m_normalShader.bindUniform("Id", m_light.diffuse);
	m_normalShader.bindUniform("Is", m_light.specular);
	m_normalShader.bindUniform("lightDirection", m_light.direction);
	m_normalShader.bindUniform("cameraPosition", glm::vec3(glm::inverse(m_view)[3]));

	pvm = m_projection * m_view * m_spearTransform;
	m_normalShader.bindUniform("ProjectionViewModel", pvm);
	m_normalShader.bindUniform("ModelMatrix", m_spearTransform);
	m_normalShader.bindUniform("NormalMatrix",
		glm::inverseTranspose(glm::mat3(m_spearTransform)));

	//Binds the uniform for each light in the array
	m_normalShader.bindUniform("numLights", (int)gLights.size());

	for (int i = 0; i < gLights.size(); i++)
	{
		BindLightUniform(&m_normalShader, "position", i, gLights[i].position);
		BindLightUniform(&m_normalShader, "intensities", i, gLights[i].intensities);
		BindLightUniform(&m_normalShader, "attenuation", i, gLights[i].attenuation);
		BindLightUniform(&m_normalShader, "ambientCoefficient", i, gLights[i].ambientCoefficient);
		BindLightUniform(&m_normalShader, "coneAngle", i, gLights[i].coneAngle);
		BindLightUniform(&m_normalShader, "coneDirection", i, gLights[i].coneDirection);
	}

	m_spearMesh.draw();						//Draws the Spear Mesh

	//----------------------------------------SPEARDRAW----------------------------------------//


	//m_dragonMesh.draw();					//Draws the Dragon Mesh

	//-------------------------RENDER TARGET DATA-------------------------//
	//m_renderTarget.unbind();
	//clearScreen();
	//m_texturedShader.bind();
	//pvm = m_projection * m_view * m_quadTransform;
	//m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	//m_texturedShader.bindUniform("diffuseTexture", 0);
	//m_renderTarget.getTarget(0).bind(0);
	//m_quadMesh.draw();						//Draws the Quad Mesh
	//-------------------------RENDER TARGET DATA-------------------------//

	aie::Gizmos::draw(m_projection * m_view);						///Draw 3D gizmos
	aie::Gizmos::draw2D((float)getWindowW(), (float)getWindowH());	///Draw 2D Gizmos using orthogonal projection matrix

	glfwSwapBuffers(m_window);					///This updates the monitors display by swapping the rendered back buffer.
}

void Application3D::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
