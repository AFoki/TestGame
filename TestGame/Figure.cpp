#include "Figure.h"
#include <SFML/Graphics.hpp>
#include "Types.h"
#include <iostream>

Figure::Figure(const Texture& NewTexture) : FigureTexture{NewTexture}, Name{FigureName::BASIC}
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

Texture Figure::GetTexture() const
{
	return FigureTexture;
}

Sprite Figure::GetSprite() const
{
	return bIsActive ? ActiveSprite : FigureSprite;
}

void Figure::SetPosition(int X, int Y)
{
	XPosition = X;
	YPosition = Y;
}

void Figure::SetPosition(const Vector2i& NewPosition)
{
	XPosition = NewPosition.x;
	YPosition = NewPosition.y;
}

void Figure::DrawFigure(RenderWindow& window)
{
	Sprite Temp = bIsActive ? ActiveSprite : FigureSprite;
	SpriteOffset.x = 100 + 10 * (static_cast<float>(XPosition) + 1) + 90 * XPosition;
	SpriteOffset.y = 100 + 10 * (static_cast<float>(YPosition) + 1) + 90 * YPosition;
	Temp.move(SpriteOffset);
	window.draw(Temp);
}

bool Figure::CheckPosition(int X, int Y) const
{
	return XPosition == X && YPosition == Y;
}

bool Figure::GetIsActive() const
{
	return bIsActive;
}

FigureName Figure::GetName() const
{
	return Name;
}

Vector2i Figure::GetPosition() const
{
	return Vector2i(XPosition, YPosition);
}
