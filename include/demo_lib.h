#ifndef DEMO_LIB_H
#define DEMO_LIB_H

// 从配置文件中获取的版本信息
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

// 基本数学函数
int add(int a, int b);
int subtract(int a, int b);

// 字符串函数
const char* get_greeting();

// 版本信息
const char* get_version();

#ifdef __cplusplus
}
#endif

// 宏定义
#define DEMO_LIB_MAX_VALUE 100

#endif // DEMO_LIB_H