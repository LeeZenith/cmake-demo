# find_package示例 - 展示如何查找和使用外部包

# 基本用法(查找Zlib库)
find_package(ZLIB REQUIRED)

message(STATUS "Zlib版本: ${ZLIB_VERSION}")
message(STATUS "Zlib包含目录: ${ZLIB_INCLUDE_DIRS}")
message(STATUS "Zlib库文件: ${ZLIB_LIBRARIES}")

# 创建使用Zlib的可执行文件
add_executable(zlib_demo main.cpp)

# 链接Zlib库
target_link_libraries(zlib_demo
    PRIVATE
        ${ZLIB_LIBRARIES}
)

# 添加包含目录
target_include_directories(zlib_demo
    PRIVATE
        ${ZLIB_INCLUDE_DIRS}
)

# 组件和版本约束示例(以Boost为例)
# find_package(Boost 1.70.0 REQUIRED COMPONENTS filesystem system)

# 自定义查找逻辑
# 1. 首先尝试系统安装的包
# 2. 如果找不到，使用本地构建的版本
find_package(JSONCPP QUIET)
if(NOT JSONCPP_FOUND)
    message(STATUS "系统未安装JsonCpp，使用本地构建")
    add_subdirectory(jsoncpp)
    set(JSONCPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include)
    set(JSONCPP_LIBRARIES jsoncpp_lib)
endif()

# 创建示例源文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
R"(#include <iostream>
#include <zlib.h>

int main() {
    std::cout << "Zlib版本: " << ZLIB_VERSION << "\\n";
    std::cout << "编译时版本: " << zlibVersion() << "\\n";
    return 0;
}
)")

# 创建模拟的jsoncpp目录结构
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include)

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/CMakeLists.txt
"add_library(jsoncpp_lib STATIC jsoncpp.cpp)")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/jsoncpp.cpp
"// 模拟的JsonCpp实现")

message(STATUS "\nfind_package总结:")
message(STATUS "1. REQUIRED选项使找不到包时报错")
message(STATUS "2. QUIET选项抑制未找到包的消息")
message(STATUS "3. 可以指定版本约束(如Boost 1.70.0)")
message(STATUS "4. COMPONENTS指定需要的组件")
"]>