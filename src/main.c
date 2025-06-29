#include <stdio.h>
#include "math/add.h"    // math库的头文件
#include "math/sub.h"
#include "utils/logger.h" // utils库的头文件

// 条件编译宏定义
#ifdef BUILD_WITH_LOGGER
#define USE_LOGGER 1
#else
#define USE_LOGGER 0
#endif

int main() {
    int a = 10, b = 5;
    
    // 使用math库的函数
    printf("Math operations:\n");
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));

    // 条件编译演示
    #if USE_LOGGER
    // 使用utils库的日志功能
    log_message("Logger is enabled");
    printf("Logger is enabled and working\n");
    #else
    printf("Logger is disabled\n");
    #endif

    printf("\nCMake project structure demo completed successfully!\n");
    return 0;
}