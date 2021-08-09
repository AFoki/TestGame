#include "Desk.h"
#include "WhiteFigure.h"
#include "BlackFigure.h"


Desk::Desk(Texture& TExtureForWhite, Texture& TExtureForBlack)
{
	WhiteCellTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\WhiteCell.png");
	DarkCellTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\DarkCell.png");
	ActiveCellTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\PossibleCell.png");
	int IdInArray{ 0 };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Field[i][j].YPosition = i;
			Field[i][j].XPosition = j;
			if (i < 3 && j < 3)
			{
				Field[i][j].FigureInCell = new WhiteFigure(TExtureForWhite);
				Field[i][j].FigureInCell->SetStartPosition(j, i);
				FiguresArray[IdInArray++] = Field[i][j].FigureInCell;
			}
			if (i > 4 && j > 4)
			{
				Field[i][j].FigureInCell = new BlackFigure(TExtureForBlack);
				Field[i][j].FigureInCell->SetStartPosition(j, i);
				FiguresArray[IdInArray++] = Field[i][j].FigureInCell;
			}
		}
	}
}

Desk::~Desk()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete Field[i][j].FigureInCell;
		}
	}
}

void Desk::DrawDesk(RenderWindow& Window)
{
	//Sprite Temp;
	//float MoveX;
	//float MoveY;
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (Field[i][j].FigureInCell)
	//		{
	//			Temp = Field[i][j].FigureInCell->GetSprite();
	//			MoveX = 100 + 10 * (j + 1) + 90 * j;
	//			MoveY = 100 + 10 * (i + 1) + 90 * i;
	//			Temp.move(MoveX, MoveY);
	//			Window.draw(Temp);
	//		}
	//	}
	//}
	for (auto CurrentFigure : FiguresArray)
	{
		CurrentFigure->DrawFigure(Window);
	}
}

Figure* Desk::GetFigureInCoordinates(int X, int Y)
{
	for (auto CurrentFigure : FiguresArray)
	{
		if (CurrentFigure->CheckPosition(X, Y))
		{
			return CurrentFigure;
		}
	}
	return nullptr;
}
