#include <iostream>

int main() {
    std::cout << "Position Independent Executable (PIE) example\n";
    
    // 打印一些地址来观察PIE效果
    std::cout << "Main function address: " << (void*)&main << "\n";
    
    return 0;
}