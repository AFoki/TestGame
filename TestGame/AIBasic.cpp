#include "AIBasic.h"
#include "Figure.h"
#include "PossibleMovementCell.h"

AIBasic::AIBasic(Desk* GameDesk)
{
	MyDesk = GameDesk;
	Field = GameDesk->GetField();
	FiguresArray = GameDesk->GetFiguresArray();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i > j)
			{
				Field->at(i)[j]->CellWeight = 0 - (4 * i + j);
			}
			else
			{
				if (i == j)
				{
					Field->at(i)[j]->CellWeight = 0 - (3 * i + 3 * j);
				}
				else
				{
					Field->at(i)[j]->CellWeight = 0 - (i + 4 * j);
				}
			}

		}
	}
	Field->at(0)[0]->CellWeight = 100;
	Field->at(0)[1]->CellWeight = 90;
	Field->at(1)[0]->CellWeight = 90;
	Field->at(1)[1]->CellWeight = 80;
	Field->at(0)[2]->CellWeight = 80;
	Field->at(2)[0]->CellWeight = 80;
	Field->at(1)[2]->CellWeight = 70;
	Field->at(2)[1]->CellWeight = 70;
	Field->at(2)[2]->CellWeight = 60;

	Field->at(7)[7]->CellWeight = -100;
	Field->at(6)[7]->CellWeight = -90;
	Field->at(7)[6]->CellWeight = -90;
	Field->at(5)[7]->CellWeight = -80;
	Field->at(6)[6]->CellWeight = -80;
	Field->at(7)[5]->CellWeight = -80;
	Field->at(5)[6]->CellWeight = -70;
	Field->at(6)[5]->CellWeight = -70;
	Field->at(5)[5]->CellWeight = -60;
}

void AIBasic::AIMove()
{
	int WorthDesk;
	Vector2i Position;
	std::map<int, std::pair<Figure*, Vector2i>> MovesVithWeight;

	for (int i = 9; i < 18; i++)
	{
		Position = FiguresArray->at(i)->GetPosition();

		if (Position.x > 0 && Field->at(Position.y)[Position.x - 1]->FigureInCell == nullptr)
		{
			CheckMove(FiguresArray->at(i), Position, -1, 0, WorthDesk, MovesVithWeight);
		}
		if (Position.x < 7 && Field->at(Position.y)[Position.x + 1]->FigureInCell == nullptr)
		{
			CheckMove(FiguresArray->at(i), Position, 1, 0, WorthDesk, MovesVithWeight);
		}
		if (Position.y > 0 && Field->at(Position.y - 1)[Position.x]->FigureInCell == nullptr)
		{
			CheckMove(FiguresArray->at(i), Position, 0, -1, WorthDesk, MovesVithWeight);
		}
		if (Position.y < 7 && Field->at(Position.y + 1)[Position.x]->FigureInCell == nullptr)
		{
			CheckMove(FiguresArray->at(i), Position, 0, 1, WorthDesk, MovesVithWeight);
		}
	}
	std::pair<Figure*, Vector2i> BestMove = MovesVithWeight.at(WorthDesk);
	MyDesk->FigureMove(BestMove.first, BestMove.second);
}


int AIBasic::CalculateWorthOfDesk(Figure* MovableFigure, const Vector2i& NewCoordinates)
{
	int Worth = 0;
	int NumberOfMovesToNeighbour;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Field->at(i)[j]->FigureInCell && Field->at(i)[j]->FigureInCell->GetName() == FigureName::BLACK)
			{
				if (Field->at(i)[j]->FigureInCell == MovableFigure)
				{
					Worth += Field->at(NewCoordinates.y)[NewCoordinates.x]->CellWeight;
					// Проверка на возможность движения соседних белых фигур
					if (NewCoordinates.x < 7 &&
						Field->at(NewCoordinates.y)[NewCoordinates.x + 1]->FigureInCell &&
						Field->at(NewCoordinates.y)[NewCoordinates.x + 1]->FigureInCell->GetName() == FigureName::WHITE &&
						MyDesk->CalculatePossibleMove(Field->at(NewCoordinates.y)[NewCoordinates.x + 1]->FigureInCell, NumberOfMovesToNeighbour) == 1)
					{
						return Worth = -1000;
					}
					if (NewCoordinates.x > 0 &&
						Field->at(NewCoordinates.y)[NewCoordinates.x - 1]->FigureInCell &&
						Field->at(NewCoordinates.y)[NewCoordinates.x - 1]->FigureInCell->GetName() == FigureName::WHITE &&
						MyDesk->CalculatePossibleMove(Field->at(NewCoordinates.y)[NewCoordinates.x - 1]->FigureInCell, NumberOfMovesToNeighbour) == 1)
					{
						return Worth = -1000;
					}
					if (NewCoordinates.y < 7 &&
						Field->at(NewCoordinates.y + 1)[NewCoordinates.x]->FigureInCell &&
						Field->at(NewCoordinates.y + 1)[NewCoordinates.x]->FigureInCell->GetName() == FigureName::WHITE &&
						MyDesk->CalculatePossibleMove(Field->at(NewCoordinates.y + 1)[NewCoordinates.x]->FigureInCell, NumberOfMovesToNeighbour) == 1)
					{
						return Worth = -1000;
					}
					if (NewCoordinates.y > 0 &&
						Field->at(NewCoordinates.y - 1)[NewCoordinates.x]->FigureInCell &&
						Field->at(NewCoordinates.y - 1)[NewCoordinates.x]->FigureInCell->GetName() == FigureName::WHITE &&
						MyDesk->CalculatePossibleMove(Field->at(NewCoordinates.y - 1)[NewCoordinates.x]->FigureInCell, NumberOfMovesToNeighbour) == 1)
					{
						return Worth = -1000;
					}
				}
				else
				{
					Worth += Field->at(i)[j]->CellWeight;
				}
			}
		}
	}
	return Worth;
}

int AIBasic::CheckMove(Figure* FigureToCheck, Vector2i& FigurePosition, int DisplacementX, int DisplacementY, int& CurrentWorth, std::map<int, std::pair<Figure*, Vector2i>>& Statistic)
{
	std::pair<Figure*, Vector2i> RawMove = { FigureToCheck, { FigurePosition.x + DisplacementX, FigurePosition.y + DisplacementY } };
	int NewWorth = CalculateWorthOfDesk(RawMove.first, RawMove.second);
	Statistic.insert(std::pair<int, std::pair<Figure*, Vector2i>> {NewWorth, RawMove});
	if (CurrentWorth < NewWorth) CurrentWorth = NewWorth;
	return NewWorth;
}
