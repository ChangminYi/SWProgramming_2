#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996) //strnicmp() �Լ� ����� ���� ��� ����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <omp.h>	//for ��Ƽ������


//�˻��� ���� ������ ����ü
#include "Struct_Define.h"

//���� ���� ����, ������ ���� �˻�
char **dataSearch(char **fileName, int order);
int wordSearch(char **sentence, char *wordToFind, int threadNumber);
int **dataAnalyze(char **fileName, char *toFind);

//�ð������� ���� ����
int analyzeTime;

//����ü�� ����, ���� ��Ƽ� ��ȯ
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

	analyzeTime = clock();

	return AnalyzedFile;
}

int **dataAnalyze(char **fileName, char *toFind) {
	char **data = NULL;
	int numThread = omp_get_num_threads();

	int **wordFindCount = (int **)calloc(sizeof(int *), _msize(fileName) / sizeof(char *));
	for (int i = 0; i < _msize(fileName) / sizeof(char *); i++) {
		wordFindCount[i] = (int *)malloc(sizeof(int));
		data = dataSearch(fileName, i);
		wordFindCount[i] = wordSearch(data, toFind, numThread);
	}

	free(data);
	return wordFindCount;
}

char **dataSearch(char **fileName, int order) {
	char sentenceTemp[1000] = { 0 };	//����
	//���� ��� �� �̸� ����
	char *fileLoc = (char *)calloc(strlen("dataset\\")+strlen(fileName[order]), 1);
	strcpy(fileLoc, "dataset\\");
	strcat(fileLoc, fileName[order]);

	//���� ���� ����ó��
	FILE *tempfp = fopen(fileLoc, "r");
	if (tempfp == NULL) {
		puts("File open error.");
		return 0;
	}

	//���� ������ ����
	fseek(tempfp, 0, SEEK_END);
	long fileSize = ftell(tempfp);
	fseek(tempfp, 0, SEEK_SET);

	char **tempData = (char **)calloc(1, sizeof(char *));
	int sentenceCount = 0;
	do {
		fgets(sentenceTemp, sizeof(sentenceTemp), tempfp);

		//���� ����
		tempData = (char **)realloc(tempData, sizeof(char *) * (sentenceCount + 2));
		tempData[sentenceCount] = (char *)calloc(sizeof(char), strlen(sentenceTemp) + 1);
		strcpy(tempData[sentenceCount++], sentenceTemp);
	} while (!feof(tempfp));

	fclose(tempfp);

	return tempData;
}

int wordSearch(char **sentence, char *wordToFind, int threadNumber) {
	int count = 0;
	int loopCount = _msize(sentence) / sizeof(char *);

	//openMP ���
	omp_set_num_threads(threadNumber);
#pragma omp parallel for
	for (int j = 0; j < loopCount - 2; j++) {
		for (int i = 0; i < strlen(sentence[j]) - strlen(wordToFind); i++) {
			if (strlen(sentence[j]) < strlen(wordToFind)) {
				break;
			}
			if (!strnicmp(sentence[j] + i, wordToFind, strlen(wordToFind))) {
				count++;
			}
		}
	}

	return count;
}
