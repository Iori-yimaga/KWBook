#pragma once
#include <stdio.h>

#define PATH "MyKeyBook.txt" // 文件路径

// 管理员信息
typedef struct _ADMIN {
	char USERNAME[20];   // 管理员账户
	char PASSWD[20];     // 管理员密码
}ADMIN;

// 用户密码信息结构体
typedef struct _USERINFO {
	int ID;              // 用户ID（唯一主键）
	char webSite[20];    // 网站
	char userName[20];   // 账户
	char passWord[20];   // 密码
}USERINFO, *PUSERINFO;

extern int g_Count;      // 总记录数
extern int adminFlag;    // 是否拥有权限