# 循环示例 - 展示CMake中的foreach和while循环

# 创建一个测试列表
set(MY_LIST "A" "B" "C" "D")

# 基础foreach循环
message(STATUS "基础列表遍历:")
foreach(item IN LISTS MY_LIST)
    message(STATUS "  - 处理项目: ${item}")
endforeach()

# 范围循环(RANGE)
message(STATUS "\n范围循环(1-5):")
foreach(i RANGE 1 5)
    message(STATUS "  - 当前值: ${i}")
endforeach()

# 带步长的范围循环
message(STATUS "\n带步长的范围循环(0-10步长2):")
foreach(i RANGE 0 10 2)
    message(STATUS "  - 当前值: ${i}")
endforeach()

# while循环示例
message(STATUS "\nwhile循环示例:")
set(counter 3)
while(counter GREATER 0)
    message(STATUS "  - 倒计时: ${counter}")
    math(EXPR counter "${counter} - 1")
endwhile()

# 循环控制(通过if模拟break/continue)
message(STATUS "\n循环控制示例(模拟break):")
foreach(item IN LISTS MY_LIST)
    if(item STREQUAL "C")
        message(STATUS "  - 遇到C,提前退出循环")
        break()
    endif()
    message(STATUS "  - 处理项目: ${item}")
endforeach()

message(STATUS "\n循环控制示例(模拟continue):")
foreach(item IN LISTS MY_LIST)
    if(item STREQUAL "B")
        message(STATUS "  - 跳过B")
        continue()
    endif()
    message(STATUS "  - 处理项目: ${item}")
endforeach()