#include "passwd_op.h"
#include "globalVals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <conio.h>

int g_Count = 0;
USERINFO myinfo = { 0 };

// 查看全部密码
void showAll() {
	g_Count = 0;
	FILE* fp = NULL;
	if ((fopen_s(&fp, PATH, "r")) == 0) {
		// 获取记录数
		int flag = 0;
		while (!feof(fp)) {
			flag = fgetc(fp);
			if (flag == '\n') {
				g_Count += 1;
			}
		}
		// 文件指针置于开头
		rewind(fp);
		PUSERINFO pMyInfo = (PUSERINFO)malloc(g_Count * sizeof(USERINFO));
		for (int i = 0; i < g_Count; i++) {
			fscanf_s(fp, "%d\t%s\t%s\t%s\n", &(pMyInfo + i)->ID, (pMyInfo + i)->webSite, 20, (pMyInfo + i)->userName, 20, (pMyInfo + i)->passWord, 20);
			// printf("%d\t%s\t%s\t%s\n", (pMyInfo + i)->ID, (pMyInfo + i)->webSite, (pMyInfo + i)->userName, (pMyInfo + i)->passWord);
			printf("%d\t%s\t%s\t%s\n", (pMyInfo + i)->ID, (pMyInfo + i)->webSite, (pMyInfo + i)->userName, "******");
		}
		free(pMyInfo);
		fclose(fp);
	}
	else {
		printf("文件打开失败！");
		exit(1);
	}
}

// 新增一条记录
void addPasswd() {
	g_Count = 0;
	FILE* fp = NULL;
	fopen_s(&fp, PATH, "a+");
	fseek(fp, 0, SEEK_SET);

	int flag = 0;
	while (!feof(fp)) {
		flag = fgetc(fp);
		if (flag == '\n') {
			g_Count += 1;
		}
	}
	g_Count += 1;

	// 输入数据
	myinfo.ID = g_Count;
	printf("请输入网站：");
	scanf_s("%s", &myinfo.webSite, 20);
	printf("请输入账户：");
	scanf_s("%s", &myinfo.userName, 20);
	printf("请输入密码：");
	// scanf_s("%s", &myinfo.passWord, 20);
	
	// 无回显版本输入
	char ch = '0';   // 单字符接收密码
	int index = 0;   // 游标
	while ((ch = _getch()) != '\r') {
		if (ch != 8) {
			myinfo.passWord[index] = ch;
			putchar('*');
			index++;
		}
		else {
			if (index > 0) {
				index--;
				myinfo.passWord[index] = '\0';
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
	}
	myinfo.passWord[index] = '\0';

	// 写入数据
	if (fprintf(fp, "%d\t%s\t%s\t%s\n", myinfo.ID, myinfo.webSite, myinfo.userName, myinfo.passWord)) {
		printf("\n写入成功！\n");
		g_Count += 1;
	}
	else {
		printf("\n写入失败！\n");
	}
	fclose(fp);
}

// 修改密码
void changePasswd() {
	// 获取行数
	g_Count = 0;
	FILE* fp = NULL;
	fopen_s(&fp, PATH, "r");
	int flag = 0;
	while (!feof(fp)) {
		flag = fgetc(fp);
		if (flag == '\n') {
			g_Count += 1;
		}
	}
	// 文件指针置于开头
	rewind(fp);
	PUSERINFO pMyInfo = (PUSERINFO)malloc(g_Count * sizeof(USERINFO));
	for (int i = 0; i < g_Count; i++) {
		fscanf_s(fp, "%d\t%s\t%s\t%s\n", &(pMyInfo + i)->ID, (pMyInfo + i)->webSite, 20, (pMyInfo + i)->userName, 20, (pMyInfo + i)->passWord, 20);
	}
	fclose(fp);
	// 以"w"的形式覆写文件
	fopen_s(&fp, PATH, "w");

	// 交互部分
	int num = 0;
	char arr[20] = { 0 };
	printf("请输入需要修改的ID：");
	scanf_s("%d", &num);
	printf("请输入新密码：");
	// scanf_s("%s", arr, 20);

	// 无回显版本
	char ch = '0';   // 单字符接收密码
	int index = 0;   // 游标
	while ((ch = _getch()) != '\r') {
		if (ch != 8) {
			arr[index] = ch;
			putchar('*');
			index++;
		}
		else {
			if (index > 0) {
				index--;
				arr[index] = '\0';
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
	}
	arr[index] = '\0';

	strcpy_s((pMyInfo + num - 1)->passWord, 20, arr);
	for (int i = 0; i < g_Count; i++) {
		fprintf(fp, "%d\t%s\t%s\t%s\n", (pMyInfo + i)->ID, (pMyInfo + i)->webSite, (pMyInfo + i)->userName, (pMyInfo + i)->passWord);
	}
	printf("修改成功！\n");
	free(pMyInfo);
	fclose(fp);
}

// 查看指定密码
void queryPasswd() {
	int num = 0;
	printf("请输入需要查看的ID：");
	scanf_s("%d", &num);
	// 获取行数
	g_Count = 0;
	FILE* fp = NULL;
	fopen_s(&fp, PATH, "r+");
	int flag = 0;
	while (!feof(fp)) {
		flag = fgetc(fp);
		if (flag == '\n') {
			g_Count += 1;
		}
	}
	// 文件指针置于开头
	rewind(fp);
	// 将文件读到内存中
	PUSERINFO pMyInfo = (PUSERINFO)malloc(g_Count * sizeof(USERINFO));
	for (int i = 0; i < g_Count; i++) {
		fscanf_s(fp, "%d\t%s\t%s\t%s\n", &(pMyInfo + i)->ID, (pMyInfo + i)->webSite, 20, (pMyInfo + i)->userName, 20, (pMyInfo + i)->passWord, 20);
	}
	// 判断用户输入数字的界限
	if (num > 0 && num < g_Count) {
		printf("%d\t%s\t%s\t%s\n", (pMyInfo + num - 1)->ID, (pMyInfo + num - 1)->webSite, (pMyInfo + num - 1)->userName, (pMyInfo + num - 1)->passWord);
	}
	else {
		printf("没找到记录哦，越界了吧~~~\n");
	}
	free(pMyInfo);
	fclose(fp);
}

// 删除指定密码
void removePasswd() {
	// 获取行数
	g_Count = 0;
	FILE* fp = NULL;
	fopen_s(&fp, PATH, "r+");
	int flag = 0;
	while (!feof(fp)) {
		flag = fgetc(fp);
		if (flag == '\n') {
			g_Count += 1;
		}
	}
	// 文件指针置于开头
	rewind(fp);
	PUSERINFO pMyInfo = (PUSERINFO)malloc(g_Count * sizeof(USERINFO));
	for (int i = 0; i < g_Count; i++) {
		fscanf_s(fp, "%d\t%s\t%s\t%s\n", &(pMyInfo + i)->ID, (pMyInfo + i)->webSite, 20, (pMyInfo + i)->userName, 20, (pMyInfo + i)->passWord, 20);
	}
	fclose(fp);

	fopen_s(&fp, PATH, "w");
	// 交互部分
	int num = 0;
	char choice[10] = { 0 };
	printf("请输入你想删除的ID：");
	scanf_s("%d", &num);
	printf("危险操作！确认要删除这条数据吗？yes/no \n");
	printf("%d\t%s\t%s\t%s\n", (pMyInfo + num - 1)->ID, (pMyInfo + num - 1)->webSite, (pMyInfo + num - 1)->userName, (pMyInfo + num - 1)->passWord);
	printf("请确认您的操作：");
	scanf_s("%s", choice, 10);
	if (!strcmp(choice, "yes")) {
		for (int i = num - 1; i < g_Count; i++) {
			(pMyInfo + i)->ID = (pMyInfo + i + 1)->ID;
			memcpy((pMyInfo+i)->webSite, (pMyInfo+i+1)->webSite, 20);
			memcpy((pMyInfo + i)->userName, (pMyInfo + i + 1)->userName, 20);
			memcpy((pMyInfo + i)->passWord, (pMyInfo + i + 1)->passWord, 20);
		}
		g_Count -= 1;
		for (int i = 0; i < g_Count; i++) {
			fprintf(fp, "%d\t%s\t%s\t%s\n", (pMyInfo + i)->ID, (pMyInfo + i)->webSite, (pMyInfo + i)->userName, (pMyInfo + i)->passWord);
		}
		printf("删除成功！ 0.0\n");
	}else if (!strcmp(choice, "no")) {
		printf("取消？那没事了~~~\n");
	}
	else {
		printf("按的啥啊？看不懂 -.-\n");
	}
	free(pMyInfo);
	fclose(fp);
}