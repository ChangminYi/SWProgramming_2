#include <stdio.h>
#include "Function_Define.h"
#include "Struct_Define.h"


fData **sortStruct(fData **data, int Left, int Right) {
	//퀵소트(오류있음->수정계획)
	/*if (Left >= Right) {
		return NULL;
	}
	else {
		int pivot = (Left + Right) / 2;
		int L = Left, R = Right;
		fData *temp = NULL;

		for (;;) {
			while (data[L]->frequency < data[pivot]->frequency) {
				L++;
			}
			while (data[R]->frequency > data[pivot]->frequency) {
				R--;
			}
			if (L > R) {
				break;
			}

			temp = data[L];
			data[L++] = data[R];
			data[R--] = temp;
		}

		sortStruct(data, Left, R);
		sortStruct(data, L, Right);
	}
	*/

	//버블소트
	fData *temp;
	for (int i = 0; i < Right - Left; i++) {
		for (int j = 0; j < Right - Left - i; j++) {
			if (data[j]->frequency > data[j + 1]->frequency) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}

	return data;
}