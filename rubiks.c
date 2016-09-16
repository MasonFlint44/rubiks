#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubiks.h"

Square* buildCube(Square* cube)
{
	Color face = WHITE;
	int i;

	for(i = 0; i < 54; i++)
	{
		cube[i].color = face;

		if((i+1) % 9 == 0)
		{
			face++;
		}
	}

	return cube;
}

void shuffleCube(Square* cube, int** rowNum, int** faceNum, Color* color, int cycles, Bool indexMode)
{
	if(cycles <= 0)
	{
		return;
	}

	srand(time(NULL));

	int face;
	Bool inverted;
	int i;

	for(i = 0; i < cycles; i++)
	{
		face = rand()%6;
		inverted = rand()%2;

		movements(cube, rowNum[face], faceNum[face], color, face, inverted);

		clearHome();
		printf("Shuffling... %d", i+1);
		//waitFor(1);
		printRubiks(cube, indexMode);
	}

	clearHome();
	printf("Shuffled %d times\n", cycles);
}

void movementHelper(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i, int face, Bool inverted)
{
	movements(cube, rowNum[face], faceNum[face], color, face, inverted);
	clearHome();
	printf("Solving... %d", ++(*i));
	printRubiks(cube, indexMode);
}

void rotateHelper(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i, Direction direction)
{
	rotateCube(cube, faceNum, color, direction);
	//clearHome();
	//printf("Solving... %d", ++(*i));
	printRubiks(cube, indexMode);
}

void solveCube(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode)
{
	int i = 0;

	//orientCube(cube, faceNum, color, indexMode, &i);

	solveWhiteCross(cube, rowNum, faceNum, color, indexMode, &i);
	solveWhiteCorners(cube, rowNum, faceNum, color, indexMode, &i);

	rotateHelper(cube, faceNum, color, indexMode, &i, DOWN);
	rotateHelper(cube, faceNum, color, indexMode, &i, DOWN);

	solveMiddleLayer(cube, rowNum, faceNum, color, indexMode, &i);
	solveYellowCross(cube, rowNum, faceNum, color, indexMode, &i);
	solveYellowCorners(cube, rowNum, faceNum, color, indexMode, &i);
	positionYellowCorners(cube, rowNum, faceNum, color, indexMode, &i);
	positionYellowEdges(cube, rowNum, faceNum, color, indexMode, &i);

	//orientCube(cube, faceNum, color, indexMode, &i);
	
	printRubiks(cube, indexMode);
	clearHome();
	printf("Solved in %d moves", i);
}

void orientCube(Square* cube, int** faceNum, Color* color, Bool indexMode, int* j)
{
	int centerArr[6] = {4, 13, 22, 31, 40, 49};
	int i;
	for(i = 0; i < 6; i++)
	{
		if(cube[centerArr[i]].color == WHITE)
		{
			break;
		}
	}
	switch(i)
	{
		case 0:
			break;
		case 1:
			rotateHelper(cube, faceNum, color, indexMode, j, RIGHT);
		case 2:
			rotateHelper(cube, faceNum, color, indexMode, j, UP);
			break;
		case 3:
			rotateHelper(cube, faceNum, color, indexMode, j, LEFT);
			rotateHelper(cube, faceNum, color, indexMode, j, UP);
			break;
		case 4:
			rotateHelper(cube, faceNum, color, indexMode, j, RIGHT);
			rotateHelper(cube, faceNum, color, indexMode, j, RIGHT);
			rotateHelper(cube, faceNum, color, indexMode, j, UP);
			break;
		case 5:
			rotateHelper(cube, faceNum, color, indexMode, j, UP);
			rotateHelper(cube, faceNum, color, indexMode, j, UP);
			break;
	}
}

void solveWhiteCross(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* l)
{
	int edgeArr[2][12] = {	{5, 7, 3, 1, 32, 34, 30, 25, 21, 16, 12, 43},
							{28, 19, 10, 37, 41, 50, 23, 46, 14, 48, 39, 52}	};
	int i, j;

	while(checkWhiteCross(cube, faceNum, color, indexMode, l) == false)
	{
		for(i = 0; i < 4; i++)
		{
			for(j = 0; j < 12; j++)
			{
				if(cube[edgeArr[0][j]].color == cube[4].color && cube[edgeArr[1][j]].color == cube[31].color)
				{
					break;
				}
				else if(cube[edgeArr[0][j]].color == cube[31].color && cube[edgeArr[1][j]].color == cube[4].color)
				{
					break;
				}
			}

			switch(j)
			{
				case 0:
					break;
				case 1:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 2:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 0, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
					break;
				case 3:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 5, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, true);
					break;
				case 4:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, true);
					break;
				case 5:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 6:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 7:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 8:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 0, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 0, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 9:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					break;
				case 10:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 5, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 5, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, false);
					break;
				case 11:
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 3, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, true);
					break;
			}

			if(cube[edgeArr[0][0]].color == cube[31].color && cube[edgeArr[1][0]].color == cube[4].color)
			{
				movementHelper(cube, rowNum, faceNum, color, indexMode, l, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, l, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, l, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, l, 2, true);
			}

			rotateHelper(cube, faceNum, color, indexMode, l, RIGHT);
		}
	}
}

Bool checkWhiteCross(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;

	for(j = 0; j < 4; j++)
	{
		if(cube[7].color != cube[4].color)
		{
			return false;
		}
		if(cube[19].color != cube[22].color)
		{
			return false;
		}

		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	
	return true;
}

void solveWhiteCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int cornerArray[3][8] = {	{8, 2, 0, 6, 26, 35, 15, 17},
								{20, 29, 9, 11, 33, 44, 42, 24},
								{27, 38, 36, 18, 47, 53, 51, 45}	};
	int j, k;

	while(checkWhiteCorners(cube, faceNum, color, indexMode, i) == false)
	{
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if(cube[cornerArray[0][k]].color == cube[4].color || cube[cornerArray[0][k]].color == cube[22].color || cube[cornerArray[0][k]].color == cube[31].color)
				{
					if(cube[cornerArray[1][k]].color == cube[31].color || cube[cornerArray[1][k]].color == cube[4].color || cube[cornerArray[1][k]].color == cube[22].color)
					{
						if(cube[cornerArray[2][k]].color == cube[22].color || cube[cornerArray[2][k]].color == cube[31].color || cube[cornerArray[2][k]].color == cube[4].color)
						{
							break;
						}
					}
				}
			}

			switch(k)
			{
				case 0:
					break;
				case 1:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					break;
				case 2:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
					break;
				case 3:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
					break;
				case 4:
					break;
				case 5:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, true);
					break;
				case 6:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
				case 7:
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
					break;
			}

			while(cube[cornerArray[0][0]].color != cube[4].color || cube[cornerArray[1][0]].color != cube[22].color || cube[cornerArray[2][0]].color != cube[31].color)
			{
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 3, false);
			}

			rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
		}
	}
}

Bool checkWhiteCorners(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[8].color != cube[4].color)
		{
			return false;
		}
		if(cube[20].color != cube[22].color)
		{
			return false;
		}
		if(cube[27].color != cube[31].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}

void solveMiddleLayer(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j, k;

	while(checkMiddleLayer(cube, faceNum, color, indexMode, i) == false)
	{
		for(k = 0; k < 4; k++)
		{
			if(cube[14].color != cube[4].color && cube[21].color != cube[4].color)
			{
				if(cube[14].color == cube[22].color || cube[14].color == cube[31].color || cube[14].color == cube[40].color)
				{
					while(cube[7].color != cube[4].color && cube[19].color != cube[4].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					}
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				}
				else if(cube[21].color == cube[13].color || cube[21].color == cube[31].color || cube[21].color == cube[40].color)
				{
					while(cube[7].color != cube[4].color && cube[19].color != cube[4].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					}
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				}
			}
			
			if(cube[23].color != cube[4].color && cube[30].color != cube[4].color)
			{
				if(cube[23].color == cube[13].color || cube[23].color == cube[31].color || cube[23].color == cube[40].color)
				{
					while(cube[7].color != cube[4].color && cube[19].color != cube[4].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					}
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				}
				else if(cube[30].color == cube[13].color || cube[30].color == cube[22].color || cube[30].color == cube[40].color)
				{
					while(cube[7].color != cube[4].color && cube[19].color != cube[4].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					}
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
					movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				}
			}		for(j = 0; j < 4; j++)
			{
				if(cube[19].color == cube[22].color && cube[7].color == cube[13].color)
				{
					while(cube[14].color != cube[13].color || cube[21].color != cube[22].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
					}
				}
				else if(cube[19].color == cube[22].color && cube[7].color == cube[31].color)
				{
					while(cube[30].color != cube[31].color || cube[23].color != cube[22].color)
					{
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
						movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
					}
				}
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
			}
			rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
		}
	}
}

Bool checkMiddleLayer(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[23].color != cube[22].color)
		{
			return false;
		}
		if(cube[30].color != cube[31].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}

int getYellowCrossState(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	if(cube[1].color == cube[4].color && cube[3].color == cube[4].color && cube[5].color == cube[4].color && cube[7].color == cube[4].color)
	{
		return 1;
	}
	else if(cube[1].color != cube[4].color && cube[3].color != cube[4].color && cube[5].color != cube[4].color && cube[7].color != cube[4].color)
	{
		return 2;
	}

	while(cube[3].color != cube[4].color)
	{
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}

	if(cube[7].color == cube[4].color)
	{
		rotateHelper(cube, faceNum, color, indexMode, i, LEFT);
	}

	if(cube[1].color == cube[4].color && cube[3].color == cube[4].color)
	{
		return 3;
	}
	else if(cube[3].color == cube[4].color && cube[5].color == cube[4].color)
	{
		return 4;
	}
	return 0;
}

void solveYellowCross(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int state;

	while(checkYellowCross(cube, faceNum, color, indexMode, i) == false)
	{
		state = getYellowCrossState(cube, faceNum, color, indexMode, i);

		switch(state)
		{
			case 1:
				break;
			case 2:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				break;
			case 3:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				break;
			case 4:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				break;
		}
	}
}

Bool checkYellowCross(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[7].color != cube[4].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}

int getYellowCornerState(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	int yellowCornerCount = 0;
	for(j = 0; j < 4; j++)
	{
		if(cube[8].color == cube[4].color)
		{
			yellowCornerCount++;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	switch(yellowCornerCount)
	{
		case 0:
			return 1;
		case 1:
			return 2;
		case 2:
			return 3;
	}
	return 0;
}

void solveYellowCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	while(checkYellowCorners(cube, faceNum, color, indexMode, i) == false)
	{
		switch(getYellowCornerState(cube, faceNum, color, indexMode, i))
		{
			case 1:
				while(cube[11].color != cube[4].color)
				{
					rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
				}
				break;
			case 2:
				while(cube[6].color != cube[4].color)
				{
					rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
				}
				break;
			case 3:
				while(cube[18].color != cube[4].color)
				{
					rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
				}
				break;
		}

		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
	}
}

Bool checkYellowCorners(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[8].color != cube[4].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}

int getYellowCornersPosition(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j, k;
	
	for(j = 0; j < 4; j++)
	{
		for(k = 0; k < 4; k++)
		{
			if(checkYellowCornersPosition(cube, faceNum, color, indexMode, i) == true)
			{
				return 4;
			}
			else if((cube[9].color == cube[13].color && cube[36].color == cube[40].color) && (cube[29].color == cube[31].color && cube[38].color == cube[40].color))
			{
				return 1;
			}
			else if((cube[9].color == cube[13].color && cube[36].color == cube[40].color) && (cube[20].color == cube[22].color && cube[27].color == cube[31].color))
			{
				return 2;
			}
			else if((cube[29].color == cube[31].color && cube[38].color == cube[40].color) && (cube[11].color == cube[13].color && cube[18].color == cube[22].color))
			{
				return 3;
			}

			rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
		}
		movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);	
	}
	return 0;
}

void positionYellowCorners(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	while(checkYellowCornersPosition(cube, faceNum, color, indexMode, i) == false)
	{
		switch(getYellowCornersPosition(cube, rowNum, faceNum, color, indexMode, i))
		{
			case 1:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				break;
			case 2:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);

				rotateHelper(cube, faceNum, color, indexMode, i, LEFT);

				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);

				rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);

				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				break;
			case 3:
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);

				rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);

				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);

				rotateHelper(cube, faceNum, color, indexMode, i, LEFT);

				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 5, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, true);
				break;
			case 4:
				break;
		}
	}
}

Bool checkYellowCornersPosition(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[20].color != cube[22].color || cube[27].color != cube[31].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}

void positionYellowEdges(Square* cube, int** rowNum, int** faceNum, Color* color, Bool indexMode, int* i)
{
	while(checkYellowEdgesPosition(cube, faceNum, color, indexMode, i) == false)
	{
		if(cube[10].color == cube[13].color || cube[19].color == cube[22].color || cube[28].color == cube[31].color || cube[37].color == cube[40].color)
		{
			if(cube[10].color == cube[13].color)
			{
				rotateHelper(cube, faceNum, color, indexMode, i, LEFT);
			}
			else if(cube[19].color == cube[22].color)
			{
				rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
				rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
			}
			else if(cube[28].color == cube[31].color)
			{
				rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
			}

			while(cube[10].color != cube[13].color || cube[19].color != cube[22].color || cube[28].color != cube[31].color || cube[37].color != cube[40].color)
			{
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
				movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			}
		}
		else
		{
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, true);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 0, true);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 1, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 2, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
			movementHelper(cube, rowNum, faceNum, color, indexMode, i, 4, false);
		}
	}
}

Bool checkYellowEdgesPosition(Square* cube, int** faceNum, Color* color, Bool indexMode, int* i)
{
	int j;
	for(j = 0; j < 4; j++)
	{
		if(cube[19].color != cube[22].color)
		{
			return false;
		}
		rotateHelper(cube, faceNum, color, indexMode, i, RIGHT);
	}
	return true;
}
