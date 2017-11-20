/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW���α׷���(2) Term Project
		20170454 ��â��
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

/*		���α׷� ����		*/
//FindFirstFile, FindNextFile ����Ͽ� ���� Ž��
//���� �̸� ���ڿ��� ����
//���� �ϳ��ϳ� ��� ���ڿ� Ž�� (��Ƽ������(openMP) ���)
//���� ���Ͽ� ������ ��� ����
//����Ʈ Ȥ�� ���񽺼�Ʈ�� ���� (����Ʈ ���)
//���

#define _CRT_SECURE_NO_WARNINGS

//�⺻ �������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//�Լ� ���� �������
#include "Function_Define.h"

//����ü ���� �������
#include "Struct_Define.h"

void main(int argc, char **argv) {
	int frontClock = clock();

	//���ڷ� ���� ���ڿ� ����
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
	printf("����ð�: %lf��\n", ((double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC));	//�ð������� �� �ȳ��´�.

	system("pause");
	return;
}