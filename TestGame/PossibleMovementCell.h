#pragma once
#include "Figure.h"
#include <SFML/Graphics.hpp>

class PossibleMovementCell : public Figure
{
public:
	PossibleMovementCell(Texture& NewTexture);
	~PossibleMovementCell() override;
	void DrawFigure(RenderWindow& window) override;
};

