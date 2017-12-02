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
//��ġ�� Ƚ�� ����
//�������� (������ ����), ��������(�̸� ����) ���
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
	long frontClock = clock();	//�ʱ�ð�

	system("cls");

	//���ڷ� ���� ���ڿ� ����
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

	long searchTime = clock();	//���� Ž������ �ɸ� �ð�

	freqData = sortStruct(fileAnalyze(fileList, wordToFind, fileCount), 0, fileCount - 1);
	nameSort(freqData);

	extern analyzeTime;			//�м��� �ɸ� �ð�
	long sortTime = clock();	//���Ŀ� �ɸ� �ð�

	if (freqData[0]->frequency != 0) {
		for (int k = 0; k < _msize(freqData) / sizeof(fData *); k++) {
			//���� �����󵵰� 0�̸� �ű⼭���ʹ� ��� ����.
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

	long rearClock = clock();	//��� �� �������� �ɸ� �ð�

	printf("��ü ����ð�: %.3lf��\n", (double)(rearClock - frontClock) / (double)CLOCKS_PER_SEC);
	printf("���� Ž�� ����ð�: %.3lf��\n", (double)(searchTime - frontClock) / (double)CLOCKS_PER_SEC);
	printf("���� �м� ����ð�: %.3lf��\n", (double)(analyzeTime - searchTime) / (double)CLOCKS_PER_SEC);
	printf("������ ���� ����ð�: %.3lf��\n", (double)(sortTime - analyzeTime) / (double)CLOCKS_PER_SEC);
	printf("��� �� ���� ����ð�: %.3lf��\n", (double)(rearClock - sortTime) / (double)CLOCKS_PER_SEC);

	system("pause");
	return;
}