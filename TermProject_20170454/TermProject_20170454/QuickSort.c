#include <stdio.h>
#include "Function_Define.h"
#include "Struct_Define.h"

fData **sortStruct(fData **data, int Left, int Right) {
	if (Left >= Right) {
		return NULL;
	}
	else {
		int pivot = (Left + Right) / 2;
		int L = Left, R = Right;
		fData *temp = NULL;

		while (1) {
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

	return data;
}