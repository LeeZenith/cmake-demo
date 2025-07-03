# 顶级CMakeLists.txt - CMake现代特性示例项目
# CMake最低版本要求（演示3.10新特性）
cmake_minimum_required(VERSION 3.10)
project(ModernCMakeExamples)

# 设置输出目录
# 设置运行时输出目录
# CMAKE_BINARY_DIR: 构建目录的绝对路径
# 该变量控制可执行文件的生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 设置固定安装路径
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install" CACHE PATH "Installation directory" FORCE)

# 添加高级生成器表达式示例
# 添加生成器表达式示例模块
# 演示如何使用target_include_directories和target_compile_definitions
# 的生成器表达式配置目标属性
add_subdirectory(examples/advanced_generator_expressions/target_property_example)
add_subdirectory(examples/advanced_generator_expressions/compile_language_example)

# 添加平台特定特性示例
add_subdirectory(examples/platform_specific/pie_check_example)
add_subdirectory(examples/platform_specific/vs_properties_example)
add_subdirectory(examples/platform_specific/xcode_attributes_example)



# 安装规则 - 安装所有可执行文件
install(TARGETS 
    target_property_example
    compile_language_example
    pie_check_example
    vs_properties_example
    xcode_attributes_example
    RUNTIME DESTINATION bin
)