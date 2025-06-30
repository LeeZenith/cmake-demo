#include <iostream>

extern "C" void helper_function();

int main() {
#ifdef USING_CXX
    std::cout << "This is C++ code\n";
#endif

    helper_function();
    return 0;
}