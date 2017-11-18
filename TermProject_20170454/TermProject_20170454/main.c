/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW프로그래밍(2) Term Project
		20170454 이창민
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

/*		프로그램 개요		*/
//FindFirstFile, FindNextFile 사용하여 파일 탐색
//파일 이름 문자열로 저장
//파일 하나하나 열어서 문자열 탐색 (여기서 스레드 사용 가능성)
//기준 정하여 산출한 결과 저장
//퀵소트 혹은 래딕스소트로 정렬 (효율 좋은 정렬 알고리즘 선택)
//출력 (puts 가 printf에 비해 더 빠르다.)

#define _CRT_SECURE_NO_WARNINGS

//기본 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//함수 정의 헤더파일
#include "Function_Define.h"

void main(int argc, char **argv) {
	char *wordToFind = (char *)calloc(sizeof(char), 1);
	{//인자로 받은 문자열 저장
		for (int i = 1; i < argc; i++) {
			wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + strlen(argv[i]));
			strcat(wordToFind, argv[i]);

			if (i != argc - 1) {
				wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + sizeof(char));
				strcat(wordToFind, " ");
			}
		}
	}

	char **fileList = (char **)calloc(sizeof(char *), 1);
	char *tempFileName = NULL;
	int frontClock, rearClock;
	int fileCount = 0;

	frontClock = clock();

	printf("Word to search: %s\n\n", wordToFind);
	while (1) {
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

	fileAnalyze(fileList, wordToFind, fileCount);

	rearClock = clock();

	printf("경과시간: %lf초\n", (double)((rearClock - frontClock) / CLOCKS_PER_SEC));

	free(wordToFind);
	free(fileList);
	free(tempFileName);

	system("pause");
	return;
}