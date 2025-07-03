# CMake教程 - 现代CMake最佳实践

cmake_minimum_required(VERSION 3.15)
project(CMakeTutorial VERSION 1.0.0 LANGUAGES CXX)

# 启用现代CMake特性
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加示例子目录
add_subdirectory(examples/basic/conditions)
add_subdirectory(examples/basic/loops)
add_subdirectory(examples/basic/functions)

add_subdirectory(examples/build_system/interface_lib)
add_subdirectory(examples/build_system/imported_target)
add_subdirectory(examples/build_system/target_alias)

add_subdirectory(examples/dependency/find_package)
add_subdirectory(examples/dependency/package_config)
add_subdirectory(examples/dependency/transitive_deps)

# 创建README文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/README.md
"# CMake教程

本教程展示现代CMake的最佳实践，包含以下示例：

## 基础特性
1. 条件语句 - examples/basic/conditions
2. 循环 - examples/basic/loops
3. 函数和宏 - examples/basic/functions

## 构建系统
1. 接口库 - examples/build_system/interface_lib
2. 导入目标 - examples/build_system/imported_target
3. 目标别名 - examples/build_system/target_alias

## 依赖管理
1. find_package - examples/dependency/find_package
2. 包配置 - examples/dependency/package_config
3. 依赖传递性 - examples/dependency/transitive_deps

## 构建说明
\```bash
mkdir build && cd build
cmake ..
cmake --build .
\```
")

# 安装说明
install(DIRECTORY examples/ DESTINATION share/cmake-tutorial/examples)
install(FILES README.md DESTINATION share/cmake-tutorial)

message(STATUS "\nCMake教程构建完成！")
message(STATUS "查看README.md获取详细说明")
]>