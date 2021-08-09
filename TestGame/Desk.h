#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>
struct DrawableFigure
{

};

class Desk
{
private:
	Texture WhiteCellTexture;
	Texture DarkCellTexture;
	Texture ActiveCellTexture;

	class Cell
	{
	public:
		int XPosition;
		int YPosition;
		Figure* FigureInCell = nullptr;
		bool bIsActive{ 0 };
	};
	Cell Field[8][8];
	Figure* FiguresArray[18];
public:
	Desk(Texture& TExtureForWhite, Texture& TExtureForBlack);
	~Desk();
	void DrawDesk(RenderWindow &Window);
	Figure* GetFigureInCoordinates(int X, int Y);
};

