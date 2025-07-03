# 目标别名示例 - 展示add_library/add_executable别名的使用

# 创建一个库目标
add_library(string_utils STATIC string_utils.cpp)

# 为库目标添加别名
add_library(str_utils ALIAS string_utils)

# 创建可执行目标
add_executable(string_demo main.cpp)

# 为可执行目标添加别名
add_executable(str_demo ALIAS string_demo)

# 链接时可以使用原始名称或别名
target_link_libraries(string_demo
    PRIVATE
        str_utils  # 使用别名
)

# 创建示例源文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/string_utils.cpp
"#include <string>
#include <algorithm>

std::string to_upper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
"#include <iostream>
#include \"string_utils.hpp\"

int main() {
    std::cout << to_upper(\"hello alias\") << \"\\n\";
    return 0;
}
")

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/string_utils.hpp
"#pragma once
#include <string>

std::string to_upper(const std::string& str);
")

# 展示别名和原始目标的区别
message(STATUS "原始库目标: ${string_utils}")
message(STATUS "库目标别名: ${str_utils}")

message(STATUS "原始可执行目标: ${string_demo}")
message(STATUS "可执行目标别名: ${str_demo}")

# 检查别名是否可用
if(TARGET str_utils AND TARGET string_utils)
    message(STATUS "别名str_utils可用")
endif()

if(TARGET str_demo AND TARGET string_demo)
    message(STATUS "别名str_demo可用")
endif()