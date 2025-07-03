# 方法3: find_package + 包配置 示例
cmake_minimum_required(VERSION 3.15)
project(FindPackageDemo)

# 尝试查找已安装的包
find_package(MakefileDemo QUIET)

if(NOT MakefileDemo_FOUND)
    # 如果没找到，则构建并安装
    include(ExternalProject)
    ExternalProject_Add(
        makefile_project
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/../../makefile_project
        CONFIGURE_COMMAND ""
        BUILD_COMMAND make -C <SOURCE_DIR>
        INSTALL_COMMAND make -C <SOURCE_DIR> install DESTDIR=<BINARY_DIR>/install
    )
    
    # 设置安装后的路径
    set(MakefileDemo_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/install/usr/local/include/demo)
    set(MakefileDemo_LIBRARIES ${CMAKE_BINARY_DIR}/install/usr/local/lib/libdemo.a)
    
    # 创建包配置文件
    file(WRITE ${CMAKE_BINARY_DIR}/MakefileDemoConfig.cmake
    "set(MakefileDemo_INCLUDE_DIRS \"${MakefileDemo_INCLUDE_DIRS}\")
    set(MakefileDemo_LIBRARIES \"${MakefileDemo_LIBRARIES}\")
    set(MakefileDemo_FOUND TRUE)")
    
    # 添加依赖
    add_dependencies(demo_app makefile_project)
endif()

# 创建主程序
add_executable(demo_app main.cpp)

# 包含目录和链接库
target_include_directories(demo_app PRIVATE ${MakefileDemo_INCLUDE_DIRS})
target_link_libraries(demo_app PRIVATE ${MakefileDemo_LIBRARIES})