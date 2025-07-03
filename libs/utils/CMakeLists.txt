# Utils库源文件配置
# 本文件演示工具模块的构建配置
# 关键知识点：
# 1. 使用父作用域变量传递配置参数
# 2. 条件编译选项的传递方法

# 收集所有源文件
# 使用通配符收集C源文件
# 注意：此处演示GLOB的快捷用法
# 实际项目建议使用显式文件列表保证可靠性
file(GLOB UTILS_SOURCES *.c)

# 将源文件列表和条件编译选项添加到父作用域
# 向父作用域传递关键变量
# PARENT_SCOPE使这些变量在顶层CMakeLists中可用：
# - UTILS_SOURCES 用于集中构建
# - BUILD_WITH_LOGGER 控制日志功能的条件编译
set(UTILS_SOURCES ${UTILS_SOURCES} PARENT_SCOPE)
set(BUILD_WITH_LOGGER ${BUILD_WITH_LOGGER} PARENT_SCOPE)