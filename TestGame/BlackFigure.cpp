#include "BlackFigure.h"
#include <iostream>

BlackFigure::BlackFigure(Texture& NewTexture) : Figure(NewTexture)
{
	std::cout << "Black figure created\n";
	Name = FigureName::BLACK;
}

BlackFigure::~BlackFigure()
{
	std::cout << "BlackFigure deleted\n";
}
