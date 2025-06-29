#include "demo_lib.h"
#include "config.h"

#include <string>

// 基本数学函数实现
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// 字符串函数实现
const char* get_greeting() {
    return "Hello, CMake!";
}

// 版本信息函数实现
const char* get_version() {
    static std::string version = PROJECT_NAME " v" PROJECT_VERSION;
    return version.c_str();
}

// 使用特性开关
#ifdef FEATURE_ENABLED
void feature_function() {
    // 特性功能的实现
}
#endif