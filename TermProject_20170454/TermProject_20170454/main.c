/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW���α׷���(2) Term Project
		20170454 ��â��
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

/*		���α׷� ����		*/
//FindFirstFile, FindNextFile ����Ͽ� ���� Ž��
//���� �̸� ���ڿ��� ����
//���� �ϳ��ϳ� ��� ���ڿ� Ž�� (���⼭ ������ ��� ���ɼ�)
//���� ���Ͽ� ������ ��� ����
//����Ʈ Ȥ�� ���񽺼�Ʈ�� ���� (ȿ�� ���� ���� �˰��� ����)
//��� (puts �� printf�� ���� �� ������.)

#define _CRT_SECURE_NO_WARNINGS

//�⺻ �������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//�Լ� ���� �������
#include "Function_Define.h"

void main(int argc, char **argv) {
	char *wordToFind = (char *)calloc(sizeof(char), 1);
	{//���ڷ� ���� ���ڿ� ����
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

	printf("����ð�: %lf��\n", (double)((rearClock - frontClock) / CLOCKS_PER_SEC));

	free(wordToFind);
	free(fileList);
	free(tempFileName);

	system("pause");
	return;
}