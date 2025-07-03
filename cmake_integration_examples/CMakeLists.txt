# CMake集成Makefile项目的多种方式示例

# 方法1: ExternalProject (已实现)
# 适合作为项目依赖在构建时下载编译
include(ExternalProject)
ExternalProject_Add(
    makefile_project
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -C <SOURCE_DIR>
    INSTALL_COMMAND ""
)

# 方法2: add_custom_command/target
# 适合已有本地Makefile项目的集成
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/libmakefile.a
    COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project
    COMMENT "Building Makefile project"
)

add_custom_target(
    build_makefile
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/libmakefile.a
)

# 方法3: find_package + 包配置
# 需要Makefile项目支持安装到系统目录
find_package(MakefileProject QUIET)
if(NOT MakefileProject_FOUND)
    include(ExternalProject)
    ExternalProject_Add(
        makefile_project_installable
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project
        CONFIGURE_COMMAND ""
        BUILD_COMMAND make -C <SOURCE_DIR>
        INSTALL_COMMAND make -C <SOURCE_DIR> install
    )
    
    # 生成包配置文件
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/MakefileProjectConfig.cmake
    "set(MakefileProject_INCLUDE_DIRS \"/usr/local/include/makefile_project\")
    set(MakefileProject_LIBRARIES \"/usr/local/lib/libmakefile.a\")")
endif()

# 方法4: 直接系统调用
# 配置阶段执行
execute_process(
    COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project prepare
)

# 构建阶段执行
add_custom_command(
    TARGET my_app PRE_BUILD
    COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/external/makefile_project
    COMMENT "Pre-building Makefile project"
)

# 方法5: 混合构建系统
# 通过选项选择构建方式
option(USE_MAKEFILE "Use existing Makefile instead of CMake" OFF)

if(USE_MAKEFILE)
    add_custom_target(
        build_all
        COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    # 正常的CMake构建逻辑
    add_subdirectory(src)
endif()

# 创建说明文件
file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/INTEGRATION_README.md
"# CMake集成Makefile项目的方法

## 方法比较表
| 方法 | 适用场景 | 优点 | 缺点 |
|------|----------|------|------|
| ExternalProject | 需要下载和构建的外部项目 | 自动化程度高 | 配置复杂 |
| add_custom_command | 已有本地Makefile项目 | 灵活控制 | 手动管理依赖 |
| find_package | 支持安装的项目 | 符合CMake规范 | 需要项目支持安装 |
| 系统调用 | 简单的一次性操作 | 简单直接 | 难以跟踪依赖 |
| 混合构建 | 迁移过渡期 | 渐进式迁移 | 维护两份构建系统 |

## 推荐实践
1. 新项目优先使用纯CMake
2. 迁移期使用混合方式逐步替换
3. 外部依赖优先使用ExternalProject
4. 最终目标是通过包管理器管理所有依赖
")