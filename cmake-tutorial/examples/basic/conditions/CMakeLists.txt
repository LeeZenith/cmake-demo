# 条件语句示例 - 展示CMake中的if/elseif/else控制流

# 设置一个测试变量
set(TEST_CONDITION "A")

# 基础if语句
if(TEST_CONDITION STREQUAL "A")
    message(STATUS "条件1满足: TEST_CONDITION是A")
elseif(TEST_CONDITION STREQUAL "B")
    message(STATUS "条件2满足: TEST_CONDITION是B")
else()
    message(STATUS "其他情况: TEST_CONDITION是${TEST_CONDITION}")
endif()

# 检查变量定义
if(DEFINED TEST_CONDITION)
    message(STATUS "TEST_CONDITION已定义")
endif()

# 平台检测示例
if(WIN32)
    message(STATUS "这是Windows平台")
elseif(UNIX)
    message(STATUS "这是Unix-like平台")
endif()

# 编译器检测
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "使用GCC编译器")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "使用MSVC编译器")
endif()

# 复合条件
if(NOT WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "在Unix-like平台使用GCC编译器")
endif()