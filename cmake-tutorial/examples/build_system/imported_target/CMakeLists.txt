# 导入目标示例 - 展示IMPORTED库的使用

# 假设我们有一个预编译的数学库
set(MATH_LIB_NAME "math_utils")

# 平台特定的库路径和名称
if(WIN32)
    set(LIB_PREFIX "")
    set(LIB_SUFFIX ".lib")
    set(LIB_DIR "windows")
elseif(UNIX)
    set(LIB_PREFIX "lib")
    set(LIB_SUFFIX ".a")
    set(LIB_DIR "linux")
endif()

# 设置库文件路径(模拟预编译库)
set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_DIR}/${LIB_PREFIX}${MATH_LIB_NAME}${LIB_SUFFIX})

# 创建导入目标
add_library(math_utils STATIC IMPORTED)

# 设置导入属性
set_target_properties(math_utils PROPERTIES
    IMPORTED_LOCATION ${LIBRARY_PATH}
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 创建使用该库的可执行文件
add_executable(math_demo main.cpp)

# 链接导入库
target_link_libraries(math_demo
    PRIVATE
        math_utils
)

# 创建模拟的库文件和头文件目录
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_DIR})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/math_utils)

# 模拟创建库文件(实际项目中应该是真实的预编译库)
file(WRITE ${LIBRARY_PATH} "模拟的预编译库文件")

# 创建头文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/math_utils/utils.h
"// 数学工具库头文件
#pragma once

namespace math_utils {
    int add(int a, int b);
    int subtract(int a, int b);
}
")

# 创建示例源文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
"#include <math_utils/utils.h>
#include <iostream>

int main() {
    std::cout << \"3 + 5 = \" << math_utils::add(3, 5) << \"\\n\";
    std::cout << \"8 - 3 = \" << math_utils::subtract(8, 3) << \"\\n\";
    return 0;
}
")

message(STATUS "导入库路径: ${LIBRARY_PATH}")