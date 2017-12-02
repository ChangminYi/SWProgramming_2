#include <stdio.h>
#include <stdlib.h>
#include "Function_Define.h"
#include "Struct_Define.h"

//병합정렬 시 사용할 임시 메모리
fData **sortTemp = NULL;

void mergesort(fData **arg, int l, int r);
void merge(fData **arg, int l, int m, int r);

//병합정렬 (퀵소트는 도저히 짤 수가 없었음)
fData **sortStruct(fData **data, int Left, int Right) {

	sortTemp = (fData **)malloc(_msize(data));
	mergesort(data, 0, _msize(data) / sizeof(fData **) - 1);

	free(sortTemp);
	return data;
}

void mergesort(fData **arg, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;

		mergesort(arg, l, m);
		mergesort(arg, m + 1, r);

		merge(arg, l, m, r);
	}

	return;
}

void merge(fData **arg, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	fData **L = (fData **)malloc(sizeof(fData) * n1);
	fData **R = (fData **)malloc(sizeof(fData) * n2);

	for (int i = 0; i < n1; i++) {
		L[i] = arg[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arg[m + j + 1];
	}

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i]->frequency >= R[j]->frequency) {
			arg[k++] = L[i++];
		}
		else {
			arg[k++] = R[j++];
		}
	}

	while (i < n1) {
		arg[k++] = L[i++];
	}
	while (j < n2) {
		arg[k++] = R[j++];
	}

	free(L);
	free(R);

	return;
}

//이름 오름차순으로 정렬
void nameSort(fData **data) {
	fData *temp;
	int nameCount = _msize(data) / sizeof(fData **);
	int tempCount = 0;

	for (int i = 0; i < nameCount - 2; i++) {

		if (data[i]->order != data[i + 1]->order) {
			for (int j = 0; j < tempCount - 1; j++) {
				for (int k = 0; k < tempCount - 1 - j; k++) {
					if (data[i + k]->order > data[i + k + 1]->order) {
						temp = data[i + k];
						data[i + k] = data[i + k + 1];
						data[i + k + 1] = temp;
					}
				}
			}

			tempCount = 0;
		}
		else {
			tempCount++;
		}
	}

	return;
}