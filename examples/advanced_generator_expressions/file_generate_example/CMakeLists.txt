# file(GENERATE) 示例
cmake_minimum_required(VERSION 3.10)
project(FileGenerateExample)

# 创建一个包含构建信息的输入模板
set(BUILD_INFO_TEMPLATE 
"// 自动生成的构建信息文件
#pragma once

#define PROJECT_NAME \"@PROJECT_NAME@\"
#define BUILD_TYPE \"@CMAKE_BUILD_TYPE@\"
#define BUILD_TIMESTAMP \"@TIMESTAMP@\"
#define COMPILER_ID \"@CMAKE_CXX_COMPILER_ID@\"
#define COMPILER_VERSION \"@CMAKE_CXX_COMPILER_VERSION@\"
")

# 使用file(GENERATE)动态创建文件
file(GENERATE 
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build_info.h"
    CONTENT "${BUILD_INFO_TEMPLATE}"
    CONDITION 1  # 总是生成
)

# 替换模板变量
string(TIMESTAMP TIMESTAMP)
string(REPLACE "@PROJECT_NAME@" "${PROJECT_NAME}" CONTENT "${BUILD_INFO_TEMPLATE}")
string(REPLACE "@CMAKE_BUILD_TYPE@" "${CMAKE_BUILD_TYPE}" CONTENT "${CONTENT}")
string(REPLACE "@TIMESTAMP@" "${TIMESTAMP}" CONTENT "${CONTENT}")
string(REPLACE "@CMAKE_CXX_COMPILER_ID@" "${CMAKE_CXX_COMPILER_ID}" CONTENT "${CONTENT}")
string(REPLACE "@CMAKE_CXX_COMPILER_VERSION@" "${CMAKE_CXX_COMPILER_VERSION}" CONTENT "${CONTENT}")

# 再次使用file(GENERATE)生成最终文件
file(GENERATE 
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build_info_final.h"
    CONTENT "${CONTENT}"
)

# 添加一个示例可执行文件来使用生成的文件
add_executable(file_generate_example main.cpp)
target_include_directories(file_generate_example PRIVATE ${CMAKE_CURRENT_BINARY_DIR})