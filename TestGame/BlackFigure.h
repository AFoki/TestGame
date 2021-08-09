#pragma once
#include "Figure.h"
class BlackFigure : public Figure
{
public:
	BlackFigure(Texture& NewTexture);
	~BlackFigure() override;
};

