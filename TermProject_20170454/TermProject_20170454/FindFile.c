#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "Function_Define.h"

HWND fileHandle;
BOOL prev_operated = FALSE;
WIN32_FIND_DATA tF, *tempFile = &tF;
char prevTempName[100] = { 0 };

char *SearchFile() {
	if (prev_operated == FALSE) {
		fileHandle = FindFirstFile("dataset\\*.txt", tempFile);

		if (fileHandle == INVALID_HANDLE_VALUE) {
			puts("There is no file.");

			return NULL;
		}
		else {
			prev_operated = TRUE;
			strcpy(prevTempName, tempFile->cFileName);

			return tempFile->cFileName;
		}
	}
	else {
		FindNextFile(fileHandle, tempFile);

		if (!strcmp(prevTempName, tempFile->cFileName)) {
			FindClose(fileHandle);

			return NULL;
		}
		else {
			strcpy(prevTempName, tempFile->cFileName);

			return tempFile->cFileName;
		}
	}
}
