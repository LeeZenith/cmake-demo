#include <stdio.h>

void helper_function() {
#ifdef USING_C
    printf("This is C code\n");
#endif

    // 这个参数不会被警告，因为设置了-Wno-unused-parameter
    int unused_param = 0;
}