/*Boulder Break */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 10

void InitialiseStory(char* paragraph)
{
	char temp[2000] = "You are an adventurer on your way to find some treasure.\nAlong the way you entered a cave and got stuck.\nTo escape the cave and collect the treasure,\nyou must push the boulders into holes that block the exit.\nGood luck on your adventures.";
	strcpy(paragraph, temp); 
}

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
			//when there's treasure -5 or empty space
			if ((move == 'w') && (cave[row][col] == 40)) {
				if ((cave[row - 1][col] == 0) || (cave[row - 1][col] == -5)) {
					cave[row - 1][col] = 40; //w up
					cave[row][col] = 0;
					return 0;
				}
			}
			else if ((move == 'a') && (cave[row][col] == 40)) {
				if ((cave[row][col - 1] == 0) || (cave[row][col - 1] == -5)) {
					cave[row][col - 1] = 40; //a left
					cave[row][col] = 0;
					return 0;
				}

			}
			else if ((move == 's') && (cave[row][col] == 40)) {
				if ((cave[row + 1][col] == 0) || (cave[row + 1][col] == -5)) {
					cave[row + 1][col] = 40; //s down
					cave[row][col] = 0;
					return 0;
				}

			}
			else if ((move == 'd') && (cave[row][col] == 40)) {
				if ((cave[row][col + 1] == 0) || (cave[row][col + 1] == -5)) {
					cave[row][col + 1] = 40; //d right
					cave[row][col] = 0;
					return 0;
				}

			}
		}
	}
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			//when player moves a boulder 31 into a hole -6
			if ((move == 'w') && (cave[row - 1][col] == 31) && (cave[row][col] == 40) && (cave[row - 2][col] == -6)) {
				cave[row - 1][col] = 0; //w up
				cave[row - 2][col] = 0;
				return 0;
			}
			else if ((move == 'a') && (cave[row][col - 1] == 31) && (cave[row][col] == 40) && (cave[row][col - 2] == -6)) {
				cave[row][col - 1] = 0; //a left
				cave[row][col - 2] = 0;
				return 0;
			}
			else if ((move == 's') && (cave[row + 1][col] == 31) && (cave[row][col] == 40) && (cave[row + 2][col] == -6)) {
				cave[row + 1][col] = 0; //s down
				cave[row + 1][col] = 0;
				return 0;
			}
			else if ((move == 'd') && (cave[row][col + 1] == 31) && (cave[row][col] == 40) && (cave[row][col + 2] == -6)) {
				cave[row][col + 1] = 0; //d right
				cave[row][col + 1] = 0;
				return 0;
			}
		}
	}
	for (row = 0; row < CAVE_SIZE; row++) {
		for (col = 0; col < CAVE_SIZE; col++) {
			//when player pushes boulder 31
			int i = 0;
			if ((move == 'w') && (cave[row - 1][col] == 31) && (cave[row][col] == 40)) {
				while (cave[row][col] == 0) {
					cave[row - i][col] = 31;
					i++;
				}
				return 0;
			}
			else if ((move == 'a') && (cave[row][col - 1] == 31) && (cave[row][col] == 40)) {
				while (cave[row][col] == 0) {
					cave[row][col - i] = 31;
					i++;
				}
				return 0;
			}
			else if ((move == 's') && (cave[row + 1][col] == 31) && (cave[row][col] == 40)) {
				while (cave[row][col] == 0) {
					cave[row + i][col] = 31;
					i++;
				}
				return 0;
			}
			else if ((move == 'd') && (cave[row][col + 1] == 31) && (cave[row][col] == 40)) {
				while (cave[row][col] == 0) {
					cave[row][col + i] = 31;
					i++;
				}
				return 0;
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
}


/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
	char layout[200] = "1111111111111000001111000000111000000001100000000E10010000011100000011111000001111111001111111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = {0};
	int gameOver = 0;

	InitialiseStory(story);
	InitialiseCave(cave, layout);
	AddItem(cave, 2, 4, "boulder");
	AddItem(cave, 5, 6, "boulder");
	AddItem(cave, 4, 8, "hole");
	AddItem(cave, 1, 4, "treasure");
	AddItem(cave, 4, 5, "player");

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		} else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}
