#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubiks.h"
#include "color.h"

int saveFile(Square* cube, char* name, Bool indexMode, int slotNum)
{
	char filename[] = "save0.txt";
	filename[4] = slotNum + '0';

	FILE* fp = fopen(filename, "w");

	if(fp == NULL)
	{
		printf(HOME);
		clearLine();
		printf(HOME);
		printf(KRED("Error: ")"Save file could not be written\n");
	}

	char colorArr[54];
	int i;

	for(i = 0; i < sizeof(colorArr); i++)
	{
		colorArr[i] = cube[i].color + '0';
	}

	if(0 > fprintf(fp, "%s %d %s", name, indexMode, colorArr))
	{
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}

int loadFile(Square* cube, char* name, Bool* indexMode, int slotNum)
{
	char filename[] = "save0.txt";
	filename[4] = slotNum + '0';

	FILE* fp = fopen(filename, "r");

	if(fp == NULL)
	{
		printf(HOME);
		clearLine();
		printf(HOME);
		printf(KRED("Error: ")"Save file could not be read\n");
		return -1;
	}

	char colorArr[54];
	char color[2] = "0";
	int i;

	fscanf(fp, "%s %d %s", name, (int*)indexMode, colorArr);

	for(i = 0; i < sizeof(colorArr); i++)
	{
		color[0] = colorArr[i];
		cube[i].color = (int)strtol(color, NULL, 10);
	}

	fclose(fp);
	return 0;
}
