# 方法1: ExternalProject_Add 示例
cmake_minimum_required(VERSION 3.15)
project(ExternalProjectDemo)

# 包含ExternalProject模块
include(ExternalProject)

# 添加Makefile项目作为外部项目
ExternalProject_Add(
    makefile_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/../../makefile_project
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -C <SOURCE_DIR>
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/makefile_project/libdemo.a
)

# 创建主项目
add_executable(demo_app main.cpp)

# 添加依赖和链接
add_dependencies(demo_app makefile_project)
target_include_directories(demo_app PRIVATE 
    ${CMAKE_SOURCE_DIR}/../../makefile_project/include)
target_link_directories(demo_app PRIVATE 
    ${CMAKE_BINARY_DIR}/makefile_project)
target_link_libraries(demo_app PRIVATE demo)