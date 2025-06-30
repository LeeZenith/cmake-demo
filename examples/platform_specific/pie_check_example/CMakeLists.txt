# CheckPIESupported 示例
cmake_minimum_required(VERSION 3.10)
project(PIECheckExample)

# 检查PIE支持
cmake_policy(SET CMP0083 NEW)
include(CheckPIESupported)
check_pie_supported()

# 添加可执行文件并设置PIE属性
add_executable(pie_check_example main.cpp)

# 如果支持PIE则启用
if(CMAKE_PIE_SUPPORTED)
    set_target_properties(pie_check_example PROPERTIES
        POSITION_INDEPENDENT_CODE TRUE
    )
    message(STATUS "PIE is supported and enabled")
else()
    message(STATUS "PIE is not supported on this platform")
endif()

# 设置输出目录以便检查结果
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)