cmake_minimum_required(VERSION 3.10)

# 项目基本信息
project(CMakeDemo
    VERSION 1.0.0
    LANGUAGES C CXX
)

# 设置C++标准 (CMake 3.10特性演示)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 不使用编译器特定扩展

# 生成器表达式示例 (CMake 3.10特性演示)
# 根据构建类型设置不同的编译选项
add_library(common_options INTERFACE)
target_compile_options(common_options INTERFACE
    $<$<CONFIG:Debug>:-O0 -g>          # Debug模式下的选项
    $<$<CONFIG:Release>:-O3 -DNDEBUG>  # Release模式下的选项
    $<$<CXX_COMPILER_ID:MSVC>:/W4>     # MSVC特有的警告级别
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>  # 其他编译器的警告选项
)

# 目标属性设置示例 (CMake 3.10特性演示)
# 创建一个演示库目标
add_library(demo_lib STATIC
    src/demo_lib.cpp
)

# 设置目标属性
target_compile_features(demo_lib PUBLIC cxx_std_14)  # 设置C++标准特性
target_include_directories(demo_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)
target_compile_definitions(demo_lib
    PUBLIC
        DEMO_LIBRARY
        $<$<CONFIG:Debug>:DEBUG_MODE=1>
)
target_link_libraries(demo_lib
    PUBLIC
        common_options
)

# 测试支持示例 (CMake 3.10特性演示)
enable_testing()  # 启用测试功能

# 添加测试可执行文件
# 查找Google Test
find_package(GTest REQUIRED)

add_executable(test_demo
    tests/test_demo.cpp
)

# 链接Google Test库
target_link_libraries(test_demo
    PRIVATE
        GTest::GTest
        GTest::Main
)
target_link_libraries(test_demo
    PRIVATE
        demo_lib
)

# 添加测试用例
add_test(NAME basic_test
    COMMAND test_demo --gtest_filter=TestDemo.BasicTest
)
add_test(NAME advanced_test
    COMMAND test_demo --gtest_filter=TestDemo.AdvancedTest
)

# 设置测试属性
set_tests_properties(basic_test
    PROPERTIES
        LABELS "quick"
        TIMEOUT 10
)
set_tests_properties(advanced_test
    PROPERTIES
        LABELS "extended"
        TIMEOUT 30
)

# 文件操作示例 (CMake 3.10特性演示)
# 1. configure_file 示例
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

# 2. 使用configure_file替代file(GENERATE)
set(BUILD_INFO_CONTENT "// Auto-generated build info\n"
                       "const char* BUILD_DATE = \"${CMAKE_SYSTEM_NAME}\";\n"
                       "const char* BUILD_TYPE = \"${CMAKE_BUILD_TYPE}\";\n")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/build_info.cpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/build_info.cpp)

# 创建一个使用生成文件的目标
add_library(build_info STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/build_info.cpp
)

# 字符串操作示例 (CMake 3.10特性演示)
# 1. 字符串连接
string(CONCAT FULL_PROJECT_NAME 
    "${PROJECT_NAME} " 
    "v${PROJECT_VERSION}"
)
message(STATUS "Full project name: ${FULL_PROJECT_NAME}")

# 2. 字符串大小写转换
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
message(STATUS "Upper case: ${PROJECT_NAME_UPPER}")
message(STATUS "Lower case: ${PROJECT_NAME_LOWER}")

# 3. 字符串查找和替换
string(FIND ${PROJECT_NAME} "Demo" DEMO_POS)
if(DEMO_POS GREATER_EQUAL 0)
    message(STATUS "'Demo' found at position: ${DEMO_POS}")
    string(REPLACE "Demo" "Example" PROJECT_NEW_NAME ${PROJECT_NAME})
    message(STATUS "New project name: ${PROJECT_NEW_NAME}")
endif()

# 4. 字符串子串
string(SUBSTRING ${PROJECT_NAME} 0 4 PROJECT_PREFIX)
message(STATUS "Project prefix: ${PROJECT_PREFIX}")

# 5. 字符串比较
if("${PROJECT_NAME}" STREQUAL "CMakeDemo")
    message(STATUS "Project name matches expected value")
endif()

# 现代CMake实践示例 (CMake 3.10特性演示)
# 1. 创建接口库
add_library(demo_interface INTERFACE)
target_include_directories(demo_interface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(demo_interface INTERFACE cxx_std_14)

# 2. 改进目标依赖关系
target_link_libraries(demo_lib
    PUBLIC
        common_options
        demo_interface
)

# 1. 首先收集子目录中的源文件
add_subdirectory(libs/math ${CMAKE_BINARY_DIR}/math_build)
add_subdirectory(libs/utils ${CMAKE_BINARY_DIR}/utils_build)

# 条件编译选项
option(BUILD_WITH_LOGGER "Build with logger functionality" ON)

# 创建math_lib和utils_lib目标
add_library(math_lib STATIC src/math_utils.cpp ${MATH_SOURCES})
target_include_directories(math_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/math>
    $<INSTALL_INTERFACE:include>
)

add_library(utils_lib STATIC src/logger.cpp ${UTILS_SOURCES})
target_include_directories(utils_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libs/utils>
    $<INSTALL_INTERFACE:include>
)

# 添加条件编译定义
if(BUILD_WITH_LOGGER)
    target_compile_definitions(utils_lib PRIVATE BUILD_WITH_LOGGER)
    message(STATUS "Building utils_lib with logger functionality")
else()
    message(STATUS "Building utils_lib without logger functionality")
endif()

# 2. 设置目标属性
set_target_properties(demo_lib PROPERTIES
    PUBLIC_HEADER "include/demo_lib.h"
)

set_target_properties(math_lib PROPERTIES
    PUBLIC_HEADER "include/math_utils.h"
)

set_target_properties(utils_lib PROPERTIES
    PUBLIC_HEADER "include/logger.h"
)

# 3. 最后配置安装目标
install(TARGETS demo_lib math_lib utils_lib build_info common_options demo_interface
    EXPORT CMakeDemoTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/utils
)

# 安装导出目标
install(EXPORT CMakeDemoTargets
    FILE CMakeDemoTargets.cmake
    NAMESPACE CMakeDemo::
    DESTINATION lib/cmake/CMakeDemo
)

# 安装包含目录
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY libs/math/ DESTINATION include/math)
install(DIRECTORY libs/utils/ DESTINATION include/utils)

# 4. 安装导出文件
install(EXPORT CMakeDemoTargets
    FILE CMakeDemoTargets.cmake
    NAMESPACE CMakeDemo::
    DESTINATION lib/cmake/CMakeDemo
)

# 5. 配置包文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeDemoConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeDemoConfig.cmake
    INSTALL_DESTINATION lib/cmake/CMakeDemo
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