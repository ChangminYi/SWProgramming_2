#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996) //strnicmp() 함수 사용을 위한 경고 무시

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <omp.h>	//for 멀티스레드


//검사한 내용 저장할 구조체
#include "Struct_Define.h"

//파일 정보 복사, 복사한 내용 검사
char **dataSearch(char **fileName, int order);
int wordSearch(char **sentence, char *wordToFind, int threadNumber);
int **dataAnalyze(char **fileName, char *toFind);

//시간측정을 위한 변수
int analyzeTime;

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
	char sentenceTemp[1000] = { 0 };	//버퍼
	//파일 경로 및 이름 설정
	char *fileLoc = (char *)calloc(strlen("dataset\\")+strlen(fileName[order]), 1);
	strcpy(fileLoc, "dataset\\");
	strcat(fileLoc, fileName[order]);

	//파일 열기 예외처리
	FILE *tempfp = fopen(fileLoc, "r");
	if (tempfp == NULL) {
		puts("File open error.");
		return 0;
	}

	//파일 사이즈 측정
	fseek(tempfp, 0, SEEK_END);
	long fileSize = ftell(tempfp);
	fseek(tempfp, 0, SEEK_SET);

	char **tempData = (char **)calloc(1, sizeof(char *));
	int sentenceCount = 0;
	do {
		fgets(sentenceTemp, sizeof(sentenceTemp), tempfp);

		//정보 복사
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

	//openMP 사용
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
