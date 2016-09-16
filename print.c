#include <stdio.h>
#include <time.h>
#include <string.h>
#include "rubiks.h"
#include "color.h"

void printRubiks(Square* cube, Bool indexMode)
{
	if(indexMode == false)
	{
		printCube(cube);
	}
	else
	{
		printCubeIndex(cube);
	}
}

void printMirrorFace(Square* square, int padding)
{
	int i, j;

	for(i = 2; i < 9; i--)
	{
		switch(i)
		{
			case 2:
			case 5:
			case 8:
				printf("\n\n");
				for(j = 0; j < padding; j++)
				{
					printf("\t");
				}
				break;
		}
		printSquare(square[i]);
		switch(i)
		{
			case 0: i = 6; break;
			case 3: i = 9; break;
			case 6: return;
		}
	}
}

void printMirrorFaceIndex(Square* square, int padding, int sideId)
{
	int index = sideId * 9;
	int i, j;

	for(i = 2; i < 9; i--)
	{
		switch(i)
		{
			case 2:
			case 5:
			case 8:
				printf("\n\n");
				for(j = 0; j < padding; j++)
				{
					printf("\t");
				}
				break;
		}
		printSquareIndex(square[i], index + i);
		switch(i)
		{
			case 0: i = 6; break;
			case 3: i = 9; break;
			case 6: return;
		}
	}
}

void removeNewLine(char* string)
{
	char* swap;
	swap = strrchr(string, '\n');
	if(swap != NULL)
	{
		*swap = '\0';
	}
}

void clearMenu()
{
	int i;
	printf(LFOU);
	for(i = 0; i < 11; i++)
	{
		clearLine();
		printf("\n");
	}
	printf(LFOU);
}

void clearHome()
{
	printf(HOME);
	clearLine();
	printf(HOME);
}

void clearLine()
{
	int i;
	for(i = 0; i < 50; i++)
	{
		printf(" ");
	}
}

char* printBool(Bool bool)
{
	if(bool == true)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

void printCube(Square* cube)
{
	printf(LONE);
	printFace(cube, 2);
	printf(LTWO);
	printFace(cube+9, 0);
	printf(LTWO);
	printFace(cube+18, 2);
	printf(LTWO);
	printFace(cube+27, 4);
	printf(LTWO);
	printMirrorFace(cube+36, 6);
	printf(LTHR);
	printFace(cube+45, 2);
	printf("\n");
}

void printFace(Square* square, int padding)
{
	int i, j;

	for(i = 0; i < 9; i++)
	{
		if(i % 3 == 0)
		{
			printf("\n\n");
			for(j = 0; j < padding; j++)
			{
				printf("\t");
			}
		}
		printSquare(square[i]);
	}
}

void printSquare(Square square)
{
	switch(square.color)
	{
		case WHITE:
			printf(KWHT("  ██"));
			break;
		case GREEN:
			printf(KGRN("  ██"));
			break;
		case RED:
			printf(KRED("  ██"));
			break;
		case BLUE:
			printf(KBLU("  ██"));
			break;
		case ORANGE:
			printf(KMAG("  ██"));
			break;
		case YELLOW:
			printf(KYEL("  ██"));
			break;
		//For invalid colors
		default:
			printf(KCYN("  XX"));
			break;
	}
}

void printCubeIndex(Square* cube)
{
	printf(LONE);
	printFaceIndex(cube, 2, 0);
	printf(LTWO);
	printFaceIndex(cube+9, 0, 1);
	printf(LTWO);
	printFaceIndex(cube+18, 2, 2);
	printf(LTWO);
	printFaceIndex(cube+27, 4, 3);
	printf(LTWO);
	printMirrorFaceIndex(cube+36, 6, 4);
	printf(LTHR);
	printFaceIndex(cube+45, 2, 5);
	printf("\n");
	printf(LFOU);
}

void printFaceIndex(Square* square, int padding, int sideId)
{
	int index = sideId*9;
	int i, j;

	for(i = 0; i < 9; i++)
	{
		if(i % 3 == 0)
		{
			printf("\n\n");
			for(j = 0; j < padding; j++)
			{
				printf("\t");
			}
		}
		printSquareIndex(square[i], index);
		index++;
	}
}

void printSquareIndex(Square square, int index)
{
	switch(square.color)
	{
		case WHITE:
			printf(KWHT(BOLD("  %02d")), index);
			break;
		case GREEN:
			printf(KGRN(BOLD("  %02d")), index);
			break;
		case RED:
			printf(KRED(BOLD("  %02d")), index);
			break;
		case BLUE:
			printf(KBLU(BOLD("  %02d")), index);
			break;
		case ORANGE:
			printf(KMAG(BOLD("  %02d")), index);
			break;
		case YELLOW:
			printf(KYEL(BOLD("  %02d")), index);
			break;
		//For invalid colors
		default:
			printf(KCYN(BOLD("  %02d")), index);
			break;
	}
}

void waitFor(int secs)
{
	int wTime = time(NULL) + secs;

	while(time(NULL) < wTime);
}
