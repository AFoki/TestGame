#pragma once

#include <SFML/Graphics.hpp>
#include "Types.h"

using namespace sf;

class Figure
{
private:
    Texture FigureTexture;
    Sprite FigureSprite;
    Sprite ActiveSprite;
    bool bIsActive{ false };
    int XPosition;
    int YPosition;
protected:
    Figure(const Texture& NewTexture);
    FigureName Name;
    Vector2f SpriteOffset;
public:
    virtual ~Figure();
    void SelectFigure();
    void UnselectFigure();
    Texture GetTexture() const;
    Sprite GetSprite() const;
    void SetPosition(int X, int Y);
    void SetPosition(const Vector2i& NewPosition);
    virtual void DrawFigure(RenderWindow& window);
    bool CheckPosition(int X, int Y) const;
    bool GetIsActive() const;
    FigureName GetName() const;
    Vector2i GetPosition() const;
};

