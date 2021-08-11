#include "Desk.h"
#include "WhiteFigure.h"
#include "BlackFigure.h"
#include "PossibleMovementCell.h"
#include "Types.h"
#include <functional>
#include <Windows.h>
#include <iostream>



Desk::Desk(Texture& TExtureForWhite, Texture& TExtureForBlack)
{
	PossibleMoveTexture.loadFromFile("C:\\Users\\Foki\\source\\repos\\TestGame\\TestGame\\src\\Texture\\PossibleCell.png");
	int IdInArray{ 0 };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
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
	InitAI();
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

	std::cout << FigureUnderMouse->GetPosition().x << '\t' <<  FigureUnderMouse->GetPosition().y <<'\n';

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
		//ActiveFigure->SetPosition(FigureUnderMouse->GetPosition());
		FigureMove(ActiveFigure, FigureUnderMouse->GetPosition());
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
	ClearPossibleMove();
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

void Desk::FigureMove(Figure* MovableFigure, const Vector2i& NewCoordinates)
{
	Vector2i StartCoordinates = MovableFigure->GetPosition();
	MovableFigure->SetPosition(NewCoordinates);
	Field[NewCoordinates.y][NewCoordinates.x].FigureInCell = MovableFigure;
	Field[StartCoordinates.y][StartCoordinates.x].FigureInCell = nullptr;
	if (MovableFigure->GetName() == FigureName::WHITE)
	{
		Sleep(1000);
		AIMove();
	}
}

void Desk::InitAI()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i > j)
			{
				Field[i][j].CellWeght = 0 - (4 * i + j);
			}
			else
			{
				if (i == j)
				{
					Field[i][j].CellWeght = 0 - (2 * i + 2 * j);
				}
				else 
				{
					Field[i][j].CellWeght = 0 - (i + 4 * j);
				}
			}
			
		}
	}
	Field[0][0].CellWeght = 100;
	Field[0][1].CellWeght = 90;
	Field[1][0].CellWeght = 90;
	Field[1][1].CellWeght = 80;
	Field[0][2].CellWeght = 80;
	Field[2][0].CellWeght = 80;
	Field[1][2].CellWeght = 70;
	Field[2][1].CellWeght = 70;
	Field[2][2].CellWeght = 60;
}

void Desk::AIMove()
{
	//Sleep(1000);
	int WorthDesk;
	Vector2i Position;
	std::map<int, std::pair<Figure*, Vector2i>> MovesVithWeight;

	for (int i = 0; i < 18; i++)
	{
		if (FiguresArray[i]->GetName() != FigureName::BLACK) continue;

		Position = FiguresArray[i]->GetPosition();

		if (Position.x > 0 && Field[Position.y][Position.x - 1].FigureInCell == nullptr)
		{
			CheckMove(FiguresArray[i], Position, -1, 0, WorthDesk, MovesVithWeight);
		}
		if (Position.x < 7 && Field[Position.y][Position.x + 1].FigureInCell == nullptr)
		{
			CheckMove(FiguresArray[i], Position, 1, 0, WorthDesk, MovesVithWeight);
		}
		if (Position.y > 0 && Field[Position.y - 1][Position.x].FigureInCell == nullptr)
		{
			CheckMove(FiguresArray[i], Position, 0, -1, WorthDesk, MovesVithWeight);
		}
		if (Position.y < 7 && Field[Position.y + 1][Position.x].FigureInCell == nullptr)
		{
			CheckMove(FiguresArray[i], Position, 0, 1, WorthDesk, MovesVithWeight);
		}
	}
	std::pair<Figure*, Vector2i> BestMove = MovesVithWeight.at(WorthDesk);
	FigureMove(BestMove.first, BestMove.second);
}

int Desk::CalculateWorthOfDesk(Figure* MovableFigure, const Vector2i& NewCoordinates)
{
	int Worth = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Field[i][j].FigureInCell && Field[i][j].FigureInCell->GetName() == FigureName::BLACK)
			{
				if (Field[i][j].FigureInCell == MovableFigure)
				{
					Worth += Field[NewCoordinates.y][NewCoordinates.x].CellWeght;
				}
				else
				{
					Worth += Field[i][j].CellWeght;
				}
			}
		}
	}
	return Worth;
}

int Desk::CheckMove(Figure* FigureToCheck, Vector2i& FigurePosition, int X, int Y, int& CurrentWorth, std::map<int, std::pair<Figure*, Vector2i>>& Statistic)
{
	std::pair<Figure*, Vector2i> RawMove = { FigureToCheck, { FigurePosition.x + X, FigurePosition.y + Y } };
	int NewWorth = CalculateWorthOfDesk(RawMove.first, RawMove.second);
	Statistic.insert(std::pair<int, std::pair<Figure*, Vector2i>> {NewWorth, RawMove});
	if (CurrentWorth < NewWorth) CurrentWorth = NewWorth;
	return NewWorth;
}


