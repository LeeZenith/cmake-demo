# Math库源文件配置

# 收集所有源文件
file(GLOB MATH_SOURCES *.c)

# 将源文件列表添加到父作用域
set(MATH_SOURCES ${MATH_SOURCES} PARENT_SCOPE)