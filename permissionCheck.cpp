#include "permissionCheck.h"
#include "globalVals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

ADMIN admin = {"admin", "admin"};
int adminFlag = 0;

// 权限验证
int isAdmin() {
	system("title 权限认证页");
	char username[20] = { "" };
	char passwd[20] = { "" };
	printf("要使用本程序\n");
	printf("请先进行权限验证.\n");
	printf("请输入用户名: ");
	scanf_s("%s", username, 20);
	printf("请输入密码: ");
	// scanf_s("%s", passwd, 20);

	// 无回显版本输入
	char ch = '0';   // 单字符接收密码
	int index = 0;   // 游标
	while ((ch = _getch()) != '\r') {
		if (ch != 8) {
			passwd[index] = ch;
			putchar('*');
			index++;
		}
		else {
			if (index > 0) {
				index--;
				passwd[index] = '\0';
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
	}
	passwd[index] = '\0';

	if (!strcmp(username, admin.USERNAME) && !strcmp(passwd, admin.PASSWD)) {
		printf("验证成功！欢迎使用本程序！\n");
		adminFlag = 1;
	}
	else {
		printf("用户名或密码错误，验证失败！\n");
	}
	system("cls");
	return adminFlag;
}