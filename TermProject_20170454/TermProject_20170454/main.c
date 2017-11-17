/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW프로그래밍(2) Term Project
		20170454 이창민
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

////	프로그램 개요
//FindFirstFile, FindNextFile 사용하여 파일 탐색
//파일 이름 문자열로 저장
//파일 하나하나 열어서 문자열 탐색 (여기서 스레드 사용 가능성)
//기준 정하여 산출한 결과 저장
//퀵소트 혹은 래딕스소트로 정렬 (효율 좋은 정렬 알고리즘 선택)
//출력 (puts 가 printf에 비해 더 빠르다.)

#define _CRT_SECURE_NO_WARNINGS

//헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>			//for 시간측정
//#include <Windows.h>		//for 파일 탐색
//#include <process.h>		//for 스레드 사용
#include "Function_Define.h"


void main(char *argv) {
	char *wordToFind = (char *)calloc(strlen(argv), sizeof(char));
	strcpy(wordToFind, argv);

	char **fileList = NULL;
	char *fileName = NULL;
	int frontClock, rearClock;

	frontClock = clock();
	do {
		fileName = SearchFile();

		if (fileName != NULL) {
			puts(fileName);
		}
	} while (fileName != NULL);
	rearClock = clock();

	printf("경과시간: %.3lf초\n", (double)(rearClock - frontClock) / CLOCKS_PER_SEC);

	system("pause");
	return;
}