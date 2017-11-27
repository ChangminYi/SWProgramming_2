#include <stdio.h>
#include "Function_Define.h"
#include "Struct_Define.h"


//버블소트 (퀵소트는 오류나서 잠깐 보류)
fData **sortStruct(fData **data, int Left, int Right) {
	fData *temp;

	for (int i = 0; i < Right - Left; i++) {
		for (int j = 0; j < Right - Left - i; j++) {
			if (data[j]->frequency < data[j + 1]->frequency) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}

	return data;
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