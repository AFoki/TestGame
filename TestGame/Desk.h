#pragma once
#include <array>
#include "Figure.h"
#include "Types.h"
#include <SFML/Graphics.hpp>

class Desk
{
private:
	Texture PossibleMoveTexture;
	GameStates *CurrentState;
	std::array<std::array<Cell*, 8>, 8> Field;
	std::array<Figure*, 18> FiguresArray;
	Figure* PossibleMovements[4];
	Figure* ActiveFigure = nullptr;
	Figure* FigureUnderMouse = nullptr;

public:
	Desk(Texture& TExtureForWhite, Texture& TExtureForBlack, GameStates& BasicState);
	~Desk();
	void DrawDesk(RenderWindow &Window);
	Figure* GetFigureInCoordinates(int X, int Y);
	void MouseClick(int X, int Y);
	void ClearSelection();
	void CheckWinLose();
	std::array<std::array<Cell*, 8>, 8>* GetField();
	std::array<Figure*, 18>* GetFiguresArray();
private:
	void CalculatePossibleMove(const Figure* FigureToCalculate);
public:
	int CalculatePossibleMove(const Figure* FigureToCalculate, int& NumberOfMoves);
private:
	void ClearPossibleMove();
public:
	void FigureMove(Figure* MovableFigure, const Vector2i &NewCoordinates);
	void FigureMove(std::pair<Figure*, const Vector2i&> NewPosition);
};

