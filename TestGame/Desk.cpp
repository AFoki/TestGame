#include "Desk.h"
#include "WhiteFigure.h"
#include "BlackFigure.h"
#include "PossibleMovementCell.h"
#include "Types.h"
#include <iostream>



Desk::Desk(Texture& TExtureForWhite, Texture& TExtureForBlack)
{
	WhiteCellTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\WhiteCell.png");
	DarkCellTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\DarkCell.png");
	PossibleMoveTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\PossibleCell.png");
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
				Field[i][j].FigureInCell->SetPosition(j, i);
				FiguresArray[IdInArray++] = Field[i][j].FigureInCell;
			}
			if (i > 4 && j > 4)
			{
				Field[i][j].FigureInCell = new BlackFigure(TExtureForBlack);
				Field[i][j].FigureInCell->SetPosition(j, i);
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
	for (auto CurrentFigure : FiguresArray)
	{
		CurrentFigure->DrawFigure(Window);
	}
	for (auto CurrentMove : PossibleMovements)
	{
		if (CurrentMove)
		{
			CurrentMove->DrawFigure(Window);
		}
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
	for (auto CurrentMove : PossibleMovements)
	{
		if (CurrentMove && CurrentMove->CheckPosition(X, Y))
		{
			return CurrentMove;
		}
	}
	return nullptr;
}

void Desk::MouseClick(int X, int Y)
{
	int MouseX = static_cast<int>(ceil((X - 100) / 100));
	int MouseY = static_cast<int>(ceil((Y - 100) / 100));

	FigureUnderMouse = GetFigureInCoordinates(MouseX, MouseY);
	std::cout << FigureUnderMouse << '\n';
	if (!FigureUnderMouse) return;

	switch (FigureUnderMouse->GetName())
	{
	case FigureName::WHITE:
		ClearPossibleMove();
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
		CalculatePossibleMove(ActiveFigure);
		break;
	case FigureName::POSSIBLETOMOVE:
		ActiveFigure->SetPosition(FigureUnderMouse->GetPosition());
		ClearPossibleMove();
		ClearSelection();
		break;
	}
	
}

void Desk::ClearSelection()
{
	if (ActiveFigure)
	{
		ActiveFigure->UnselectFigure();
	}
	ActiveFigure = nullptr;

}

void Desk::CalculatePossibleMove(const Figure* FigureToCalculate)
{
	Vector2i FigurePosition{FigureToCalculate->GetPosition()};
	if (!GetFigureInCoordinates(FigurePosition.x - 1, FigurePosition.y) && FigurePosition.x > 0)
	{
		PossibleMovements[0] = new PossibleMovementCell(PossibleMoveTexture);
		PossibleMovements[0]->SetPosition(FigurePosition.x - 1, FigurePosition.y);
	}
	if (!GetFigureInCoordinates(FigurePosition.x + 1, FigurePosition.y) && FigurePosition.x < 7)
	{
		PossibleMovements[1] = new PossibleMovementCell(PossibleMoveTexture);
		PossibleMovements[1]->SetPosition(FigurePosition.x + 1, FigurePosition.y);
	}
	if (!GetFigureInCoordinates(FigurePosition.x, FigurePosition.y - 1) && FigurePosition.y > 0)
	{
		PossibleMovements[2] = new PossibleMovementCell(PossibleMoveTexture);
		PossibleMovements[2]->SetPosition(FigurePosition.x, FigurePosition.y - 1);
	}
	if (!GetFigureInCoordinates(FigurePosition.x, FigurePosition.y + 1) && FigurePosition.y < 7)
	{
		PossibleMovements[3] = new PossibleMovementCell(PossibleMoveTexture);
		PossibleMovements[3]->SetPosition(FigurePosition.x, FigurePosition.y + 1);
	}
}

void Desk::ClearPossibleMove()
{
	for (int i = 0; i < 4; i++)
	{
		if (PossibleMovements[i])
		{
			delete PossibleMovements[i];
			PossibleMovements[i] = nullptr;
		}
	}
}
