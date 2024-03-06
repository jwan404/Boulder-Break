#include <stdio.h>
#define CAVE_SIZE 10
#include <string.h>

void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char* layout)
{
	int i = 0;
	int row;
	int col;
	while (layout[i] != '\0') {
		for (row = 0; row < CAVE_SIZE; row++) {
			for (col = 0; col < CAVE_SIZE; col++) {
				cave[row][col] = layout[i] - 48;
				i++;
			}
		}
		i++;
	}
}

void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int value;
	int row;
	int col;
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			value = cave[row][col];
			if ((value == '1') || (value == 1)) {
				value = '#';
			}
			else if ((value == '0') || (value == 0)) {
				value = ' ';
			}
			else if (value == 40) {
				value = 'X';
			}
			else if (value == 31) {
				value = 'O';
			}
			else if (value == -6) {
				value = '*';
			}
			else if (value == -5) {
				value = '+';
			}
			else {
				value = ' ';
			}
			printf("%c", value);
		}
		printf("\n");
	}

}

void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char* element)
{
	int cRow;
	int cCol;
	int variable = 0;
	if (strcmp(element, "player") == 0) {
		variable = 40;
	}
	else if (strcmp(element, "boulder") == 0) {
		variable = 31;
	}
	else if (strcmp(element, "hole") == 0) {
		variable = -6;
	}
	else if (strcmp(element, "treasure") == 0) {
		variable = -5;
	}
	else {
		return;
	}

	int player = 0;
	for (cRow = 1; cRow < (CAVE_SIZE - 1); cRow++) {
		for (cCol = 1; cCol < (CAVE_SIZE - 1); cCol++) {
			if (cave[cRow][cCol] == 40) {
				player++;
			}
		}
	}
	if ((player == 0) && (row < CAVE_SIZE) && (row > 0) && (col < CAVE_SIZE) && (col > 0) && (cave[row][col] == 0)) {
		cave[row][col] = variable;
	}
	else if ((variable != 40) && (row < CAVE_SIZE) && (row > 0) && (col < CAVE_SIZE) && (col > 0) && (cave[row][col] == 0)) {
		cave[row][col] = variable;
	}
	else {
		return;
	}
}

void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int temp[CAVE_SIZE][CAVE_SIZE];
	int row;
	int col;
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			if (cave[row][col] <= 40) {
				temp[col][CAVE_SIZE - (row + 1)] = cave[row][col];
			}

		}
	}
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			cave[row][col] = temp[row][col];
		}
	}
}

int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
	int row;
	int col;

	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			if (cave[row][col] == 40) {
				if ((move == 'w') && ((cave[row - 1][col] == 0) || (cave[row - 1][col] == -5))) {
					cave[row - 1][col] = 40;
					cave[row][col] = 0;
					return 0;
				}
				else if ((move == 'a') && ((cave[row][col - 1] == 0) || (cave[row][col - 1] == -5))) {
					cave[row][col - 1] = 40;
					cave[row][col] = 0;
					return 0;
				}
				else if ((move == 's') && ((cave[row + 1][col] == 0) || (cave[row + 1][col] == -5))) {
					cave[row + 1][col] = 40;
					cave[row][col] = 0;
					return 0;
				}
				else if ((move == 'd') && ((cave[row][col + 1] == 0) || (cave[row][col + 1] == -5))) {
					cave[row][col + 1] = 40;
					cave[row][col] = 0;
					return 0;
				}
				else {
				}
			}
		}
	}

	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			if (cave[row][col] == 40) {
				if ((move == 'w') && (cave[row - 1][col] == 31)) {
					int n = 2;
					while ((cave[row - n][col] != -6) && (cave[row - n][col] != -5) && (cave[row - n][col] != 1) && (cave[row - n][col] != 31)) {
						cave[row - n][col] = 31;
						cave[row - n + 1][col] = 0;
						n++;
					}
					if (cave[row - n][col] == -6) {
						cave[row - n + 1][col] = 0;
						cave[row - n][col] = 0;
					}
					return 0;
				}
				else if ((move == 'a') && (cave[row][col - 1] == 31)) {
					int n = 2;
					while ((cave[row][col - n] != -6) && (cave[row][col - n] != -5) && (cave[row][col - n] != 1) && (cave[row][col - n] != 31)) {
						cave[row][col - n] = 31;
						cave[row][col - n + 1] = 0;
						n++;
					}
					if (cave[row][col - n] == -6) {
						cave[row][col - n + 1] = 0;
						cave[row][col - n] = 0;
					}
					return 0;
				}
				else if ((move == 's') && (cave[row + 1][col] == 31)) {
					int n = 2;
					while ((cave[row + n][col] != -6) && (cave[row + n][col] != -5) && (cave[row + n][col] != 1) && (cave[row + n][col] != 31)) {
						cave[row + n][col] = 31;
						cave[row + n - 1][col] = 0;
						n++;
					}
					if (cave[row + n][col] == -6) {
						cave[row + n - 1][col] = 0;
						cave[row + n][col] = 0;
					}
					return 0;
				}
				else if ((move == 'd') && (cave[row][col + 1] == 31)) {
					int n = 2;
					while ((cave[row][col + n] != -6) && (cave[row][col + n] != -5) && (cave[row][col + n] != 1) && (cave[row][col + n] != 31)) {
						cave[row][col + n] = 31;
						cave[row][col + n - 1] = 0;
						n++;
					}
					if (cave[row][col + n] == -6) {
						cave[row][col + n - 1] = 0;
						cave[row][col + n] = 0;
					}
					return 0;
				}
				else {
				}
			}
		}
	}
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			//when player falls into a hole -6
			if ((move == 'w') && (cave[row - 1][col] == -6) && (cave[row][col] == 40)) {
				cave[row][col] = 0; //w up
				return 1;
			}
			else if ((move == 'a') && (cave[row][col - 1] == -6) && (cave[row][col] == 40)) {
				cave[row][col] = 0; //a left
				return 1;
			}
			else if ((move == 's') && (cave[row + 1][col] == -6) && (cave[row][col] == 40)) {
				cave[row][col] = 0; //s down
				return 1;
			}
			else if ((move == 'd') && (cave[row][col + 1] == -6) && (cave[row][col] == 40)) {
				cave[row][col] = 0; //d right
				return 1;
			}
		}
	}
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			//when player reaches exit
			if ((move == 'w') && (cave[row - 1][col] == 21) && (cave[row][col] == 40)) {
				cave[row - 1][col] = 40;
				cave[row][col] = 0;
				return 2;
			}
			else if ((move == 'a') && (cave[row][col - 1] == 21) && (cave[row][col] == 40)) {
				cave[row][col - 1] = 40;
				cave[row][col] = 0;
				return 2;
			}
			else if ((move == 's') && (cave[row + 1][col] == 21) && (cave[row][col] == 40)) {
				cave[row + 1][col] = 40;
				cave[row][col] = 0;
				return 2;
			}
			else if ((move == 'd') && (cave[row][col + 1] == 21) && (cave[row][col] == 40)) {
				cave[row][col + 1] = 40;
				cave[row][col] = 0;
				return 2;
			}
		}
	}
	return 0;
}

int main(void)
{
	char layout[200] = "1111111111100000000110000000011000000001100000000E10000000011000000001100000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = { 0 };
	InitialiseCave(cave, layout);
	AddItem(cave, 7, 3, "player");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 2, 3, "boulder");
	AddItem(cave, 4, 6, "boulder");
	AddItem(cave, 5, 7, "boulder");
	AddItem(cave, 6, 8, "boulder");
	AddItem(cave, 7, 1, "hole");
	AddItem(cave, 8, 3, "hole");
	AddItem(cave, 6, 4, "treasure");
	AddItem(cave, 3, 5, "treasure");
	AddItem(cave, 1, 1, "treasure");
	AddItem(cave, 8, 8, "treasure");
	AddItem(cave, 5, 1, "hole");
	AddItem(cave, 6, 1, "hole");

	MakeMove(cave, 'w');

	PrintCave(cave);
	return 0;
}