# 顶级CMakeLists.txt - CMake现代特性示例项目
cmake_minimum_required(VERSION 3.10)
project(ModernCMakeExamples)

# 添加高级生成器表达式示例
add_subdirectory(examples/advanced_generator_expressions/target_property_example)
add_subdirectory(examples/advanced_generator_expressions/compile_language_example)

# 添加平台特定特性示例
add_subdirectory(examples/platform_specific/pie_check_example)
add_subdirectory(examples/platform_specific/vs_properties_example)
add_subdirectory(examples/platform_specific/xcode_attributes_example)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 安装规则
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
    DESTINATION bin
    FILES_MATCHING PATTERN "*"
)