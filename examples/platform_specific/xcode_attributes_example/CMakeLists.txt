# Xcode 属性示例 (跨平台版本)
cmake_minimum_required(VERSION 3.10)
project(XcodeAttributesExample)

# 添加可执行文件
add_executable(xcode_attributes_example main.cpp)

# Xcode特定的目标属性 (仅在使用Xcode生成器时生效)
# 完整属性列表参考：<mcurl name="Xcode属性文档" url="https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#xcode-scheme-properties"></mcurl>
# 关键参数说明：
# 1. 这些设置仅在Xcode生成器下生效
# 2. 影响Xcode项目文件生成但不影响其他生成器
if(CMAKE_GENERATOR STREQUAL "Xcode")
    # 设置Xcode项目属性 (保留作为参考)
    set_target_properties(xcode_attributes_example PROPERTIES
        XCODE_ATTRIBUTE_GCC_OPTIMIZATION_LEVEL "0"  # 调试时禁用优化(O0)
# 可选值：fast(Os)/faster(O1)/fastest(O2)/fastest,unroll-loops(O3)
        XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES"      # 仅构建活动架构
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC "YES"  # 启用ARC
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "12.0"
    )

    # 设置Xcode方案属性 (保留作为参考)
    set_property(TARGET xcode_attributes_example PROPERTY XCODE_SCHEME_ENABLE_SANITIZE_ADDRESS "YES")
    set_property(TARGET xcode_attributes_example PROPERTY XCODE_SCHEME_ENABLE_SANITIZE_THREAD "YES")
endif()

# 标准C++编译选项
target_compile_features(xcode_attributes_example PRIVATE cxx_std_11)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# 平台检测
# 平台兼容性检测
# APPLE变量由CMake自动检测macOS/iOS平台时设置
if(NOT APPLE)
    message(STATUS "Note: This example demonstrates Xcode-specific attributes")
    message(STATUS "Full functionality is only available when building with Xcode on macOS")
endif()