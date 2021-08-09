#include "BlackFigure.h"
#include <iostream>

BlackFigure::BlackFigure(Texture& NewTexture) : Figure(NewTexture)
{
	std::cout << "Black figure created\n";
}

BlackFigure::~BlackFigure()
{
	std::cout << "BlackFigure deleted\n";
}
