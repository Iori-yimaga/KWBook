#include "initializer.h"
#include "globalVals.h"
#include <io.h>
#include <stdio.h>

// 初始化程序
void init() {
	// 判断文件是否存在，若不存在则新建文件
	// 若存在，则不进行操作
	if (_access(PATH, 0)) {
		FILE* fp = NULL;
		fopen_s(&fp, PATH, "w");
		fclose(fp);
	}
}