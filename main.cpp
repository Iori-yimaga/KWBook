/*
	密码本项目：
	01 查看密码本
	02 增加密码
	03 修改密码
	04 查看指定密码
	05 删除指定密码
	06 退出程序
*/
// 系统引用区
#include <stdio.h>
#include <stdlib.h>

// 自有引用区
#include "menu.h"
#include "globalVals.h"
#include "passwd_op.h"
#include "initializer.h"
#include "permissionCheck.h"

// 主程序
int main() {
	// 初始化程序
	init();

	// 权限认证
	int flag = isAdmin();
	if (flag == 1) {
		system("title 密码本v1.0");
		// 选择
		int choice = 0;

		do {
			menu();
			printf("请按照提示进行选择：");
			scanf_s("%d", &choice);
			switch (choice) {
				case 1: { // 查看密码本
					showAll();
					break;
				}
				case 2: { // 增加密码
					addPasswd();
					break;
				}
				case 3: { // 修改密码
					changePasswd();
					break;
				}
				case 4: { // 查看指定密码
					queryPasswd();
					break;
				}
				case 5: { // 删除指定密码
					removePasswd();
					break;
				}
				case 6: { // 退出程序
					printf("再见~~~\n");
					break;
				}
				default: {
					printf("非法输入！！！\n");
					break;
				}
			}
		} while (choice != 6);
	}
	else {
		exit(1);
	}

	return 0;
}