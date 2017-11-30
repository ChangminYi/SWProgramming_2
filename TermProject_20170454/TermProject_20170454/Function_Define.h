#pragma once
#include "Struct_Define.h"

//FindFile.c
	char *SearchFile();

//analyzeFile.c
	fData **fileAnalyze(char **fileName, char *toFind, int numFiles);


//QuickSort.c
	fData **sortStruct(fData **data, int Left, int Right);
	void nameSort(fData **data);