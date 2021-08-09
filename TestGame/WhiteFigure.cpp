#include "WhiteFigure.h"
#include <iostream>

WhiteFigure::WhiteFigure(Texture& NewTexture) : Figure(NewTexture)
{
	std::cout << "White figure created\n";
}

WhiteFigure::~WhiteFigure()
{
	std::cout << "White figure deleted\n";
}
