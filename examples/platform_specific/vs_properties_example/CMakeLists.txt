# Visual Studio 属性示例
cmake_minimum_required(VERSION 3.10)
project(VSPropertiesExample)

# 设置VS全局属性
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # 启用解决方案文件夹
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# 添加可执行文件
add_executable(vs_properties_example main.cpp)

# VS特定的目标属性
if(MSVC)
    # 设置VS项目属性
    set_target_properties(vs_properties_example PROPERTIES
        VS_GLOBAL_ROOTNAMESPACE "VSExample"
        VS_GLOBAL_PROJECT_TYPES "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}"  # VC++项目类型GUID
        VS_GLOBAL_Keyword "Win32Proj"
    )

    # 添加VS特定的编译选项
    target_compile_options(vs_properties_example PRIVATE
        /W4     # 警告级别4
        /sdl     # 启用附加安全检查
    )

    # 添加VS解决方案文件夹
    set_property(TARGET vs_properties_example PROPERTY FOLDER "Examples")
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)