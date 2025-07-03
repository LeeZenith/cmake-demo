# 函数和宏示例 - 展示CMake中的代码组织和重用

# 基本函数定义
function(print_hello)
    message(STATUS "Hello from function!")
endfunction()

# 调用函数
print_hello()

# 带参数的函数
function(greet name)
    message(STATUS "Hello, ${name}!")
endfunction()

greet("CMake Learner")

# 带返回值的函数
function(add_numbers a b result_var)
    math(EXPR sum "${a} + ${b}")
    set(${result_var} ${sum} PARENT_SCOPE)
    message(STATUS "在函数内计算: ${a} + ${b} = ${sum}")
endfunction()

add_numbers(3 5 RESULT)
message(STATUS "函数返回值: ${RESULT}")

# 宏定义(与函数类似但作用域不同)
macro(setup_target target_name)
    add_executable(${target_name} main.cpp)
    target_compile_features(${target_name} PRIVATE cxx_std_11)
    message(STATUS "设置目标: ${target_name}")
endmacro()

# 调用宏
setup_target(my_app)

# 展示函数和宏的作用域差异
set(outer_var "原始值")

function(change_var_function)
    set(outer_var "函数内修改的值" PARENT_SCOPE)
    message(STATUS "函数内outer_var: ${outer_var}")
endfunction()

macro(change_var_macro)
    set(outer_var "宏内修改的值")
    message(STATUS "宏内outer_var: ${outer_var}")
endmacro()

message(STATUS "\n作用域测试:")
message(STATUS "调用前outer_var: ${outer_var}")
change_var_function()
message(STATUS "调用函数后outer_var: ${outer_var}")
change_var_macro()
message(STATUS "调用宏后outer_var: ${outer_var}")

# 内置函数示例
message(STATUS "\n内置函数示例:")
string(TOUPPER "convert to uppercase" uppercase)
message(STATUS "字符串转大写: ${uppercase}")

list(APPEND MY_LIST "E" "F")
message(STATUS "列表操作后: ${MY_LIST}")