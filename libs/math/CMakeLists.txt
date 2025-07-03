# Math库源文件配置
# 本文件演示如何组织基础数学运算库的构建配置
# 关键知识点：
# 1. GLOB命令自动收集源文件
# 2. PARENT_SCOPE变量的作用域传递机制

# 收集所有源文件
# 使用通配符收集所有C源文件
# 注意：GLOB在新增文件时会自动包含，但CMake官方推荐显式列出重要源文件
file(GLOB MATH_SOURCES *.c)

# 将源文件列表添加到父作用域
# 将源文件列表传递到父作用域
# PARENT_SCOPE使变量在上级CMakeLists中可用
# 这是模块化CMake工程的标准做法
set(MATH_SOURCES ${MATH_SOURCES} PARENT_SCOPE)