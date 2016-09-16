#include <stdlib.h>
#include "rubiks.h"

void movements(Square* cube, int* rowNum, int* faceNum, Color* color, int face, Bool inverted)
{
	Direction rowDir;
	Direction faceDir;

	switch(face)
	{
		//Left face
		case 0:
			//Clockwise
			if(inverted == false)
			{
				rowDir = DOWN;
				faceDir = UP;
			}
			//Inverted
			else
			{
				rowDir = UP;
				faceDir = DOWN;
			}
			break;

		//Right face
		case 1:
			//Clockwise
			if(inverted == false)
			{
				rowDir = UP;
				faceDir = UP;
			}
			//Inverted
			else
			{
				rowDir = DOWN;
				faceDir = DOWN;
			}
			break;

		//Up face
		case 2:
			//Clockwise
			if(inverted == false)
			{
				rowDir = UP;
				faceDir = UP;
			}
			//Inverted
			else
			{
				rowDir = DOWN;
				faceDir = DOWN;
			}
			break;

		//Down face
		case 3:
			//Clockwise
			if(inverted == false)
			{
				rowDir = DOWN;
				faceDir = UP;
			}
			//Inverted
			else
			{
				rowDir = UP;
				faceDir = DOWN;
			}
			break;

		//Front face
		case 4:
			//Clockwise
			if(inverted == false)
			{
				rowDir = DOWN;
				faceDir = UP;
			}
			//Inverted
			else
			{
				rowDir = UP;
				faceDir = DOWN;
			}
			break;

		//Back face
		case 5:
			//Clockwise
			if(inverted == false)
			{
				rowDir = UP;
				faceDir = DOWN;
			}
			//Inverted
			else
			{
				rowDir = DOWN;
				faceDir = UP;
			}
			break;
	}
	rotateSide(cube, rowNum, color, rowDir);
	rotateFace(cube, faceNum, color, faceDir);
}

void rotateCube(Square* cube, int** faceNum, Color* color, Direction direction)
{
	switch(direction)
	{
		case UP:
			rotateFace(cube, faceNum[0], color, DOWN);
			rotateFace(cube, faceNum[1], color, UP);
			swapFaces(cube, faceNum, color, 2, 3);
			swapFaces(cube, faceNum, color, 2, 4);
			swapFaces(cube, faceNum, color, 3, 5);
			reflectFaceOverX(cube, faceNum[3]);
			reflectFaceOverX(cube, faceNum[5]);
			break;
		case DOWN:
			rotateFace(cube, faceNum[0], color, UP);
			rotateFace(cube, faceNum[1], color, DOWN);
			swapFaces(cube, faceNum, color, 4, 5);
			swapFaces(cube, faceNum, color, 2, 4);
			swapFaces(cube, faceNum, color, 3, 5);
			reflectFaceOverX(cube, faceNum[2]);
			reflectFaceOverX(cube, faceNum[5]);
			break;
		case LEFT:
			rotateFace(cube, faceNum[2], color, UP);
			rotateFace(cube, faceNum[3], color, DOWN);
			swapFaces(cube, faceNum, color, 0, 1);
			swapFaces(cube, faceNum, color, 0, 4);
			swapFaces(cube, faceNum, color, 1, 5);
			reflectFaceOverY(cube, faceNum[1]);
			reflectFaceOverY(cube, faceNum[5]);
			break;
		case RIGHT:
			rotateFace(cube, faceNum[2], color, DOWN);
			rotateFace(cube, faceNum[3], color, UP);
			swapFaces(cube, faceNum, color, 4, 5);
			swapFaces(cube, faceNum, color, 0, 4);
			swapFaces(cube, faceNum, color, 1, 5);
			reflectFaceOverY(cube, faceNum[0]);
			reflectFaceOverY(cube, faceNum[5]);
			break;
	}
}

void reflectFaceOverY(Square* cube, int* faceNum)
{
	swapColor(cube, faceNum[0], faceNum[2]);
	swapColor(cube, faceNum[3], faceNum[7]);
	swapColor(cube, faceNum[4], faceNum[6]);
}

void reflectFaceOverX(Square* cube, int* faceNum)
{
	swapColor(cube, faceNum[0], faceNum[6]);
	swapColor(cube, faceNum[1], faceNum[5]);
	swapColor(cube, faceNum[2], faceNum[4]);
}

void swapColor(Square* cube, int swapOne, int swapTwo)
{
	Color swap;

	swap = cube[swapOne].color;
	cube[swapOne].color = cube[swapTwo].color;
	cube[swapTwo].color = swap;
}

void swapFaces(Square* cube, int** faceNum, Color* color, int faceOne, int faceTwo)
{
	int i;
	color = fillFaceColor(cube, color, faceNum[faceOne]);
	for(i = 0; i < 9; i++)
	{
		cube[faceNum[faceOne][i]].color = cube[faceNum[faceTwo][i]].color;
	}
	for(i = 0; i < 9; i++)
	{
		cube[faceNum[faceTwo][i]].color = color[i];
	}
}

void rotateFace(Square* cube, int* faceNum, Color* color, Direction direction)
{
	int i, j;

	color = fillFaceColor(cube, color, faceNum);

	if(direction == UP)
	{
		j = 6;
	}
	else
	{
		j = 2;
	}

	for(i = 0; i < 8; i++)
	{
		cube[faceNum[i]].color = color[j];

		if(j != 7)
		{
			j++;
		}
		else
		{
			j = 0;
		}

	}
}

void rotateSide(Square* cube, int* rowNum, Color* color, Direction direction)
{
	int i, j;

	color = fillSideColor(cube, color, rowNum);

	if(direction == UP)
	{
		j = 3;
	}
	else
	{
		j = 9;
	}

	for(i = 0; i < 12; i++)
	{
		cube[rowNum[i]].color = color[j];

		if(j != 11)
		{
			j++;
		}
		else
		{
			j = 0;
		}
	}
}

Color* fillFaceColor(Square* cube, Color* color, int* faceNum)
{
	int i;

	for(i = 0; i < 9; i++)
	{
		color[i] = cube[faceNum[i]].color;
	}

	return color;
}

Color* fillSideColor(Square* cube, Color* color, int* rowNum)
{
	int i;

	for(i = 0; i < 12; i++)
	{
		color[i] = cube[rowNum[i]].color;
	}

	return color;
}
