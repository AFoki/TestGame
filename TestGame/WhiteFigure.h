#pragma once
#include "Figure.h"

class WhiteFigure : public Figure
{
public:
    WhiteFigure(Texture& NewTexture);
    ~WhiteFigure() override;
};

