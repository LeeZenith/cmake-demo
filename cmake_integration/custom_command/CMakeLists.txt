# 方法2: add_custom_command/target 示例
cmake_minimum_required(VERSION 3.15)
project(CustomCommandDemo)

# 设置Makefile项目路径
set(MAKEFILE_PROJECT_DIR ${CMAKE_SOURCE_DIR}/../../makefile_project)

# 自定义命令构建Makefile项目
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/libdemo.a
    COMMAND make -C ${MAKEFILE_PROJECT_DIR}
    COMMAND cp ${MAKEFILE_PROJECT_DIR}/libdemo.a ${CMAKE_BINARY_DIR}/
    DEPENDS ${MAKEFILE_PROJECT_DIR}/src/hello.c 
           ${MAKEFILE_PROJECT_DIR}/src/util.c
    WORKING_DIRECTORY ${MAKEFILE_PROJECT_DIR}
    COMMENT "Building Makefile project"
)

# 自定义目标
add_custom_target(
    build_makefile
    DEPENDS ${CMAKE_BINARY_DIR}/libdemo.a
)

# 主程序
add_executable(demo_app main.cpp)
add_dependencies(demo_app build_makefile)

# 链接设置
target_include_directories(demo_app PRIVATE ${MAKEFILE_PROJECT_DIR}/include)
target_link_directories(demo_app PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(demo_app PRIVATE demo)