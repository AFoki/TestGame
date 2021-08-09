#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Figure
{
private:
    Texture FigureTexture;
    Sprite FigureSprite;
    Sprite ActiveSprite;
    Vector2f SpriteOffset;
    bool bIsActive{ false };
    int XPosition;
    int YPosition;
    
protected:
    Figure(const Texture& NewTexture);
public:
    virtual ~Figure();
    void SelectFigure();
    void UnselectFigure();
    Texture GetTexture();
    Sprite GetSprite();
    void SetStartPosition(int X, int Y);
    void DrawFigure(RenderWindow& window);
    bool CheckPosition(int X, int Y);
    bool GetIsActive();
};

