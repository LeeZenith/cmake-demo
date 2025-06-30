#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    std::cout << "Visual Studio Properties Example\n";
    
    // 演示跨平台实现
    #ifdef _WIN32
    // Windows特定实现
    char buffer[10];
    strcpy_s(buffer, "Hello");  // 使用安全的字符串函数
    
    SYSTEM_INFO sysInfo;
    GetNativeSystemInfo(&sysInfo);
    std::cout << "Number of processors: " << sysInfo.dwNumberOfProcessors << "\n";
    #else
    // 非Windows平台实现
    std::cout << "This example demonstrates Visual Studio specific properties.\n";
    std::cout << "Windows-specific features are not available on this platform.\n";
    #endif
    
    return 0;
}