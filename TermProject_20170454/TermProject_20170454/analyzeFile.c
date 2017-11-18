#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

#define NUMBER_OF_THREAD 6

//파일 정보 복사, 복사한 내용 검사
char *dataSearch(char **fileName, int order);
void dataAnalyze(char **fileName, char *toFind, int order);

//검사한 내용 저장할 구조체
#include "Struct_Define.h"

void fileAnalyze(char **fileName, char *toFind, int numFiles) {

	omp_set_num_threads(NUMBER_OF_THREAD);
#pragma omp parallel for
	for (int i = 0; i < numFiles;i++) {
		dataAnalyze(fileName, toFind, i);
	}
}

void dataAnalyze(char **fileName, char *toFind, int order) {
	/*char *tempLocationFind = NULL;

	char *data = dataSearch(fileName, order);
	do {
		tempLocationFind = strstr(data, "computer");
	} while (tempLocationFind != NULL);
	*/
}

char *dataSearch(char **fileName, int order) {
	char *fileLoc = (char *)calloc(strlen("dataset\\")+strlen(fileName[order]), 1);
	strcpy(fileLoc, "dataset\\");
	strcat(fileLoc, fileName[order]);

	FILE *tempfp = fopen(fileLoc, "r");
	if (tempfp == NULL) {
		puts("File open error.");
		return 0;
	}

	fseek(tempfp, 0, SEEK_END);
	long fileSize = ftell(tempfp);
	fseek(tempfp, 0, SEEK_SET);

	char *tempData = (char *)calloc(fileSize, sizeof(char) + 1);
	char *tempData2 = (char *)calloc(fileSize, sizeof(char));
	do {
		fgets(tempData2, fileSize, tempfp);
		strcat(tempData, tempData2);
	} while (!feof(tempfp));

	free(tempData2);
	fclose(tempfp);

	return tempData;
}