# 单元测试(Unit Test)

## 开发流程

1. 整理需求文档
2. 构思具体的实现方案（需求哪些模块，增加哪些模块，添加公共函数）
3. 实现功能
4. 编译代码，解决语法错误
5. 调试、修复bug
6. 测试
7. 修复bug


## 单元测试

程序的所有逻辑都可以测试到，避免调试、测试的时候所有情跑不到。

1. 以函数为单位
2. 类进行测试

## 测试框架

1. 测试应该是独立且可重复的。
2. 测试应该有良好的组织以反映被测试的结构。
3. 测试应该是可移植和可复用的。
4. 当测试失败，应该详细提供问题信息。
5. 只需要关注测试内容。
6. 测试应该快速。


## 测试原则

1. 每一个测试要尽量小。
2. 要测试错误的情况，不能只测试不正确的情况。
3. 如果需要依赖别的，那么我们可以"编造"一些数据进行测试

# Google Test

GoogleTest包含了两大组件`googletest`（通常使用头文件`gtest/gtest.h`以及静态库`libgtest.a/libgtest_main.a`）以及`googlemock`（通常使用头文件`gmock/gmock.h`以及静态库`libgmock.a/libgmock_main.a`）。

- `GoogleMock`用于打桩测试
- `GoogleMock`包含于`GooglteTest`

GoogleTest测试层次：
- 项目（一个）
    - 单元测试（一个）
        - 测试套件(类、函数)
            - 测试案例（表现的具体方向）
                - ASSERT/EXPECT（多个）
        - 测试套件
            - 测试案例
                - ASSERT/EXPECT（多个）
        - ...

> 此外，断言支持使用输出流
```c++
EXPECT_EQ(2, sum(1, 1)) << "1+1=2"; // 可以配合输出流
```

## 特性

1. 函数的测试，类的测试，使用TEST（套件，案例/方向）
2. 测试夹具（相当于测试套件，测试案例之间传递数据）
    - 需要继承一个类`testing::Test`
    - 开始之前调用`Setup()`，结束时候调用`TarDown()`

3. gtest事件机制
    - 在单元测试、测试套件、测试案例的前后埋点===>断言返回、回调函数
    - `virtual void OnTestEnvironmentStart(const TestInfo& test_info) = 0;`
    - `virtual void OnTestSuitStart(const TestInfo& test_info) = 0;`
    - `virtual void OnTestCaseStart(const TestInfo& test_info) = 0;`

4. 内存泄漏检测
    - `new`和`delete`没有成对使用。
    - 通过重载`new`.`delete`构造和析构的埋点来判断是否会发生内存泄漏。(cpp)
    - hook技术。(c)

5. 打桩测试(googleMock)
    - 使用环境
        - 运行很慢，需要很多依赖库。
        - 运行很脆弱，使用的一些资源是不可靠的（网络）
        - 逻辑流程很难描述边界条件，边界条件不容易形成。
        - 想模拟出复杂的依赖关系。
    - 使用方法
        - 类来模拟复杂的逻辑行为。（模拟出依赖）
        - 调用哪些接口，调用的次数、调用顺序、参数、返回值。（核心）
        - 具体的实现方式。
