#include "Application3D.h"



Application3D::Application3D()
{
	if (glfwInit() == false)	///if the initialiser is false
	{
		return;
	}

	///The rest of our code goes in here

	window = glfwCreateWindow(1280, 720, "OpenGL Window",
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

	aie::Gizmos::create(10000, 10000, 10000, 10000);

	///The GLM lookAt() Method builds a view transform, which is an inverseion of a transform that has a translation of (10,10,10)
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);
}


Application3D::~Application3D()
{
}

int Application3D::startup()
{
	return 0;
}

bool Application3D::update()
{
	if (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
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
	glfwDestroyWindow(window);
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

	aie::Gizmos::draw(projection * view);

	glfwSwapBuffers(window);	///This updates the monitors display by swapping the rendered back buffer.
}
