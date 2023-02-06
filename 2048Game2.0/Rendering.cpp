#include "Rendering.h"

void Rendering::startRendering(int* gamefield)
{
	setCursorPosition(20, 0);
	printf("                                                           ");
	string topwall = "\t ___________________________";
	string topbot = " \t|______|______|______|______|";
	string wall = " \t|      |      |      |      |";
	int printvalue = 0;
	printf("\n%s\n", topwall.c_str());

	for (int i = 0; i < SIZE_ARRAY; i += SIZE_ROW_OR_COL)
	{
		printf("%s\n \t", wall.c_str());
		for (int j = 0; j < SIZE_ROW_OR_COL; j++)
		{
			printvalue = gamefield[i + j];

			switch (printvalue)
			{
			case 2: case 4:
				printf("|   \x1B[31m%-3d\033[0m", printvalue);
				break;
			default:
				printf("|   %-3d", printvalue);
				break;
			}

		}
		printf("|\n%s\n", topbot.c_str());
	}

	setCursorPosition(51, 2);
	printf("Текущий счет: %d      ", 0);

	setCursorPosition(51, 5);
	printf("Команды управления игрой:");

	setCursorPosition(51, 7);
	printf("<- Cмещение всех блоков влево");

	setCursorPosition(51, 8);
	printf("\x18 Cмещение всех блоков вверх");

	setCursorPosition(51, 9);
	printf("-> Cмещение всех блоков вправо");

	setCursorPosition(51, 10);
	printf("\x19 Cмещение всех блоков вниз");

	setCursorPosition(51, 12);
	printf("'b' - Отмена одного хода");

	setCursorPosition(51, 13);
	printf("'n' - Начать игру сначала");

	setCursorPosition(0, 0);
}

void  Rendering::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void  Rendering::ShowGameField(int* gamefield, const int& score)
{
	int print_cell = 0;
	for (int i = 0; i < SIZE_ARRAY; i += 4)
	{
		for (int j = 0; j < SIZE_ROW_OR_COL; j++)
		{
			setCursorPosition(9 + j * 7, 3 + (i / 4) * 3);

			gamefield[i + j] = abs(gamefield[i + j]);
			print_cell = gamefield[i + j];

			switch (print_cell)
			{
			case 0:
				printf("   %-3d", print_cell);
				break;

			case 2: case 4: case 8:
				printf("   \x1B[31m%-3d\033[0m", print_cell);
				break;

			case 16: case  32: case  64:
				printf("   \x1B[32m%-3d\033[0m", print_cell);
				break;

			case 128: case 256: case 512:
				printf("   \x1B[33m%-3d\033[0m", print_cell);
				break;

			case 1024: case 2048: case 4096:
				printf("   \x1B[34m%-5d\033[0m", print_cell);
				break;

			case 8192: case 16384: case 32768:
				printf("   \x1B[35m%-5d\033[0m", print_cell);
				break;

			default:
				printf("|\x1B[36m%-5d\033[0m", print_cell);
				break;
			}
		}
	}
	setCursorPosition(65, 2);
	printf("%d          ", score);
	setCursorPosition(0, 0);
}