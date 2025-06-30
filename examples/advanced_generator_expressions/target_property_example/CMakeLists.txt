# $<TARGET_PROPERTY:...> 生成器表达式示例
cmake_minimum_required(VERSION 3.10)
project(TargetPropertyExample)

# 创建一个库目标
add_library(my_library STATIC lib_source.cpp)

# 设置一些自定义属性
define_property(TARGET PROPERTY MY_CUSTOM_FLAGS
    BRIEF_DOCS "Custom compiler flags"
    FULL_DOCS "Additional compiler flags for this target"
)

set_target_properties(my_library PROPERTIES
    MY_CUSTOM_FLAGS "-DEXTRA_FEATURE"
    CXX_STANDARD 14
)

# 添加一个可执行文件来演示属性访问
add_executable(target_property_example main.cpp)

# 使用生成器表达式查询库目标的属性
target_compile_definitions(target_property_example PRIVATE
    $<$<BOOL:$<TARGET_PROPERTY:my_library,MY_CUSTOM_FLAGS>>:$<TARGET_PROPERTY:my_library,MY_CUSTOM_FLAGS>>
)

# 打印目标的属性信息
message(STATUS "Library CXX standard: $<TARGET_PROPERTY:my_library,CXX_STANDARD>")
message(STATUS "Library type: $<TARGET_PROPERTY:my_library,TYPE>")

# 根据属性条件设置不同的编译选项
target_compile_options(target_property_example PRIVATE
    $<$<STREQUAL:$<TARGET_PROPERTY:my_library,TYPE>,STATIC_LIBRARY>:-DUSING_STATIC_LIB>
    $<$<STREQUAL:$<TARGET_PROPERTY:my_library,TYPE>,SHARED_LIBRARY>:-DUSING_SHARED_LIB>
)