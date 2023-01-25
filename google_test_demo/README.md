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

## CMake与GoogleTest

文件结构

```
.
├── CMakeLists.txt
├── bin
├── include
│   └── sum.h
├── src
│   └── sum.cpp
├── test
│   ├── CMakeLists.txt
│   └── test_sum.cpp
```

```cmake
./CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(sample) 

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

enable_testing()
add_subdirectoires(test)
```


```cmake
./test/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
find_package(GTest REQUIRED)

include_directoires(../include/)
include_directoires(${GTEST_INCLUDE_DIRS})

add_executable(test_demo test_sum.cpp ../src/sum.cpp)

target_link_library(test_demo ${GTEST_BOTH_LIBRARIES} pthread)
```

## Google Test模块的使用

### TEST（普通）宏

### TEST_F（夹具）宏

### TEST_P（带参数）宏

## Google Mock模块的使用

当我们测试一些组件/类的时候，可能会依赖很多复杂的依赖，这个时候，我们可以考虑使用Mock（打桩）模块来进行测试。

下面简单的说说打桩在白盒测试中的重要性：

1、比如银行业务，需要测试业务模块。此时，不可能去操作真实的数据库，并且搭建新的数据库可能比较复杂或者耗时。那么就可以用gmock将数据库接口地方打桩，来模拟数据库操作。

2、比如要测试A模块，必过A模块需要调用B模块的函数。如果B模块还没有实现，此时，就可以用gmock将B模块的某些接口打桩。这样就可以让A模块的测试继续进行下去。

3、比如网关设备，在用gtest测试device模块的时候，必须有真实的设备才能让测试进行下去。如果用gmock模拟一套sdk接口，那么无需真实的设备也能让测试进行下去。（本条仅限公司内部阅读）


### 例子

Fake、Mock、Stub

- Fake对象有具体的实现，但采取一些捷径，比如用内存替代真实的数据库读取
- Stub对象没有具体的实现，只是返回提前准备好的数据
- Mock对象和Stub类似，只是在测试中需要调用时，针对某种输入指定期望的行为，Mock和Stub的区别是，Mock除了返回数据还可以指定期望以验证行为。

### 一个乌龟例子

一个纯虚类
```c++
class Turtle {
	...
	virtual ~Turtle() {};
	virtual void PenUp() = 0;
	virtual void PenDown() = 0;
	virtual void Forward(int distance) = 0;
	virtual void Turn(int degrees) = 0;
	virtual void GoTo(int x, int y) = 0;
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
};
```

MOCK方法定义
```c++
#include "gmock/gmock.h"

class MockTurtle : public Turtle {
public:
	...
	MOCK_METHOD(void, PenUp, (), (override));
	MOCK_METHOD(void, PenDown, (), (override));
	MOCK_METHOD(void, Forward, (int distance), (override));
	MOCK_METHOD(void, Turn, (int degrees), (override));
	MOCK_METHOD(void, GoTo, (int x, int y), (override));
	MOCK_METHOD(int, GetX, (), (const, override));
	MOCK_METHOD(int, GetY, (), (const, override));
};
```

创建Mock类的步骤：

1. MockTutle继承Tutle
2. 找到Tutle的一个虚函数
3. 在public的部分，写一个MOCK_METHOD()
4. 将虚函数的函数签名复制进MOCK_METHOD()中，加两个逗号：
5. 一个在返回类型和函数名之间，另一个在函数名和参数列表之间

例如：void PenDown() 有三部分：void、PenDown、和()，这三部分就是MOCK_METHOD的前三个参数

如果要模拟const方法，添加一个包含const的第四个参数，必须到括号建议添加override关键字。所以对于const方法，第四个参数变为（const, override），对于非const方法，第四个参数变为override。这不是强制性的。重复步骤直至完成要模拟的所有虚拟函数在测试中使用Mock

### 在测试中使用Mock的步骤

1. 从testing名称空间导入gmock.h的函数名(每个文件只需要执行一次)
2. 创建一些Mock对象
3. 指定对它们的期望(方法将被调用多少次? 带有什么参数? 每次应该做什么? 返回什么值 等等)
4. 使用Mock对象；可以使用googletest断言检查结果。如果mock函数的调用超出预期或参数错误，将会立即收到错误信息。
5. 当Mock对象被销毁时，gmock自动检查对模拟的所有期望是否得到满足

```c++
#include "path/to/mock-turtle.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;                         	// #1

TEST(PainterTest, CanDrawSomething) {
	MockTurtle turtle;                              // #2
	EXPECT_CALL(turtle, PenDown())                  // #3
		.Times(AtLeast(1));

	Painter painter(&turtle);                       // #4

	EXPECT_TRUE(painter.DrawCircle(0, 0, 10));      // #5
}
```
在这个例子中,我们期望tutle的PenDown()至少被调用一次。如果在tutle对象被销毁时,PenDown()还没有被调用或者调用两次以上，测试会失败。

### 指定期望

EXCEPT_CALL(指定期望)是使用Google Mock的核心。EXCEPT_CALL的作用是两方面的：

1. 告诉这个Mock（假）方法如何模拟原始方法：

我们在EXPECT_CALL中告诉Google Mock，某个对象的某个方法第一次被调用时，会修改某个参数，会返回某个值，第二次调用时， 会修改某个参数，会返回某个值......

2. 验证被调用的情况

我们在EXPECT_CALL中告诉Google Mock，某个对象的某个方法总共会被调用N次（或大于N次，小于N次）。如果

最终次数不符合预期，会导致测试失败。

#### 基本语法

```c++
EXPECT_CALL(mock_object, method(matchers))
	.Times(cardinality)
	.WillOnce(action)
	.WillRepeatedly(action);
```
mock_object是对象
method(matchers)用于匹配相应的函数调用
cardinality指定基数(被调用次数情况)
action指定被调用时的行为

#### 例子
```c++
using ::testing::Return;
...
EXPECT_CALL(turtle, GetX())
	.Times(5)
	.WillOnce(Return(100))
	.WillOnce(Return(150))
	.WillRepeatedly(Return(200));
```

这个EXPECT_CALL()指定的期望是：在turtle这个Mock对象销毁之前，turtle的getX()函数会被调用五次。第一次返回100，第二次返回150，第三次及以后都返回200。指定期望后， 5次对getX的调用会有这些行为。但如果最终调用次数不为5次，则测试失败。

#### 怎么调用
```c++
using ::testing::_;
using ::testing::Ge;
// 只与Forward(100)匹配
EXPECT_CALL(turtle, Forward(100));
// 与GoTo(x,y)匹配, 只要x>=50
EXPECT_CALL(turtle, GoTo(Ge(50), _));
```
