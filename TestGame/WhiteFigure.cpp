#include "WhiteFigure.h"
#include "Types.h"
#include <iostream>

WhiteFigure::WhiteFigure(Texture& NewTexture) : Figure(NewTexture)
{
	std::cout << "White figure created\n";
	Name = FigureName::WHITE;
}

WhiteFigure::~WhiteFigure()
{
	std::cout << "White figure deleted\n";
}
