#pragma once

class Figure;

enum class FigureName
{
    BASIC,
    WHITE,
    BLACK,
    POSSIBLETOMOVE
};
enum class GameStates
{
    GAME,
    WIN,
    LOSE,
    PLAYERMOVE,
    AIMOVE
};

struct Cell
{
    Figure* FigureInCell = nullptr;
    int CellWeight;
};
