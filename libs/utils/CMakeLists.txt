# Utils库CMake配置

# 条件编译选项
option(BUILD_WITH_LOGGER "Build with logger functionality" ON)

# 收集所有源文件
file(GLOB UTILS_SOURCES *.c)

# 创建共享库
add_library(utils_lib SHARED ${UTILS_SOURCES})

# 设置库属性
set_target_properties(utils_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "logger.h"
)

# 设置包含目录
target_include_directories(utils_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 添加条件编译定义
if(BUILD_WITH_LOGGER)
    target_compile_definitions(utils_lib PRIVATE BUILD_WITH_LOGGER)
    message(STATUS "Building utils_lib with logger functionality")
else()
    message(STATUS "Building utils_lib without logger functionality")
endif()

# 安装配置
install(TARGETS utils_lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/utils
)