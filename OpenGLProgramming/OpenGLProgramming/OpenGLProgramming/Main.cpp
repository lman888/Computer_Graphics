#include "Application3D.h"

int main()
{
	///Memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto theApp = new Application3D();

	std::cout << "START OF PROGRAM" << std::endl;

	theApp->initialise(720, 1280, "Hello", false);

	if (theApp->startup() == true)
	{
		while (theApp->update() == true)
		{
			theApp->draw();
		}

			theApp->shutdown();
		}
	else
	{
		delete theApp;
	}

	delete theApp;

	return 0;
}