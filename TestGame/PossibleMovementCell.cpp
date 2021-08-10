#include "PossibleMovementCell.h"
#include <iostream>

PossibleMovementCell::PossibleMovementCell(Texture& NewTexture) : Figure(NewTexture)
{
	std::cout << "Possible move created\n";
	Name = FigureName::POSSIBLETOMOVE;
}

PossibleMovementCell::~PossibleMovementCell()
{
	std::cout << "Possible move destroyed\n";
}

void PossibleMovementCell::DrawFigure(RenderWindow& window)
{
	Vector2i FigurePosition = GetPosition();
	Sprite TempToDraw = GetSprite();
	SpriteOffset.x = 100 + 10 * (static_cast<float>(FigurePosition.x) + 1) + 90 * static_cast<float>(FigurePosition.x);
	SpriteOffset.y = 100 + 10 * (static_cast<float>(FigurePosition.y) + 1) + 90 * static_cast<float>(FigurePosition.y);
	TempToDraw.move(SpriteOffset);
	window.draw(TempToDraw);

}
