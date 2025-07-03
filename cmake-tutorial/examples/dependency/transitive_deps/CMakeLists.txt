# 依赖传递性示例 - 展示如何正确处理目标依赖关系

# 创建基础库A
add_library(libA STATIC libA.cpp)
target_include_directories(libA
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/libA
)

# 创建基础库B(依赖A)
add_library(libB STATIC libB.cpp)
target_link_libraries(libB
    PUBLIC
        libA
)

# 创建可执行文件(依赖B)
add_executable(app main.cpp)
target_link_libraries(app
    PRIVATE
        libB
)

# 创建示例源文件
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/libA)

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/libA.cpp
R"(#include "libA/a.h"

int funcA() { return 1; }
)")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/libA/a.h
R"(#pragma once

int funcA();
)")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/libB.cpp
R"(#include "libA/a.h"

int funcB() { return funcA() + 1; }
)")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
R"(#include <iostream>
#include "libA/a.h"

int main() {
    std::cout << "funcA: " << funcA() << "\n";
    return 0;
}
)")

# 展示依赖传递性
message(STATUS "\n依赖传递性说明:")
message(STATUS "1. PUBLIC依赖: 传递给依赖当前目标的所有目标")
message(STATUS "2. PRIVATE依赖: 仅当前目标使用，不传递")
message(STATUS "3. INTERFACE依赖: 不用于当前目标，但传递给依赖者")

# 检查包含目录传递
get_target_property(libA_includes libA INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "libA包含目录: ${libA_includes}")

get_target_property(libB_includes libB INCLUDE_DIRECTORIES)
message(STATUS "libB包含目录: ${libB_includes}")

get_target_property(app_includes app INCLUDE_DIRECTORIES)
message(STATUS "app包含目录: ${app_includes}")

# 常见错误模式示例
message(STATUS "\n常见错误模式:")
message(STATUS "1. 错误: 直接使用include_directories() - 会污染全局作用域")
message(STATUS "2. 错误: 过度使用PUBLIC - 可能导致不必要的依赖传递")
message(STATUS "3. 错误: 混合使用新旧CMake命令 - 如同时使用target_link_libraries和link_libraries")

# 最佳实践总结
message(STATUS "\n最佳实践:")
message(STATUS "1. 总是优先使用target_*命令")
message(STATUS "2. 明确指定PUBLIC/PRIVATE/INTERFACE")
message(STATUS "3. 最小化依赖传递范围")
message(STATUS "4. 使用find_package管理外部依赖")
]>