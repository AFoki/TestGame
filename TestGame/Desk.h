#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>

class Desk
{
private:
	Texture PossibleMoveTexture;
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
	Figure* PossibleMovements[4];
	Figure* ActiveFigure = nullptr;
	Figure* FigureUnderMouse = nullptr;
public:
	Desk(Texture& TExtureForWhite, Texture& TExtureForBlack);
	~Desk();
	void DrawDesk(RenderWindow &Window);
	Figure* GetFigureInCoordinates(int X, int Y);
	void MouseClick(int X, int Y);
	void ClearSelection();
private:
	void CalculatePossibleMove(const Figure* FigureToCalculate);
	void ClearPossibleMove();
};

