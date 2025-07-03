# COMPILE_LANGUAGE 生成器表达式示例
cmake_minimum_required(VERSION 3.10)
project(CompileLanguageExample)

# 添加混合语言源文件
# 创建混合语言可执行文件
# 包含C++和C源文件（main.cpp和helper.c）
# CMake会自动检测文件类型并调用对应编译器
add_executable(compile_language_example 
    main.cpp
    helper.c
)

# 根据编译语言设置不同选项
# COMPILE_LANGUAGE生成器表达式会在编译时检测源文件语言
# 语法说明：$<$<COMPILE_LANGUAGE:LANG>:option> 当编译LANG语言文件时应用option
target_compile_options(compile_language_example PRIVATE
    # C++特有选项
    $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra>  # C++文件启用所有警告和额外警告
    # C特有选项
    $<$<COMPILE_LANGUAGE:C>:-Wno-unused-parameter>  # C文件禁用未使用参数警告
)

# 根据语言设置预处理器定义
# 示例场景：同一份头文件在C/C++不同语言环境下的条件编译
target_compile_definitions(compile_language_example PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:USING_CXX>
    $<$<COMPILE_LANGUAGE:C>:USING_C>
)

# 设置C语言标准（C11）
# 注意：此设置仅影响C源文件
# CMAKE_C_STANDARD是更现代的设置方式
set_property(TARGET compile_language_example PROPERTY C_STANDARD 11)

# 设置C++语言标准（C++14）
# 与C标准设置相互独立
# CMAKE_CXX_STANDARD变量控制全局C++标准
set_property(TARGET compile_language_example PROPERTY CXX_STANDARD 14)