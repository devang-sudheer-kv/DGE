#include <iostream>
#include <core/app.h>
#include "game.h"

int main()
{
	DGE::App app;
	app.init(600, 600, "Forest");
	std::cout << "Hello, World!" << std::endl;
	app.attachLayer((DGE::Layer*)new Game);
	app.run();
	app.terminate();
	return 0;
}