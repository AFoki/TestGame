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
		Figure* FigureInCell = nullptr;
		int CellWeght;
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
	void FigureMove(Figure* MovableFigure, const Vector2i &NewCoordinates);
	void InitAI();
	void AIMove();
	int CalculateWorthOfDesk(Figure* MovableFigure, const Vector2i& NewCoordinates);
	int CheckMove(Figure* FigureToCheck, Vector2i& FigurePosition, int X, int Y, int& CurrentWorth, std::map<int, std::pair<Figure*, Vector2i>>& Statistic);
};

