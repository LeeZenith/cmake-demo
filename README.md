# Modern CMake 特性示例

这个项目展示了现代CMake的几个高级特性，分为两组示例：

## 1. 高级生成器表达式

### `$<TARGET_PROPERTY:...>` 示例
演示如何使用生成器表达式访问目标属性。

构建和运行：
```bash
cd examples/advanced_generator_expressions/target_property_example
cmake -B build && cmake --build build
./build/bin/target_property_example
```

### `COMPILE_LANGUAGE` 示例
展示如何根据编译语言设置不同选项。

构建和运行：
```bash
cd examples/advanced_generator_expressions/compile_language_example
cmake -B build && cmake --build build
./build/bin/compile_language_example
```

## 2. 平台特定特性

### 跨平台PIE检查
演示如何使用`CheckPIESupported`模块。

构建和运行：
```bash
cd examples/platform_specific/pie_check_example
cmake -B build && cmake --build build
./build/bin/pie_check_example
```

### Visual Studio属性
展示如何设置VS特定的项目属性。

构建（在Visual Studio中）：
```bash
cd examples/platform_specific/vs_properties_example
cmake -B build -G "Visual Studio 16 2019"
```

### Xcode属性
展示如何设置Xcode特定的项目属性。

构建（在Xcode中）：
```bash
cd examples/platform_specific/xcode_attributes_example
cmake -B build -G Xcode
```

## 构建所有示例

要构建所有示例：
```bash
cmake -B build && cmake --build build
```

构建完成后，所有可执行文件将位于`build/bin`目录下。