#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"

int main(void)
{
	Square* cube = malloc(sizeof(Square)*54);
	Color* color = malloc(sizeof(Color)*12);
	int** faceNum = NULL;
	int** rowNum = NULL;
	char** name = NULL;

	system("clear");

	cube = buildCube(cube);
	faceNum = fillFaceNum(faceNum);
	rowNum = fillRowNum(rowNum);
	name = fillName(name);

	printRubiks(cube, false);

	saveMenu(cube, rowNum, faceNum, color, name);

	clearHome();
	printf("Thanks for playing rubiks!\n");
	clearMenu();

	freeIntArr(faceNum, 6);
	freeIntArr(rowNum, 6);
	freeCharArr(name, 3);
	free(color);
	free(cube);

	return(0);
}
