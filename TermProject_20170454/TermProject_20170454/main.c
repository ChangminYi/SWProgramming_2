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
#include <ctype.h>
#include <time.h>
#include <omp.h>

//�Լ� ���� �������
#include "Function_Define.h"

//����ü ���� �������
#include "Struct_Define.h"

void main(int argc, char **argv) {
	int frontClock = clock();

	//���ڷ� ���� ���ڿ� ����
	char *originwordToFind = (char *)calloc(sizeof(char), 1);
	for (int i = 1; i < argc; i++) {
		originwordToFind = (char *)realloc(originwordToFind, _msize(originwordToFind) + strlen(argv[i]));
		strcat(originwordToFind, argv[i]);

		if (i != argc - 1) {
			originwordToFind = (char *)realloc(originwordToFind, _msize(originwordToFind) + sizeof(char));
			strcat(originwordToFind, " ");
		}
	}
	//���ڿ� �ҹ���ȭ
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
		//���� �����󵵰� 0�̸� �ű⼭���ʹ� ��� ����.
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
	printf("����ð�: %.3lf��\n", ((double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC));	//�ð������� �� �ȳ��´�.

	system("pause");
	return;
}