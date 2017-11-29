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
#include <ctype.h>
#include <time.h>
#include <omp.h>

//함수 정의 헤더파일
#include "Function_Define.h"

//구조체 정의 헤더파일
#include "Struct_Define.h"

void main(int argc, char **argv) {
	int frontClock = clock();

	//인자로 받은 문자열 저장
	char *originwordToFind = (char *)calloc(sizeof(char), 1);
	for (int i = 1; i < argc; i++) {
		originwordToFind = (char *)realloc(originwordToFind, _msize(originwordToFind) + strlen(argv[i]));
		strcat(originwordToFind, argv[i]);

		if (i != argc - 1) {
			originwordToFind = (char *)realloc(originwordToFind, _msize(originwordToFind) + sizeof(char));
			strcat(originwordToFind, " ");
		}
	}
	//문자열 소문자화
	char *wordToFind = (char *)calloc(strlen(originwordToFind), 1);
	strcpy(wordToFind, originwordToFind);
	for (int i = 0; i < strlen(wordToFind); i++) {
		if (isupper(wordToFind[i])) {
			wordToFind[i] = tolower(wordToFind[i]);
		}
	}

	fData **freqData = NULL;
	char **fileList = (char **)calloc(sizeof(char *), 1);
	char *tempFileName = NULL;
	int fileCount = 0;


	printf("Word to search: \"%s\"\n\n", originwordToFind);
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
	nameSort(freqData);

	for (int k = 0; k < _msize(freqData) / sizeof(fData *); k++) {
		//만약 출현빈도가 0이면 거기서부터는 출력 안함.
		if (freqData[k]->frequency == 0) {
			break;
		}
		else {
			printf("%d. %s: Frequency: %d\n", k + 1, fileList[(freqData[k]->order - 1)], freqData[k]->frequency);
		}
	}

	free(originwordToFind);
	//free(wordToFind);
	free(fileList);
	free(tempFileName);

	int rearClock = clock();
	printf("경과시간: %.3lf초\n", ((double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC));	//시간측정이 잘 안나온다.

	system("pause");
	return;
}