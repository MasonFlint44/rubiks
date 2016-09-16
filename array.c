#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubiks.h"

int** fillFaceNum(int** faceNum)
{
	int faceArr[9] = {0, 1, 2, 5, 8, 7, 6, 3, 4};
	faceNum = malloc(sizeof(int*)*6);
	int faceId;
	int i, j;

	for(i = 0; i < 6; i++)
	{
		faceNum[i] = malloc(sizeof(int)*9);

		switch(i)
		{
			case 0: faceId = 1; break;
			case 1: faceId = 3; break;
			case 2: faceId = 0; break;
			case 3: faceId = 5; break;
			case 4: faceId = 2; break;
			case 5: faceId = 4;; break;
		}

		for(j = 0; j < 9; j++)
		{
			faceNum[i][j] = (faceArr[j] + (faceId * 9));
		}
	}

	return faceNum;
}

int** fillRowNum(int** rowNum)
{
	int rowArr[6][12] = {	
							{0, 3, 6, 18, 21, 24, 45, 48, 51, 42, 39, 36},
							{2, 5, 8, 20, 23, 26, 47, 50, 53, 44, 41, 38},
							{9, 10, 11, 18, 19, 20, 27, 28, 29, 38, 37, 36},
							{15, 16, 17, 24, 25, 26, 33, 34, 35, 44, 43, 42},
							{6, 7, 8, 27, 30, 33, 47, 46, 45, 17, 14, 11},
							{0, 1, 2, 29, 32, 35, 53, 52, 51, 15, 12, 9}
						};
	rowNum = malloc(sizeof(int*)*6);
	int i, j;

	for(i = 0; i < 6; i++)
	{
		rowNum[i] = malloc(sizeof(int)*12);

		for(j = 0; j < 12; j++)
		{
			rowNum[i][j] = rowArr[i][j];
		}
	}

	return rowNum;
}

char** fillName(char** name)
{
	char filename[] = "save0.txt";
	FILE* fp;
	int i;
	name = malloc(sizeof(char*)*3);

	for(i = 0; i < 3; i++)
	{
		name[i] = malloc(sizeof(char)*11);
		filename[4] = (i+1) + '0';

		fp = fopen(filename, "r");

		if(fp == NULL)
		{
			strcpy(name[i], "EMPTY");
		}
		else
		{
			fscanf(fp, "%s", name[i]);
		}

		fclose(fp);
	}

	return name;
}

void freeIntArr(int** arr, int index)
{
	int i;
	for(i = 0; i < index; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

void freeCharArr(char** arr, int index)
{
	int i;
	for(i = 0; i < index; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
