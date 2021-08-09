#include "Figure.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Figure::Figure(const Texture& NewTexture) : FigureTexture{NewTexture}
{
	FigureSprite.setTexture(FigureTexture);
	ActiveSprite = FigureSprite;
	ActiveSprite.setColor(Color::Red);
	std::cout << "Base figure created\t";
}

void Figure::SelectFigure()
{
	bIsActive = true;
}

void Figure::UnselectFigure()
{
	bIsActive = false;
}

Figure::~Figure()
{
	std::cout << "Base figure deleted\t";
}

Texture Figure::GetTexture()
{
	return FigureTexture;
}

Sprite Figure::GetSprite()
{
	return bIsActive ? ActiveSprite : FigureSprite;
}

void Figure::SetStartPosition(int X, int Y)
{
	XPosition = X;
	YPosition = Y;
}

void Figure::DrawFigure(RenderWindow& window)
{
	Sprite Temp = bIsActive ? ActiveSprite : FigureSprite;
	SpriteOffset.x = 100 + 10 * (XPosition + 1) + 90 * XPosition;
	SpriteOffset.y = 100 + 10 * (YPosition + 1) + 90 * YPosition;
	Temp.move(SpriteOffset);
	window.draw(Temp);
}

bool Figure::CheckPosition(int X, int Y)
{
	return XPosition == X && YPosition == Y;
}

bool Figure::GetIsActive()
{
	return bIsActive;
}
