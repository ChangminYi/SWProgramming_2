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
//일치한 횟수 저장
//병합정렬 (데이터 정렬), 버블정렬(이름 정렬) 사용
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
	long frontClock = clock();	//초기시간

	system("cls");

	//인자로 받은 문자열 저장
	char *wordToFind = (char *)calloc(sizeof(char), 1);
	for (int i = 1; i < argc; i++) {
		wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + strlen(argv[i]));
		strcat(wordToFind, argv[i]);

		if (i != argc - 1) {
			wordToFind = (char *)realloc(wordToFind, _msize(wordToFind) + sizeof(char));
			strcat(wordToFind, " ");
		}
	}


	fData **freqData = NULL;
	char **fileList = (char **)calloc(sizeof(char *), 1);
	char *tempFileName = NULL;
	int fileCount = 0;


	printf("Word to search: \"%s\"\n\n", wordToFind);
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

	long searchTime = clock();	//파일 탐색까지 걸린 시간

	freqData = sortStruct(fileAnalyze(fileList, wordToFind, fileCount), 0, fileCount - 1);
	nameSort(freqData);

	extern analyzeTime;			//분석에 걸린 시간
	long sortTime = clock();	//정렬에 걸린 시간

	if (freqData[0]->frequency != 0) {
		for (int k = 0; k < _msize(freqData) / sizeof(fData *); k++) {
			//만약 출현빈도가 0이면 거기서부터는 출력 안함.
			if (freqData[k]->frequency == 0) {
				break;
			}
			else {
				printf("%4d. %16s\n\tFrequency: %4d\n\n", k + 1, fileList[(freqData[k]->order - 1)], freqData[k]->frequency);
			}
		}
	}
	else {
		printf("There is no \"%s\" in files\n.", wordToFind);
	}

	free(wordToFind);
	free(fileList);
	free(tempFileName);

	long rearClock = clock();	//출력 후 정리까지 걸린 시간

	printf("전체 경과시간: %.3lf초\n", (double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC);
	printf("파일 탐색 경과시간: %.3lf초\n", (double)(searchTime - frontClock) / (double)CLOCKS_PER_SEC);
	printf("파일 분석 경과시간: %.3lf초\n", (double)(analyzeTime - searchTime) / (double)CLOCKS_PER_SEC);
	printf("데이터 정렬 경과시간: %.3lf초\n", (double)(sortTime - analyzeTime) / (double)CLOCKS_PER_SEC);
	printf("출력 및 정리 경과시간: %.3lf초\n", (double)(rearClock - sortTime) / (double)CLOCKS_PER_SEC);

	system("pause");
	return;
}