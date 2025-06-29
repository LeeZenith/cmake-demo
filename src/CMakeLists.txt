# 主程序CMake配置

# 添加可执行文件目标
# 使用项目名称作为可执行文件名
add_executable(${PROJECT_NAME} main.c)

# 确保第三方头文件目录存在
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/include)

# 添加库的头文件目录
# 这里链接到将要创建的math和utils库
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/libs
    ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/include
)

# 链接库
# 这里链接到将要创建的math和utils库
target_link_libraries(${PROJECT_NAME} PRIVATE
    math_lib
    utils_lib
    simple_makefile
)

# 打印调试信息
message(STATUS "Third party include dir: ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/include")

# 安装配置
# 将可执行文件安装到bin目录
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)