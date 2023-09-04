#include "ManagerGame.h"

AManagerGame::AManagerGame() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AManagerGame::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	//ƒобавление GameBoard
	if (world != nullptr) {
		gameBoard = world->SpawnActor<AGameBoard>(AGameBoard::StaticClass(), FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	}

	const int SIZE = gameBoard->getSIZEGRID();
	previousBoard.SetNum(SIZE);
	for (int ROW = 0; ROW < SIZE; ROW++) {
		previousBoard[ROW].SetNum(SIZE);
	}
	//—оздание виджетов
	startMenuWidget = CreateWidget<UUserWidget>(GetWorld(), mainMenu);
	gameOverWidget = CreateWidget<UUserWidget>(GetWorld(), gameOver);
	if (startMenuWidget) {
		startMenuWidget->AddToViewport();
		startMenuScoreBlock = Cast<UTextBlock>(startMenuWidget->GetWidgetFromName(TEXT("ScoreTextBlockWidget")));
		startMenuUndoCountText = Cast<UTextBlock>(startMenuWidget->GetWidgetFromName(TEXT("UndoCountText")));
	}
	if (gameOverWidget) {
		gameOverWidget->AddToViewport();
	}
	startGame();
}

void AManagerGame::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AManagerGame::startGame()
{
	//—крытие виджета до момента, пока игра не закончитс€	
	gameOverWidget->SetVisibility(ESlateVisibility::Collapsed);

	hasMoved = false;
	undoCount = 3;
	currentScore = 0;
	previousScore = 0;

	updateScore(currentScore);
	updateUndoCount(undoCount);
	const int SIZE = gameBoard->getSIZEGRID();
	for (int ROW = 0; ROW < SIZE; ROW++) {
		for (int COLUMNUMN = 0; COLUMNUMN < SIZE; COLUMNUMN++) {
			gameBoard->gameBoardTile[ROW][COLUMNUMN]->setValue(0);
		}
	}

	gameBoard->generateRandomValue();
	gameBoard->generateRandomValue();
	savePreviousBoard();
}

void AManagerGame::endGame()// ‘ункци€ дл€ окончани€ игры
{
	gameOverWidget->SetVisibility(ESlateVisibility::Visible);
}

void AManagerGame::pushUp()//—двигаем €чейки вверх
{
	savePreviousBoard();

	hasMoved = false;
	const int SIZE = gameBoard->getSIZEGRID();

	for (int COLUMN = 0; COLUMN < SIZE; COLUMN++) {
		bool hasMerged = false; // флаг, указывающий, было ли выполнено сли€ние в данном столбце на данной итерации

		for (int ROW = 1; ROW < SIZE; ROW++) {
			if (gameBoard->gameBoardTile[ROW][COLUMN]->getValue() != 0) {
				int newROW = ROW;
				while (newROW > 0 && gameBoard->gameBoardTile[newROW - 1][COLUMN]->getValue() == 0) {
					gameBoard->gameBoardTile[newROW - 1][COLUMN]->setValue(gameBoard->gameBoardTile[newROW][COLUMN]->getValue());
					gameBoard->gameBoardTile[newROW][COLUMN]->setValue(0);
					newROW--;
					hasMoved = true;
				}

				if (newROW > 0 && gameBoard->gameBoardTile[newROW - 1][COLUMN]->getValue() == gameBoard->gameBoardTile[newROW][COLUMN]->getValue() 
					&& !hasMerged && gameBoard->gameBoardTile[newROW][COLUMN]->getValue() != 0) {
					
					gameBoard->gameBoardTile[newROW - 1][COLUMN]->setValue(gameBoard->gameBoardTile[newROW - 1][COLUMN]->getValue() * 2);
					currentScore += gameBoard->gameBoardTile[newROW - 1][COLUMN]->getValue();

					gameBoard->gameBoardTile[newROW][COLUMN]->setValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else {
					hasMerged = false; // сбрасываем флаг, если не было сложени€
				}
			}
		}
	}
	ifHasMoved();
	checkEndGame();
}

void AManagerGame::pushDown()//—двигаем €чейки вниз
{
	savePreviousBoard();
	hasMoved = false;
	const int SIZE = gameBoard->getSIZEGRID();

	for (int COLUMN = 0; COLUMN < SIZE; COLUMN++)  {
		bool hasMerged = false;
		for (int ROW = SIZE - 2; ROW >= 0; ROW--) {
			if (gameBoard->gameBoardTile[ROW][COLUMN]->getValue() != 0) {
				int newROW = ROW;
				while (newROW < SIZE - 1 && gameBoard->gameBoardTile[newROW + 1][COLUMN]->getValue() == 0) {
					gameBoard->gameBoardTile[newROW + 1][COLUMN]->setValue(gameBoard->gameBoardTile[newROW][COLUMN]->getValue());
					gameBoard->gameBoardTile[newROW][COLUMN]->setValue(0);
					newROW++;
					hasMoved = true;
				}
				if (newROW < SIZE - 1 && gameBoard->gameBoardTile[newROW + 1][COLUMN]->getValue() == gameBoard->gameBoardTile[newROW][COLUMN]->getValue() 
					&& !hasMerged && gameBoard->gameBoardTile[newROW][COLUMN]->getValue() != 0) {
					gameBoard->gameBoardTile[newROW + 1][COLUMN]->setValue(gameBoard->gameBoardTile[newROW + 1][COLUMN]->getValue() * 2);

					currentScore += gameBoard->gameBoardTile[newROW + 1][COLUMN]->getValue();

					gameBoard->gameBoardTile[newROW][COLUMN]->setValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else {
					hasMerged = false; // сбрасываем флаг, если не было сложени€
				}
			}
		}
	}
	ifHasMoved();
	checkEndGame();
}

void AManagerGame::pushLeft()//—двигаем €чейки влево
{
	savePreviousBoard();
	hasMoved = false;
	const int SIZE = gameBoard->getSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++) {
		bool hasMerged = false; // добавл€ем флаг дл€ запоминани€ выполненного сложени€
		for (int COLUMN = 1; COLUMN < SIZE; COLUMN++) {
			if (gameBoard->gameBoardTile[ROW][COLUMN]->getValue() != 0) {
				int newCOLUMN = COLUMN;
				while (newCOLUMN > 0 && gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->getValue() == 0) {
					gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->setValue(gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue());
					gameBoard->gameBoardTile[ROW][newCOLUMN]->setValue(0);
					newCOLUMN--;
					hasMoved = true;
				}
				if (newCOLUMN > 0 && gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->getValue() == gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue()
					&& !hasMerged  && gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue() != 0) {
					gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->setValue(gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->getValue() * 2);

					currentScore += gameBoard->gameBoardTile[ROW][newCOLUMN - 1]->getValue();

					gameBoard->gameBoardTile[ROW][newCOLUMN]->setValue(0);
					hasMerged = true; // помечаем, что сложение было выполнено
					hasMoved = true;
				}
				else {
					hasMerged = false; // сбрасываем флаг, если не было сложени€
				}
			}
		}
	}
	ifHasMoved();
	checkEndGame();
}

void AManagerGame::pushRight()// —двигаем €чейки вправо
{
	savePreviousBoard();
	hasMoved = false;
	const int SIZE = gameBoard->getSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++) {
		bool hasMerged = false;

		for (int COLUMN = SIZE - 2; COLUMN >= 0; COLUMN--) {
			if (gameBoard->gameBoardTile[ROW][COLUMN]->getValue() != 0) {
				int newCOLUMN = COLUMN;
				while (newCOLUMN < SIZE - 1 && gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->getValue() == 0) {
					gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->setValue(gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue());
					gameBoard->gameBoardTile[ROW][newCOLUMN]->setValue(0);
					newCOLUMN++;
					hasMoved = true;
				}

				if (newCOLUMN < SIZE - 1 && gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->getValue() == gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue()
					&& !hasMerged && gameBoard->gameBoardTile[ROW][newCOLUMN]->getValue() != 0) {
					gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->setValue(gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->getValue() * 2);

					currentScore += gameBoard->gameBoardTile[ROW][newCOLUMN + 1]->getValue();

					gameBoard->gameBoardTile[ROW][newCOLUMN]->setValue(0);
					hasMerged = true;
					hasMoved = true;
				}
				else {
					hasMerged = false; // сбрасываем флаг, если не было сложени€
				}
			}
		}
	}

	ifHasMoved();
	checkEndGame();
}

void AManagerGame::checkEndGame()// проверка на конец игры
{
	// ”знаем остались ли пусте €чейки
	if (gameBoard->getCountEmptyTile() == 0) {

		const int SIZE = gameBoard->getSIZEGRID();
		// проверка: можно ли произвести сли€ние с соседними блоками
		for (int ROW = 0; ROW < SIZE; ROW++) {
			for (int COLUMNUMN = 0; COLUMNUMN < SIZE; COLUMNUMN++) {
				ATile* currentTile = gameBoard->gameBoardTile[ROW][COLUMNUMN];
				if (canCombineWithTile(currentTile, ROW - 1, COLUMNUMN) ||
					canCombineWithTile(currentTile, ROW + 1, COLUMNUMN) ||
					canCombineWithTile(currentTile, ROW, COLUMNUMN - 1) ||
					canCombineWithTile(currentTile, ROW, COLUMNUMN + 1))
				{
					return;
				}
			}
		}
		endGame();
	}
}

bool AManagerGame::canCombineWithTile(ATile* const currentTile,int const &ROW,int const &COLUMNUMN)
{
	// функци€ определ€ет можно ли сли€ть данный блок с соседним по определенному индексу
	if (ROW < 0 || ROW >= gameBoard->getSIZEGRID() || COLUMNUMN < 0 || COLUMNUMN >= gameBoard->getSIZEGRID()) {
		return false;
	}

	ATile* adjacentTile = gameBoard->gameBoardTile[ROW][COLUMNUMN];
	if (currentTile->getValue() == adjacentTile->getValue()) {
		return true;
	}

	return false;
}

void AManagerGame::savePreviousBoard()// —охранение состо€ни€ предыдущего хода
{
	previousScore = currentScore;
	int SIZE = gameBoard->getSIZEGRID();

	for (int ROW = 0; ROW < SIZE; ROW++) {
		for (int COLUMN = 0; COLUMN < SIZE; COLUMN++) {
			previousBoard[ROW][COLUMN] = gameBoard->gameBoardTile[ROW][COLUMN]->getValue();
		}
	}
}

void AManagerGame::ifHasMoved()
{
	updateScore(currentScore);
	if (hasMoved) {
		gameBoard->generateRandomValue();
	}
}

void AManagerGame::setPreviousBoard() // «амена текущих значени€ €чеек на значени€, которые были на предыдущем ходе
{	
	if (undoCount > 0 && hasMoved) {
		currentScore = previousScore;
		int SIZE = gameBoard->getSIZEGRID();

		for (int ROW = 0; ROW < SIZE; ROW++) {
			for (int COLUMN = 0; COLUMN < SIZE; COLUMN++) {
				gameBoard->gameBoardTile[ROW][COLUMN]->setValue(previousBoard[ROW][COLUMN]);
			}
		}
		updateScore(currentScore);
		updateUndoCount(--undoCount);
		hasMoved = false;
	}
}

void AManagerGame::updateUndoCount(int countUndo)
{
	startMenuUndoCountText->SetText(FText::AsNumber(countUndo));
}

void AManagerGame::updateScore(int score)
{
	startMenuScoreBlock->SetText(FText::AsNumber(score));
}