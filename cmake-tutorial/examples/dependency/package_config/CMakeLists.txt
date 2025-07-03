# 包配置示例 - 展示如何创建可重用的包配置

# 首先创建一个简单的库
add_library(math_functions STATIC math_functions.cpp)

# 设置项目版本
set(MATH_FUNCTIONS_VERSION 1.2.3)
set(MATH_FUNCTIONS_VERSION_MAJOR 1)
set(MATH_FUNCTIONS_VERSION_MINOR 2)
set(MATH_FUNCTIONS_VERSION_PATCH 3)

# 创建头文件目录
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/math_functions)

# 创建示例源文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/math_functions.cpp
R"(#include "math_functions/math_utils.h"

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
)")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/math_functions/math_utils.h
R"(#pragma once

int add(int a, int b);
int subtract(int a, int b);
)")

# 导出配置 - 创建目标导出
install(TARGETS math_functions
    EXPORT MathFunctionsTargets
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

# 安装头文件
install(DIRECTORY include/ DESTINATION include)

# 创建配置文件
include(CMakePackageConfigHelpers)

# 生成包版本文件
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
    VERSION ${MATH_FUNCTIONS_VERSION}
    COMPATIBILITY SameMajorVersion
)

# 生成包配置模板
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
    INSTALL_DESTINATION lib/cmake/MathFunctions
)

# 安装配置文件
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
    DESTINATION lib/cmake/MathFunctions
)

# 安装导出目标
install(EXPORT MathFunctionsTargets
    FILE MathFunctionsTargets.cmake
    DESTINATION lib/cmake/MathFunctions
)

# 创建配置模板文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
R"(@PACKAGE_INIT@

include("${CMAKE_CURRENT_LIST_DIR}/MathFunctionsTargets.cmake")

# 提供一些有用的变量
set(MATH_FUNCTIONS_VERSION @MATH_FUNCTIONS_VERSION@)
set(MATH_FUNCTIONS_INCLUDE_DIRS "@PACKAGE_INCLUDE_INSTALL_DIR@")

# 验证所有必需组件都存在
check_required_components(MathFunctions)
)")

message(STATUS "\n包配置创建说明:")
message(STATUS "1. 使用install()命令安装目标、头文件和配置文件")
message(STATUS "2. write_basic_package_version_file生成版本文件")
message(STATUS "3. configure_package_config_file生成主配置文件")
message(STATUS "4. 安装后其他项目可通过find_package(MathFunctions)使用")
]>