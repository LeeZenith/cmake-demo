cmake_minimum_required(VERSION 3.10)

# 项目基本信息
project(CMakeDemo
    VERSION 1.0.0
    LANGUAGES C
)

# 设置安装前缀
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "/home/heita/work/install")
endif()

# 定义安装目录变量
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含子目录 - 正常的CMake项目
add_subdirectory(libs/math)
add_subdirectory(libs/utils)

# 添加使用Makefile的三方库
include(ExternalProject)
ExternalProject_Add(
    simple_makefile_lib
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -C ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib
    INSTALL_COMMAND make -C ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib install
    BUILD_IN_SOURCE TRUE
)

# 设置三方库的头文件和库文件路径
set(THIRD_PARTY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/include)
set(THIRD_PARTY_LIB_DIR ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/lib)

# 创建导入库目标
add_library(simple_makefile STATIC IMPORTED)
set_target_properties(simple_makefile PROPERTIES
    IMPORTED_LOCATION ${THIRD_PARTY_LIB_DIR}/libsimple.a
    INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR}
)

# 包含主程序目录
add_subdirectory(src)

# 添加依赖关系，确保三方库先构建
add_dependencies(CMakeDemo simple_makefile_lib)

# 创建include目录(如果不存在)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/simple_makefile_lib/include)

# 安装可执行文件
install(TARGETS CMakeDemo
    RUNTIME DESTINATION ${INSTALL_BIN_DIR}
    COMPONENT runtime
)

# 安装库文件
install(TARGETS math_lib utils_lib
    ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    COMPONENT runtime
)

# 安装头文件
install(FILES libs/math/add.h libs/math/sub.h
    DESTINATION ${INSTALL_INCLUDE_DIR}/math
)
install(DIRECTORY libs/utils/ 
    DESTINATION ${INSTALL_INCLUDE_DIR}/utils
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY ${THIRD_PARTY_INCLUDE_DIR} 
    DESTINATION ${INSTALL_INCLUDE_DIR}/third_party
)
install(FILES ${THIRD_PARTY_LIB_DIR}/libsimple.a
    DESTINATION ${INSTALL_LIB_DIR}
    RENAME libsimple_makefile_lib.a
)

# 添加自定义install目标
add_custom_target(install_all
    COMMAND "${CMAKE_COMMAND}" --install "${CMAKE_BINARY_DIR}"
    COMMENT "Installing the project..."
)

# 打印安装信息
message(STATUS "Installation prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Binaries will be installed to: ${INSTALL_BIN_DIR}")
message(STATUS "Libraries will be installed to: ${INSTALL_LIB_DIR}")
message(STATUS "Headers will be installed to: ${INSTALL_INCLUDE_DIR}")