# Visual Studio 属性示例
cmake_minimum_required(VERSION 3.10)
project(VSPropertiesExample)

# 设置VS解决方案全局属性
# USE_FOLDERS：启用解决方案文件夹分类
# VS_STARTUP_PROJECT：设置默认启动项目
set_property(GLOBAL PROPERTY USE_FOLDERS ON)  # 启用解决方案文件夹
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# 添加可执行文件
add_executable(vs_properties_example main.cpp)

# VS特定的目标属性
# MSVC变量由CMake在检测到Visual Studio编译器时自动设置
if(MSVC)
    # 设置VS项目属性
    set_target_properties(vs_properties_example PROPERTIES
        VS_GLOBAL_ROOTNAMESPACE "VSExample"
        VS_GLOBAL_PROJECT_TYPES "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}"  # VC++项目类型GUID
# 完整GUID列表参考：<mcurl name="VS项目类型GUID" url="https://www.cmakedocs.com/vs-guids/"></mcurl>
        VS_GLOBAL_Keyword "Win32Proj"
    )

    # 添加VS特定的编译选项
    target_compile_options(vs_properties_example PRIVATE
        /W4     # 警告级别4
        /sdl     # 启用附加安全检查
    )

    # 组织VS解决方案资源管理器结构
# 将目标放入"Examples"虚拟文件夹
    set_property(TARGET vs_properties_example PROPERTY FOLDER "Examples")
endif()

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)