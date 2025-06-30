#include <iostream>

int main() {
#ifdef EXTRA_FEATURE
    std::cout << "Extra feature is enabled\n";
#endif

#ifdef USING_STATIC_LIB
    std::cout << "Using static library\n";
#elif defined(USING_SHARED_LIB)
    std::cout << "Using shared library\n";
#endif

    return 0;
}