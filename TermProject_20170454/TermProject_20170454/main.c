/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW프로그래밍(2) Term Project
		20170454 이창민
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

/*		프로그램 개요		*/
//FindFirstFile, FindNextFile 사용하여 파일 탐색
//파일 이름 문자열로 저장
//파일 하나하나 열어서 문자열 탐색 (멀티스레드(openMP) 사용)
//기준 정하여 산출한 결과 저장
//퀵소트 혹은 래딕스소트로 정렬 (퀵소트 사용)
//출력

#define _CRT_SECURE_NO_WARNINGS

//기본 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//함수 정의 헤더파일
#include "Function_Define.h"

//구조체 정의 헤더파일
#include "Struct_Define.h"

void main(int argc, char **argv) {
	int frontClock = clock();

	//인자로 받은 문자열 저장
	char *wordToFind = (char *)calloc(sizeof(char), 1);
	{
		for (int i = 1; i < argc; i++) {
			wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + strlen(argv[i]));
			strcat(wordToFind, argv[i]);

			if (i != argc - 1) {
				wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + sizeof(char));
				strcat(wordToFind, " ");
			}
		}
	}

	fData **freqData = NULL;
	char **fileList = (char **)calloc(sizeof(char *), 1);
	char *tempFileName = NULL;
	int fileCount = 0;


	printf("Word to search: %s\n\n", wordToFind);
	for (;;) {
		tempFileName = SearchFile();

		if (tempFileName != NULL) {
			fileList = (char **)realloc(fileList, sizeof(char *) * (fileCount + 1));
			fileList[fileCount] = (char *)calloc(strlen(tempFileName), sizeof(char));
			strcpy(fileList[fileCount++], tempFileName);
		}
		else {
			break;
		}
	}
	if (fileList[0] == NULL) {
		return;
	}

	freqData = sortStruct(fileAnalyze(fileList, wordToFind, fileCount), 0, fileCount - 1);
	for (int k = 0; k < _msize(freqData) / sizeof(fData *); k++) {
		printf("FileName: %s, Order: %d, Frequency: %d\n", fileList[(freqData[k]->order - 1)], freqData[k]->order, freqData[k]->frequency);;
	}

	free(wordToFind);
	free(fileList);
	free(tempFileName);

	int rearClock = clock();
	printf("경과시간: %lf초\n", ((double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC));	//시간측정이 잘 안나온다.

	system("pause");
	return;
}