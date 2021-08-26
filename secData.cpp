#include "secData.h"
#include <stdio.h>
#include <stdlib.h>

/*
	加密
	@param char*  传入一个字符串
*/
void encryptData(char* str) {
	int index = 0;
	while (*(str + index) != '\0') {
		*(str + index) |= -0x80;
		*(str + index) ^= 0x1;
		index++;
	}
}

/*
	解密
	@param char*  传入一个字符串
*/
void decryptData(char* str) {
	int index = 0;
	while (*(str + index) != '\0') {
		*(str + index) ^= 0x1;
		*(str + index) ^= 0x80;
		index++;
	}
}