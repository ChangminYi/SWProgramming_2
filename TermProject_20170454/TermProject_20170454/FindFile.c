#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "Function_Define.h"

WIN32_FIND_DATA tempFile;	//찾은 파일 정보 저장
char prevTempName[100] = { 0 };	//바로 앞의 탐색에서 찾았던 파일

char *SearchFile() {
	static HWND fileHandle;		//파일 탐색 핸들
	static BOOL prev_operated = FALSE;		//처음 실행인지 아닌지 구분

	if (prev_operated == FALSE) {
		fileHandle = FindFirstFile("dataset\\*.txt", &tempFile);

		if (fileHandle == INVALID_HANDLE_VALUE) {
			puts("There is no file.");

			return NULL;
		}
		else {
			prev_operated = TRUE;
			strcpy(prevTempName, &tempFile.cFileName);

			return &tempFile.cFileName;
		}
	}
	else {
		FindNextFile(fileHandle, &tempFile);

		if (!strcmp(prevTempName, &tempFile.cFileName)) {
			FindClose(fileHandle);

			return NULL;
		}
		else {
			strcpy(prevTempName, &tempFile.cFileName);

			return &tempFile.cFileName;
		}
	}
}
