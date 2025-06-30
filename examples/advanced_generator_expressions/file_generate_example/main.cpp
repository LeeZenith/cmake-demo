#include <iostream>
#include "build_info.h"
#include "build_info_final.h"

int main() {
    std::cout << "Project: " << PROJECT_NAME << "\n";
    std::cout << "Build type: " << BUILD_TYPE << "\n";
    std::cout << "Timestamp: " << BUILD_TIMESTAMP << "\n";
    std::cout << "Compiler: " << COMPILER_ID << " " << COMPILER_VERSION << "\n";
    
    return 0;
}