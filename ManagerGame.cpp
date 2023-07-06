
#include "ManagerGame.h"

AManagerGame::AManagerGame() : Super()
{
 	
	PrimaryActorTick.bCanEverTick = true;
}

void AManagerGame::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	//���������� GameBoard
	if (world != nullptr)
	{
		gameBoard = world->SpawnActor<AGameBoard>(AGameBoard::StaticClass(), FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	}

	const int SIZE = gameBoard->GetSIZEGRID();

	previousBoard.SetNum(SIZE);
	for (int ROW = 0; ROW < SIZE; ROW++)
	{
		previousBoard[ROW].SetNum(SIZE);
	}

	//�������� ��������
	StartMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenu);
	GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOver);
	if (StartMenuWidget)
	{
		StartMenuWidget->AddToViewport();
		StartMenuScoreBlock = Cast<UTextBlock>(StartMenuWidget->GetWidgetFromName(TEXT("ScoreTextBlockWidget")));
		StartMenuUndoCountText = Cast<UTextBlock>(StartMenuWidget->GetWidgetFromName(TEXT("UndoCountText")));
	}
	if (GameOverWidget)
	{
		//���������� �������
		GameOverWidget->AddToViewport();
	}

	StartGame();
}

void AManagerGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AManagerGame::StartGame()
{
	//������� ������� �� �������, ���� ���� �� ����������	
	GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);

	hasMoved = false;
	undoCount = 3;
	currentScore = 0;
	previousScore = 0;

	UpdateScore(currentScore);
	UpdateUndoCount(undoCount);

	for (int ROW = 0; ROW < gameBoard->GetSIZEGRID(); ROW++)
	{
		for (int COLUMNUMN = 0; COLUMNUMN < gameBoard->GetSIZEGRID(); COLUMNUMN++)
		{
			gameBoard->GameBoardTile[ROW][COLUMNUMN]->SetValue(0);
		}
	}

	gameBoard->GenerateRandomValue();
	gameBoard->GenerateRandomValue();
	SavePreviousBoard();
}

void AManagerGame::EndGame()// ������� ��� ��������� ����, ������� ������� �������
{
	GameOverWidget->SetVisibility(ESlateVisibility::Visible);
}

void AManagerGame::PushUp()//�������� ������ �����
{
	SavePreviousBoard();

	hasMoved = false;
	const int SIZE = gameBoard->GetSIZEGRID();

	for (int COLUMN = 0; COLUMN < SIZE; COLUMN++)
	{
		bool hasMerged = false; // ����, �����������, ���� �� ��������� ������� � ������ ������� �� ������ ��������

		for (int ROW = 1; ROW < SIZE; ROW++)
		{
			if (gameBoard->GameBoardTile[ROW][COLUMN]->GetValue() != 0)
			{
				int newROW = ROW;
				while (newROW > 0 && gameBoard->GameBoardTile[newROW - 1][COLUMN]->GetValue() == 0)
				{
					gameBoard->GameBoardTile[newROW - 1][COLUMN]->SetValue(gameBoard->GameBoardTile[newROW][COLUMN]->GetValue());
					gameBoard->GameBoardTile[newROW][COLUMN]->SetValue(0);
					newROW--;
					hasMoved = true;
				}

				if (newROW > 0 && gameBoard->GameBoardTile[newROW - 1][COLUMN]->GetValue() == gameBoard->GameBoardTile[newROW][COLUMN]->GetValue() && !hasMerged && gameBoard->GameBoardTile[newROW][COLUMN]->GetValue() != 0)
				{
					gameBoard->GameBoardTile[newROW - 1][COLUMN]->SetValue(gameBoard->GameBoardTile[newROW - 1][COLUMN]->GetValue() * 2);

					currentScore += gameBoard->GameBoardTile[newROW - 1][COLUMN]->GetValue();

					gameBoard->GameBoardTile[newROW][COLUMN]->SetValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else
				{
					hasMerged = false; // ���������� ����, ���� �� ���� ��������
				}
			}
		}
	}

	IfHasMoved();
	CheckEndGame();
}

void AManagerGame::PushDown()//�������� ������ ����
{
	SavePreviousBoard();

	hasMoved = false;
	const int SIZE = gameBoard->GetSIZEGRID();
	for (int COLUMN = 0; COLUMN < SIZE; COLUMN++) 
	{
		bool hasMerged = false;
		for (int ROW = SIZE - 2; ROW >= 0; ROW--) 
		{
			if (gameBoard->GameBoardTile[ROW][COLUMN]->GetValue() != 0)
			{
				int newROW = ROW;
				while (newROW < SIZE - 1 && gameBoard->GameBoardTile[newROW + 1][COLUMN]->GetValue() == 0)
				{
					gameBoard->GameBoardTile[newROW + 1][COLUMN]->SetValue(gameBoard->GameBoardTile[newROW][COLUMN]->GetValue());
					gameBoard->GameBoardTile[newROW][COLUMN]->SetValue(0);
					newROW++;
					hasMoved = true;
				}
				if (newROW < SIZE - 1 && gameBoard->GameBoardTile[newROW + 1][COLUMN]->GetValue() == gameBoard->GameBoardTile[newROW][COLUMN]->GetValue() && !hasMerged && gameBoard->GameBoardTile[newROW][COLUMN]->GetValue() != 0) {
					gameBoard->GameBoardTile[newROW + 1][COLUMN]->SetValue(gameBoard->GameBoardTile[newROW + 1][COLUMN]->GetValue() * 2);

					currentScore += gameBoard->GameBoardTile[newROW + 1][COLUMN]->GetValue();

					gameBoard->GameBoardTile[newROW][COLUMN]->SetValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else
				{
					hasMerged = false; // ���������� ����, ���� �� ���� ��������
				}
			}
		}
	}

	IfHasMoved();
	CheckEndGame();
}

void AManagerGame::PushLeft()//�������� ������ �����
{
	SavePreviousBoard();

	hasMoved = false;
	const int SIZE = gameBoard->GetSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++)
	{
		bool hasMerged = false; // ��������� ���� ��� ����������� ������������ ��������
		for (int COLUMN = 1; COLUMN < SIZE; COLUMN++)
		{
			if (gameBoard->GameBoardTile[ROW][COLUMN]->GetValue() != 0)
			{
				int newCOLUMN = COLUMN;
				while (newCOLUMN > 0 && gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->GetValue() == 0) {
					gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->SetValue(gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue());
					gameBoard->GameBoardTile[ROW][newCOLUMN]->SetValue(0);
					newCOLUMN--;
					hasMoved = true;
				}
				if (newCOLUMN > 0 && gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->GetValue() == gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue() && !hasMerged  && gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue() != 0) {
					gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->SetValue(gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->GetValue() * 2);

					currentScore += gameBoard->GameBoardTile[ROW][newCOLUMN - 1]->GetValue();

					gameBoard->GameBoardTile[ROW][newCOLUMN]->SetValue(0);
					hasMerged = true; // ��������, ��� �������� ���� ���������
					hasMoved = true;
				}
				else
				{
					hasMerged = false; // ���������� ����, ���� �� ���� ��������
				}
			}
		}
		
	}

	IfHasMoved();
	CheckEndGame();
}

void AManagerGame::PushRight()// �������� ������ ������
{
	SavePreviousBoard();

	hasMoved = false;
	const int SIZE = gameBoard->GetSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++)
	{
		bool hasMerged = false;

		for (int COLUMN = SIZE - 2; COLUMN >= 0; COLUMN--)
		{
			if (gameBoard->GameBoardTile[ROW][COLUMN]->GetValue() != 0)
			{
				int newCOLUMN = COLUMN;
				while (newCOLUMN < SIZE - 1 && gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->GetValue() == 0)
				{
					gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->SetValue(gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue());
					gameBoard->GameBoardTile[ROW][newCOLUMN]->SetValue(0);
					newCOLUMN++;
					hasMoved = true;
				}

				if (newCOLUMN < SIZE - 1 && gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->GetValue() == gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue() && !hasMerged && gameBoard->GameBoardTile[ROW][newCOLUMN]->GetValue() != 0)
				{
					gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->SetValue(gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->GetValue() * 2);

					currentScore += gameBoard->GameBoardTile[ROW][newCOLUMN + 1]->GetValue();

					gameBoard->GameBoardTile[ROW][newCOLUMN]->SetValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else
				{
					hasMerged = false; // ���������� ����, ���� �� ���� ��������
				}
			}
		}
	}

	IfHasMoved();
	CheckEndGame();
}

void AManagerGame::CheckEndGame()// �������� �� ����� ����
{
	if (gameBoard->GetCountEmptyTile() == 0) // ������ �������� �� ����� ������
	{
		// ��������: ����� �� ���������� ������� � ��������� �������
		for (int ROW = 0; ROW < gameBoard->GetSIZEGRID(); ROW++)
		{
			for (int COLUMNUMN = 0; COLUMNUMN < gameBoard->GetSIZEGRID(); COLUMNUMN++)
			{
				ATile* currentTile = gameBoard->GameBoardTile[ROW][COLUMNUMN];
				if (CanCombineWithTile(currentTile, ROW - 1, COLUMNUMN) ||
					CanCombineWithTile(currentTile, ROW + 1, COLUMNUMN) ||
					CanCombineWithTile(currentTile, ROW, COLUMNUMN - 1) ||
					CanCombineWithTile(currentTile, ROW, COLUMNUMN + 1))
				{
					return;
				}
			}
		}
		EndGame();
	}
}

bool AManagerGame::CanCombineWithTile(ATile* const currentTile,int const &ROW,int const &COLUMNUMN)
{
	// ������� ���������� ����� �� ������ ������ ���� � �������� �� ������������� �������
	if (ROW < 0 || ROW >= gameBoard->GetSIZEGRID() || COLUMNUMN < 0 || COLUMNUMN >= gameBoard->GetSIZEGRID())
	{
		return false;
	}

	ATile* adjacentTile = gameBoard->GameBoardTile[ROW][COLUMNUMN];

	if (currentTile->GetValue() == adjacentTile->GetValue())
	{
		return true;
	}

	return false;
}

void AManagerGame::SavePreviousBoard()// ���������� ��������� ����������� ����
{
	previousScore = currentScore;
	int SIZE = gameBoard->GetSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++) 
	{
		for (int COLUMN = 0; COLUMN < SIZE; COLUMN++) 
		{
			previousBoard[ROW][COLUMN] = gameBoard->GameBoardTile[ROW][COLUMN]->GetValue();
		}
	}
}

void AManagerGame::IfHasMoved()
{
	UpdateScore(currentScore);
	if (hasMoved)
	{
		gameBoard->GenerateRandomValue();
	}
}

void AManagerGame::SetPreviousBoard() // ������ ������� �������� ����� �� ��������, ������� ���� �� ���������� ����
{	
	if (undoCount > 0 && hasMoved)
	{
		currentScore = previousScore;

		int SIZE = gameBoard->GetSIZEGRID();

		for (int ROW = 0; ROW < SIZE; ROW++)
		{
			for (int COLUMN = 0; COLUMN < SIZE; COLUMN++)
			{
				gameBoard->GameBoardTile[ROW][COLUMN]->SetValue(previousBoard[ROW][COLUMN]);
			}
		}
		UpdateScore(currentScore);
		UpdateUndoCount(--undoCount);
		hasMoved = false;
	}
}

void AManagerGame::UpdateUndoCount(int UndoCount)
{
	StartMenuUndoCountText->SetText(FText::AsNumber(UndoCount));
}

void AManagerGame::UpdateScore(int Score)
{
	StartMenuScoreBlock->SetText(FText::AsNumber(Score));
}
