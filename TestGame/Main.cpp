#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "WhiteFigure.h"
#include "BlackFigure.h"
#include "Desk.h"
#include "Types.h"
#include <Windows.h>
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
    Vector2i MousePosition;
    GameStates CurrentState = GameStates::GAME;
    Text Message;
    Message.setCharacterSize(100);
    Message.setString("You Lose");
#pragma warning(suppress : 4996)
    Message.setColor(Color::Red);
    Desk MyDesk(WhiteFigureTexture, BlackFigureTexture, CurrentState);
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

                    MyDesk.MouseClick(MousePosition.x, MousePosition.y);
                }
                else
                {
                    MyDesk.ClearSelection();
                }
            }
            if (CurrentState == GameStates::LOSE)
            {
                std::cout << "\n\tYou Lose\n";
                Message.setString("You Lose");
                window.draw(Message);
                Sleep(5000);
                window.close();
            }
            if (CurrentState == GameStates::WIN)
            {
                std::cout << "\n\tYou Win\n";
                Message.setString("You Win");
                window.draw(Message);
                Sleep(5000);
                window.close();
            }
        }


        window.clear(Color::Green);
        window.draw(DeskSprite);
        MyDesk.DrawDesk(window);
        window.display();
    }

    return 0;
}