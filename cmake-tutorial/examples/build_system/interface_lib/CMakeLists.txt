# 接口库示例 - 展示INTERFACE库的使用

# 创建一个接口库(纯头文件库)
add_library(geometry_interface INTERFACE)

# 为接口库添加使用要求
target_include_directories(geometry_interface
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(geometry_interface
    INTERFACE
        USE_GEOMETRY_INTERFACE=1
)

# 创建使用该接口库的可执行文件
add_executable(geometry_demo main.cpp)

# 链接接口库(会继承include目录和编译定义)
target_link_libraries(geometry_demo
    PRIVATE
        geometry_interface
)

# 检查使用要求是否传递
get_target_property(includes geometry_interface INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "接口库包含目录: ${includes}")

get_target_property(defs geometry_interface INTERFACE_COMPILE_DEFINITIONS)
message(STATUS "接口库编译定义: ${defs}")

# 创建include目录和头文件(模拟头文件库)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/geometry)
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/include/geometry/vector.hpp
"// 示例头文件
#pragma once

namespace geometry {
    struct Vector3 {
        float x, y, z;
    };
}
")

# 创建示例源文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
"#include <geometry/vector.hpp>
#include <iostream>

int main() {
    geometry::Vector3 v{1.0f, 2.0f, 3.0f};
    std::cout << \"Vector: (\" << v.x << \", \" << v.y << \", \" << v.z << \")\\n\";
    return 0;
}
")