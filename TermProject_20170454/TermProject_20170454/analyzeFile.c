#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>	//for 멀티스레드

#define NUMBER_OF_THREAD 4

//파일 정보 복사, 복사한 내용 검사
char **dataSearch(char **fileName, int order);
int wordSearch(char **sentence, char *wordToFind);
int **dataAnalyze(char **fileName, char *toFind);

//검사한 내용 저장할 구조체
#include "Struct_Define.h"

//구조체에 순서, 정보 담아서 반환
fData **fileAnalyze(char **fileName, char *toFind, int numFiles) {
	fData **AnalyzedFile = (fData **)calloc(sizeof(fData), numFiles);
	for (int i = 0; i < numFiles; i++) {
		AnalyzedFile[i] = (fData *)malloc(sizeof(fData));
	}

	int **freqData = dataAnalyze(fileName, toFind);

	for (int i = 0; i < numFiles; i++) {
		AnalyzedFile[i]->order = i + 1;
		AnalyzedFile[i]->frequency = freqData[i];
	}

	return AnalyzedFile;
}

int **dataAnalyze(char **fileName, char *toFind) {
	char **data = NULL;
	char *toFindTest = "Computer";

	int **wordFindCount = (int **)calloc(sizeof(int *), _msize(fileName) / sizeof(char *));
	for (int i = 0; i < _msize(fileName) / sizeof(char *); i++) {
		wordFindCount[i] = (int *)malloc(sizeof(int));
		data = dataSearch(fileName, i);
		wordFindCount[i] = wordSearch(data, toFindTest);
	}

	free(data);
	return wordFindCount;
}

char **dataSearch(char **fileName, int order) {
	char sentenceTemp[1000] = { 0 };
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

	char **tempData = (char **)calloc(1, sizeof(char *));
	int sentenceCount = 0;
	do {
		fgets(sentenceTemp, sizeof(sentenceTemp), tempfp);

		tempData = (char **)realloc(tempData, sizeof(char *)*(sentenceCount + 1));
		tempData[sentenceCount] = (char *)calloc(sizeof(char), strlen(sentenceTemp) + 1);
		strcpy(tempData[sentenceCount++], sentenceTemp);
	} while (!feof(tempfp));

	fclose(tempfp);

	return tempData;
}

int wordSearch(char **sentence, char *wordToFind) {
	int count = 0;

	//openMP 사용
	omp_set_num_threads(NUMBER_OF_THREAD);
#pragma omp parallel for
	for (int j = 0; j < _msize(sentence) / sizeof(char *); j++) {
		for (int i = 0; i < _msize(sentence[j]) - strlen(wordToFind); i++) {
			if (strlen(sentence[j]) < strlen(wordToFind)) {
				break;
			}
			if (!strncmp(sentence[j] + i, wordToFind, strlen(wordToFind))) {
				count++;
				i += strlen(wordToFind);
			}
		}
	}

	return count;
}
