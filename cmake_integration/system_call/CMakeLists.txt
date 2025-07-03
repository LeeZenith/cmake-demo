# 方法4: 直接系统调用 示例
cmake_minimum_required(VERSION 3.15)
project(SystemCallDemo)

# 设置Makefile项目路径
set(MAKEFILE_PROJECT_DIR ${CMAKE_SOURCE_DIR}/../../makefile_project)

# 构建Makefile项目
execute_process(
    COMMAND make -C ${MAKEFILE_PROJECT_DIR}
    WORKING_DIRECTORY ${MAKEFILE_PROJECT_DIR}
)

# 创建主程序
add_executable(demo_app main.cpp)

# 包含目录和链接库
target_include_directories(demo_app PRIVATE ${MAKEFILE_PROJECT_DIR}/include)
target_link_directories(demo_app PRIVATE ${MAKEFILE_PROJECT_DIR})
target_link_libraries(demo_app PRIVATE demo)