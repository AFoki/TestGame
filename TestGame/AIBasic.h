#pragma once
#include "Types.h"
#include "Desk.h"
#include <array>
#include <SFML/Graphics.hpp>

using namespace sf;

class AIBasic
{
private:
	Desk* MyDesk;
	std::array<std::array<Cell*, 8>, 8>* Field;
	std::array<Figure*, 18>* FiguresArray;

public:
	AIBasic(Desk* GameDesk);
	void AIMove();

private:
	int CalculateWorthOfDesk(Figure* MovableFigure, const Vector2i& NewCoordinates);
	int CheckMove(Figure* FigureToCheck, Vector2i& FigurePosition, int DisplacementX, int DisplacementY, int& CurrentWorth, std::map<int, std::pair<Figure*, Vector2i>>& Statistic);

};

