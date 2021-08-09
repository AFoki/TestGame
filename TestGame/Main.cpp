#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "WhiteFigure.h"
#include "BlackFigure.h"
#include "Desk.h"
#include <iostream>

using namespace sf;

int main()
{
 // Preprocessor
    RenderWindow window(VideoMode(1000, 1000), "SFML works!");
    Texture DeskTexture;
    DeskTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\ChessDesk.png");
    Texture WhiteFigureTexture;
    WhiteFigureTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\FigureWhite.png");
    Texture BlackFigureTexture;
    BlackFigureTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\FigureBlack.png");
    Sprite DeskSprite(DeskTexture);
    DeskSprite.move(100.0f, 100.0f);
    Desk MyDesk(WhiteFigureTexture, BlackFigureTexture);
    Vector2i MousePosition;
    Figure* ActiveFigure = nullptr;
    Figure* FigureUnderMouse = nullptr;
    int ActiveFigurePositionX;
    int ActiveFigurePositionY;
// Processor
    while (window.isOpen())
    {
        MousePosition = Mouse::getPosition(window);
        //std::cout << MousePosition.x << '\t' << MousePosition.y << '\n';

 // Events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left)
                {
                    // Проверка на клики вне доски
                    if (MousePosition.x < 100 || MousePosition.y < 100 ||
                        MousePosition.x > 900 || MousePosition.y > 900) continue;

                    ActiveFigurePositionX = ceil((MousePosition.x - 100) / 100);
                    ActiveFigurePositionY = ceil((MousePosition.y - 100) / 100);

                    // Дебаг
                    std::cout << ActiveFigurePositionX << '\t' << ActiveFigurePositionY << '\n';

                    // Замена активной фигуры
                    FigureUnderMouse = MyDesk.GetFigureInCoordinates(ActiveFigurePositionX, ActiveFigurePositionY);
                    std::cout << FigureUnderMouse << '\n';
                    if (FigureUnderMouse)
                    {
                        if (ActiveFigure)
                        {
                            ActiveFigure->UnselectFigure();
                            ActiveFigure = FigureUnderMouse;
                            ActiveFigure->SelectFigure();
                        }
                        else
                        {
                            ActiveFigure = FigureUnderMouse;
                            ActiveFigure->SelectFigure();
                        }
                    }
                    
                }
                else
                {
                    if (ActiveFigure)
                    {
                        ActiveFigure->UnselectFigure();
                    }
                    ActiveFigure = nullptr;
                }
            }
        }

        

        window.clear(Color::Green);
        window.draw(DeskSprite);
        MyDesk.DrawDesk(window);
        window.display();
    }

// Memory cleaning

    return 0;
}