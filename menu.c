#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"

void saveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char** name)
{
	Bool indexMode = false;
	char input[5];
	int menu;
	int slot;
	Bool jumpToMain = false;
	int esc;

	clearHome();
	printf("Welcome to Rubiks!\n");

	do
	{
		clearMenu();
		printf("Rubiks\n");
		printf("1) New game\n");
		printf("2) Load game\n");
		if(jumpToMain == false)
		{
			esc = 3;
			printf("3) Exit\n");
		}
		else
		{
			esc = 5;
			printf("3) Save\n");
			printf("4) Main menu\n");
			printf("5) Exit\n");
		}
		printf(">  ");
		fgets(input, 5, stdin);
		menu = (int)strtol(input, NULL, 10);

		switch(menu)
		{
			//New game
			case 1:
				if(newGameMenu(cube, indexMode, name, &slot, input, menu) != 0)
				{
					clearHome();
					printf("Welcome to Rubiks, %s!\n", name[slot]);	
					jumpToMain = true;
					mainMenu(cube, rowNum, faceNum, color, name[slot], &indexMode, input, menu, slot);
				}
				break;

			//Load game
			case 2:
				if(-1 < loadGameMenu(cube, &indexMode, name, &slot, input, menu))
				{
					clearHome();
					printf("Welcome back, %s!\n", name[slot]);	
					jumpToMain = true;
					mainMenu(cube, rowNum, faceNum, color, name[slot], &indexMode, input, menu, slot);
				}
				break;

			case 3:
				//Exit
				if(jumpToMain == false)
				{
					return;
				}
				//Save
				else
				{
					if(saveFile(cube, name[slot], indexMode, slot+1) == 0)
					{
						clearHome();
						printf("Save successful\n");
					}
					else
					{
						clearHome();
						printf("Save unsuccessful\n");
					}
				}
				break;

			case 4:
				//Main menu
				if(jumpToMain == true)
				{	
					mainMenu(cube, rowNum, faceNum, color, name[slot], &indexMode, input, menu, slot);
				}
				break;

			//Main menu
			case 5:
				if(jumpToMain == true)
				{
					return;
				}
		}
	} while(menu != esc);
}

int loadGameMenu(Square* cube, Bool* indexMode, char** name, int* slot, char* input, int menu)
{
	do
	{
		clearMenu();
		printf("Which slot do you want to load?\n");
		printf("1) %s\n", name[0]);
		printf("2) %s\n", name[1]);
		printf("3) %s\n", name[2]);
		printf("4) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = (int)strtol(input, NULL, 10);

		switch(menu)
		{
			case 1:
			case 2:
			case 3:
				*slot = menu-1;
				if(loadFile(cube, name[*slot], indexMode, menu) == -1)
				{
					return -1;
				}
				break;

			//Go back;
			case 4: return 0;
		}
	} while(menu < 1 || 4 < menu);

	return 1;
}

int newGameMenu(Square* cube, Bool indexMode, char** name, int* slot, char* input, int menu)
{
	do
	{
		clearMenu();
		printf("Which slot do you want to save to?\n");
		printf("1) %s\n", name[0]);
		printf("2) %s\n", name[1]);
		printf("3) %s\n", name[2]);
		printf("4) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = (int)strtol(input, NULL, 10);

		switch(menu)
		{
			case 1:
			case 2:
			case 3:
				*slot = menu-1;
				clearMenu();
				printf("Enter your name: ");
				fgets(name[*slot], sizeof(name[*slot]), stdin);
				removeNewLine(name[*slot]);
				saveFile(cube, name[*slot], indexMode, menu);
				break;

			//Go back;
			case 4: return 0;
		}
	} while(menu < 1 || 4 < menu);

	return 1;
}

void mainMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* name, Bool* indexMode, char* input, int menu, int slot)
{
	do
	{
		printRubiks(cube, *indexMode);
		clearMenu();
		printf("Main Menu\n");
		printf("1) Shuffle\n");
		printf("2) Solve\n");
		printf("3) Options\n");
		printf("4) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = (int)strtol(input, NULL, 10);

		switch(menu)
		{
			//Shuffle menu
			case 1:
				shuffleMenu(cube, rowNum, faceNum, color, *indexMode, input);
				break;

			//Solve menu
			case 2:
				solveMenu(cube, rowNum, faceNum, color, input, menu, *indexMode);
				break;

			//Options menu
			case 3:
				optionsMenu(cube, menu, input, name, indexMode, slot);
				break;

			//Go back
			case 4:	return;
		}
		clearMenu();
	} while(menu != 4);
}

void shuffleMenu(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, char* input)
{
	int cycles;

	do
	{
		clearMenu();
		printf("How many shuffles do you want to perform?\n");
		printf(">  ");
		fgets(input, 5, stdin);
		cycles = strtol(input, NULL, 10);
	} while(cycles < 0);

	clearMenu();
	shuffleCube(cube, rowNum, faceNum, color, cycles, indexMode);
}

void solveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int menu, Bool indexMode)
{
	do
	{
		clearMenu();
		printf("Solve\n");
		printf("1) Auto\n");
		printf("2) Manual\n");
		printf("3) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = strtol(input, NULL, 10);

		switch(menu)
		{
			//Auto solve
			case 1:
				clearMenu();
				solveCube(cube, rowNum, faceNum, color, indexMode);
				break;
			//Manual solve
			case 2:
				manualSolveMenu(cube, rowNum, faceNum, color, input, menu, indexMode);
				break;
			//Go back
			case 3: return;
		}
	} while(menu < 1 || 3 < menu);
}

void manualSolveMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int menu, Bool indexMode)
{
	int i = 0;
	int prevTurn = 0;
	int face;
	Bool inverted;

	do
	{
		clearMenu();
		printf("Rotate face\n");
		printf("1) Left face\n");
		printf("2) Right face\n");
		printf("3) Up face\n");
		printf("4) Down face\n");
		printf("5) Front face\n");
		printf("6) Back face\n");
		printf("7) Rotate cube\n");
		printf("8) Go back\n");
		if(prevTurn != 0)
		{
			printf("9) Undo\n");
		}
		printf(">  ");
		fgets(input, 5, stdin);
		menu = strtol(input, NULL, 10);

		switch(menu)
		{
			//Direction menu
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				face = menu-1;
				prevTurn = menu;
				if(directionMenu(cube, rowNum, faceNum, color, input, face, &prevTurn, menu, indexMode, &inverted) == -1)
				{
					i--;
				}
				break;

			//Rotate cube
			case 7: 
				prevTurn = menu;
				if(rotateMenu(cube, faceNum, color, menu, input, &prevTurn) == -1)
				{
					i--;
				}
				break;

			//Go back
			case 8: return;

			//Undo previous move
			case 9:
				switch(prevTurn)
				{
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 6:
						face = prevTurn-1;
						inverted = true;
						movements(cube, rowNum[face], faceNum[face], color, face, inverted);
						break;
					case 7:
					case 8:
					case 9:
					case 10:
					case 11:
					case 12:
						face = prevTurn-7;
						inverted = false;
						movements(cube, rowNum[face], faceNum[face], color, face, inverted);
						break;
					case 13: rotateCube(cube, faceNum, color, DOWN); break;
					case 14: rotateCube(cube, faceNum, color, UP); break;
					case 15: rotateCube(cube, faceNum, color, RIGHT); break;
					case 16: rotateCube(cube, faceNum, color, LEFT); break;
						break;
				}
				prevTurn = 0;
				break;

			default: i--; break;
		}
		printRubiks(cube, indexMode);
		clearHome();
		i++;
		printf("Solving... %d", i);
	} while(menu != 8);
}

int rotateMenu(Square* cube, int** faceNum, Color* color, int menu, char* input, int* prevTurn)
{
	do
	{
		clearMenu();
		printf("Rotate cube\n");
		printf("1) Up\n");
		printf("2) Down\n");
		printf("3) Left\n");
		printf("4) Right\n");
		printf("5) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = strtol(input, NULL, 10);

		switch(menu)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				rotateCube(cube, faceNum, color, menu-1);
				*prevTurn += (menu+5);
				break;
			//Go back
			case 5: return -1;
		}
	} while(menu < 1 || 5 < menu);

	return 0;
}

int directionMenu(Square* cube, int** rowNum, int** faceNum, Color* color, char* input, int face, int* prevTurn, int menu, Bool indexMode, Bool* inverted)
{
	do
	{
		clearMenu();
		printf("Direction\n");
		printf("1) Clockwise\n");
		printf("2) Counterclockwise\n");
		printf("3) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = strtol(input, NULL, 10);

		switch(menu)
		{
			//Clockwise
			case 1: *inverted = false; break;
			//Counterclockwise
			case 2: *inverted = true; *prevTurn += 6; break;
			//Go back
			case 3: return -1;
		}
		movements(cube, rowNum[face], faceNum[face], color, face, *inverted);
	} while(menu < 1 || 3 < menu);
	return 0;
}

void optionsMenu(Square* cube, int menu, char* input, char* name, Bool* indexMode, int slot)
{
	do
	{
		clearMenu();
		printf("Options\n");
		printf("1) Change name:\t%s\n", name);
		printf("2) Index mode:\t%s\n", printBool(*indexMode));
		printf("3) Go back\n");
		printf(">  ");
		fgets(input, 5, stdin);
		menu = strtol(input, NULL, 10);

		switch(menu)
		{
			//Change name menu
			case 1:
				changeNameMenu(name);
				break;
			//Index mode menu
			case 2:
				if(*indexMode == false)
				{
					*indexMode = true;
				}
				else
				{
					*indexMode = false;
				}
				printRubiks(cube, *indexMode);
				break;
			//Go back
			case 3: 
				if(saveFile(cube, name, *indexMode, slot+1) == 0)
				{
					clearHome();
					printf("Options saved\n");
				}
				else
				{
					clearHome();
					printf("Options not saved\n");
				}
				return;
		}
	} while(menu != 3);
}

void changeNameMenu(char* name)
{
	clearMenu();
	printf("Enter a new name: ");
	fgets(name, sizeof(name), stdin);
	removeNewLine(name);
	clearHome();
	printf("Welcome to Rubiks, %s!\n", name);
}
