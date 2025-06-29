#include "gtest/gtest.h"
#include "demo_lib.h"  // 假设demo_lib.h在include目录中

// 基本测试用例
TEST(TestDemo, BasicTest) {
    EXPECT_EQ(2, 1 + 1);
    EXPECT_TRUE(true);
}

// 高级测试用例 - 演示与demo_lib的交互
TEST(TestDemo, AdvancedTest) {
    // 假设demo_lib有一个add函数
    EXPECT_EQ(5, add(2, 3));
    
    // 演示字符串比较
    const char* greeting = get_greeting();  // 假设demo_lib有get_greeting函数
    EXPECT_STREQ("Hello, CMake!", greeting);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}