/*/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
		SW���α׷���(2) Term Project
		20170454 ��â��
///////////////////////////////////////////////////////
/////////////////////////////////////////////////////*/

////	���α׷� ����
//FindFirstFile, FindNextFile ����Ͽ� ���� Ž��
//���� �̸� ���ڿ��� ����
//���� �ϳ��ϳ� ��� ���ڿ� Ž�� (���⼭ ������ ��� ���ɼ�)
//���� ���Ͽ� ������ ��� ����
//����Ʈ Ȥ�� ���񽺼�Ʈ�� ���� (ȿ�� ���� ���� �˰��� ����)
//��� (puts �� printf�� ���� �� ������.)

#define _CRT_SECURE_NO_WARNINGS

//�������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>			//for �ð�����
//#include <Windows.h>		//for ���� Ž��
//#include <process.h>		//for ������ ���
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

	printf("����ð�: %.3lf��\n", (double)(rearClock - frontClock) / CLOCKS_PER_SEC);

	system("pause");
	return;
}