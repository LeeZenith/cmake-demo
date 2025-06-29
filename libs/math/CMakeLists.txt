# Math库CMake配置

# 收集所有源文件
file(GLOB MATH_SOURCES *.c)

# 创建静态库
add_library(math_lib STATIC ${MATH_SOURCES})

# 设置库属性
set_target_properties(math_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "add.h;sub.h"
)

# 设置包含目录
target_include_directories(math_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 安装配置
install(TARGETS math_lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/math
)