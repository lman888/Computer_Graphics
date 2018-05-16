#include "Application3D.h"

int main()
{

	Application3D* theApp = new Application3D();

	if (theApp->startup() == true)
	{
		while (theApp->update() == true)
		
			theApp->draw();
			//theApp->shutdown();
		
	}

	delete theApp;

	return 0;
	/*///Memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "START OF PROGRAM" << std::endl;

	if (glfwInit() == false)	///if the initialiser is false
	{
		return -1;
	}

	/// The rest of our code goes in here

	GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL Window", 
										  nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n");

	glClearColor(0.25f, 0.25f, 0.25f, 1);	///Sets the screen color
	glEnable(GL_DEPTH_TEST);				///Enables the depth buffer

	aie::Gizmos::create(10000, 10000, 10000, 10000);

	///The GLM lookAt() Method builds a view transform, which is an inverseion of a transform that has a translation of (10,10,10)
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.025f,
											16 / 9.f, 0.1f, 1000.f);



	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
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
		glfwPollEvents();			///Makes sure all operating system messages and events are handled correctly
	}


	aie::Gizmos::destroy();		///Removes all shapes and lines
	glfwDestroyWindow(window);
	glfwTerminate();*/
}