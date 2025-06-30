# COMPILE_LANGUAGE 生成器表达式示例
cmake_minimum_required(VERSION 3.10)
project(CompileLanguageExample)

# 添加混合语言源文件
add_executable(compile_language_example 
    main.cpp
    helper.c
)

# 根据编译语言设置不同选项
target_compile_options(compile_language_example PRIVATE
    # C++特有选项
    $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra>
    # C特有选项
    $<$<COMPILE_LANGUAGE:C>:-Wno-unused-parameter>
)

# 根据语言设置不同定义
target_compile_definitions(compile_language_example PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:USING_CXX>
    $<$<COMPILE_LANGUAGE:C>:USING_C>
)

# 设置C标准
set_property(TARGET compile_language_example PROPERTY C_STANDARD 11)

# 设置C++标准
set_property(TARGET compile_language_example PROPERTY CXX_STANDARD 14)