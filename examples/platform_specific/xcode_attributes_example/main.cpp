#include <iostream>
#include <string>
#include <vector>

class ExampleClass {
public:
    // 模拟@property
    void setName(const std::string &name) { this->name = name; }
    std::string getName() const { return name; }
    
    // 模拟方法
    void printName() const {
        std::cout << "Name: " << name << "\n";
    }
    
private:
    std::string name;
};

int main() {
    ExampleClass example;
    example.setName("Xcode Attributes Example (Linux Port)");
    example.printName();
    
    // 模拟NSArray
    std::vector<std::string> array {"Hello", "World"};
    std::cout << "Array: ";
    for (const auto &item : array) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    
    std::cout << "Running on Linux\n";
    return 0;
}