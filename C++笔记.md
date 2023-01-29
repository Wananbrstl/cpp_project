# C++笔记

[toc]

## 一、编译内存相关

### **1. c++程序编译的过程**

编译阶段分为四个过程，预处理 、编译、 汇编、链接

编译分未 静态(浪费空间，但提升性能)、动态(浪费性能、节省空间), 静态编译的文件后缀为:

### **2. 内存管理**

c++ 内存分区：栈、堆、全局/静态存储区，常量存储区、代码区

- 栈： 存放函数的局部变量，函数参数、返回地址等、由编译器自动分配和释放。(自动的， 想想函数的执行顺序， 先进后出)

- 堆： 由程序员自己动态申请和管理的空间，  如果不自己释放很可能造成内存泄露

- 全局区/静态区(.bss和.data字段)： 存放着全局变量和静态变量， 程序运行结束操作系统自动释放， c++中不区分存放的区域了

- 常量存储区(.data)： 存放

  ```c++
  #include<iostream>
  using namespace std;
  
  int g_var = 0;  // 全局段
  char *gp_var;   // 全局段
  
  int main(){
      int var;  // 栈区
      char *p_Var = "abc"; // 栈区
      char arr[] = "1234"; // 栈区
      static int s_Var = 0; // 静态存储区
      const int a = 0;    // 常量段
      free(p_var); 
      return 0;
  }
  ```

  

### **3. 栈与堆的区别**

- 申请方式： 栈 -> 系统自动分配， 堆 -> 程序员主动  
- 申请后系统的响应：分配栈空间， 如果剩余空间大于申请的空间，分配成功，否则分配栈溢出；申请堆空间，堆在内存中呈现得方式类似于链表(记录空闲地址空间得链表)，在空闲链表上找到一个比申请空间大的节点分配给程序，将该节点从链表中删除， 大多书系统中该块空间的首地址存放的是本次分配空间的大小，便于释放，将该空间上的剩余空间再次连接在空闲链表上。
- 栈在内存中是一块<font color = red> **连续的存储空间**</font>(内存的地址应该是从低到高)最大容量是系统预定好的， 堆在内存(从高到低)是<font color = red> **不连续的**</font>。
- 申请效率： 栈是系统自动分配的， 申请效率高， 但人为不能操控， 堆是程序员自己申请的，效率低但使用方便容易产生碎片。
- 存放的内容： 栈中存放的是局部变量。 函数的参数，堆中存放的内容是根据程序员自己控制的。

### **4. 变量的区别**

变量最主要的就是 <font color = blue>  作用域，生命周期</font>，从作用域来看，分为： 全局变量、静态全局变量、局部变量、静态局部变量。

- **全局变量**：具有全局作用域，全局变量只需要在一个源文件中定义，就可以作用于所有的源文件。其他不包含全局变量定义的源文件需要使用` extern`关键字再次声明这个全局变量。（文件之间是可以共享的）
- **静态全局变量**：具有文件作用域， 他与全局变量的区别在于如果包含多个源文件，那么它只能限定在定义的源文件中使用。所以， 两个不同的源文件之间的静态全局变量不是同一个变量。(文件之间不可以共享)，关键词为` static ` 
- **局部变量**： 具有局部作用域。它是自动对象(auto)，在程序运行过程中，不是一直存在， 而是限定在所在区域内。在c++中，其作用符号就是` {} `。
- **静态局部变量**：具有局部作用域，它只能被初始化一次，自从第一此被初始化直到程序运行结束都存在。与全局变量最大的区别在于，它只对作用的函数可见。比如: ` void func{ static int a = 0;} `， 那么这个变量` a `只对` func `可见。

分配内存空间看：

- 静态存储区： 全局变量， 静态全局变量， 静态局部变量
- 栈： 局部变量

初始化问题：

- 静态存储区变量和栈变量、堆变量的区别： 静态变量会被放在程序的静态数据存储区(.data字段)中， 这样下次调用会保持原来的赋值。而栈变量和堆变量不能保证在下一次调用的时候依然保持原来的值。
- 静态变量和全局变量： 静态变量用` static `告诉编译器， 自己只在自己作用的范围内可见。

### **5. 全局变量在头文件中有什么作用**

防止多此被包含！

### **6. 对象创建限制在堆或栈**



### **7. 内存对齐**

### **8. 类的大小**

类的大小指的是 类的实例化对象的大小，用`sizeof`对类型名操作时，结果是该类型的对象的大小。

计算原则：

- 遵循<font color = red>结构体对齐</font>的原则。
- 与<font color =red>普通成员变量</font>相关， 与**成员函数**和**静态成员**无关。所以，普通成员函数、静态成员函数、静态成员变量， 静态常数数据成员 都对 类的大小没有影响。因为静态数据成员被类的对象共享， 并不属于某个具体的类对象。（一句话就是， 静态数据成员是被共享的， 并不属于某个类）
- 虚函数对类的大小有影响， 因为虚函数表指针的影响。
- 虚继承对类的大小有影响， 因为虚基表指针带来的影响。
- 空类的大小是一个特殊的情况，空类的大小为1， 当用`new`来创造一个空类对象时， 为了保证不同对象的地址不同， 空类也占用存储空间。

```c++
#include<iostream>
using namespace std;

class A{
private:
	static int s_var; // 不影响类的大小
	const int c_varr; // 4字节
    int var;          // 4 + 4
    char var1; 		  // 8 + 1 + 3（对齐）
public:
    A(int temp) : c_varr(temp) {} 
    ~A() {}
};

class B{};
int main(){
    cout << sizeof(A) << endl; // 12
    cout << sizeof(B) << endl; // 1
}
```

Ps： 1 word = 2 byte = 16 bit

​         1 字 = 2 字节 = 16 位 

64位处理器就是一次处理16位

带虚继承的情况:

```c++
#include<iostream>
using namespace std;

class A{
private:
    static int s_var;
    const int c_var; // 4
    int var;         // 4 
    char var1;       // 4
public:
    A(int temp) : c_var(temp) {}
    ~A(){]
    virtual void f() {cout << "A::f" << endl;}
    virtual void g() {cout << "A::g" << endl;}
    virtual void h() {cout << "A::h" << endl;}
};
int main(){
    A ex1(4);
    A *p;
    cout << sizeof(p) << endl; //指针所占的空间与指针指向的数据类型无关！
    cout << sizeof(ex1) << endl; // 24字节
    return 0;
}
```

（注意：虚函数的个数并不影响所占内存的大小，因为类对象的内存中只保存了指向虚函数表的指针。指针8字节）

![image.png](https://pic.leetcode-cn.com/1627533111-mLIYxJ-image.png)

![image.png](https://pic.leetcode-cn.com/1627533145-uuHhhx-image.png)

![image.png](https://pic.leetcode-cn.com/1627533171-cBgnfQ-image.png)

![image.png](https://pic.leetcode-cn.com/1627533185-RxEOMV-image.png)

### 9. 内存泄漏

**内存泄漏**：由于疏忽或错误导致的程序未能释放已经不再使用的内存。
进一步解释：

- 泄露不是说物理上的消失， 而是在运行的过程中， 由于疏忽或者错误，浪费了内存。
- 常常指的是堆上内存的泄露， 因为堆是动态分配的， 而且是用户控制的。
- 使用`malloc` `calloc` `realloc` `new`等分配内存时， 需要释放内存，否则会导致泄露
- 指针重新赋值

```c++
char *p = new char(10);
char *p1 = new char(10);
p = p1;
```

开始时，指针 `p` 和 `p1` 分别指向一块内存空间，但指针 `p` 被重新赋值，导致 `p` 初始时指向的那块内存空间无法找到，从而发生了内存泄漏。

### 怎么防止内存泄漏？内存泄漏检测工具的原理？

防止内存泄露的方法：

1. 内部封装： 将内存的分配和释放封装到类中， 在构造的时候申请内存， 析构的时候释放内存。

```c++
#include <iostream>
#include <cstring> 

using namesapce std;

class A{
private:
    char *p;
    unsigned int p_size;
public:
    A(unsigned int n = 1) // 析构函数分配内存空间
    {
        p = new char[n];
        p_size = n;
    }
    ~A(){
        if(p){
            delete[] p; // 删除
            p = NULL; // 防止出现野指针；
        }
    
    char* GetPointer(){
        return p;
	}
};
void func(){
    A ex1(100);
    char* p = ex1.GetPointer();
    strcpy(p, "Test");
    cout << p << endl;
}
int main(){
    func();
    return 0;
}
```

说明：但这样做并不是最佳的做法，在类的对象复制时，程序会出现同一块内存空间释放两次的情况，请看如下程序：

```
void fun1()
{
    A ex(100);
    A ex1 = ex; 
    char *p = ex.GetPointer();
    strcpy(p, "Test");
    cout << p << endl;
}
```

简单解释：对于 fun1 这个函数中定义的两个类的对象而言，在离开该函数的作用域时，会两次调用析构函数来释放空间，但是这两个对象指向的是同一块内存空间，所以导致同一块内存空间被释放两次，可以通过增加计数机制来避免这种情况，看如下程序：

## 二、 C++语言特性

### c++11 新特性

一 `auto`类型自动推导

`auto`关键字：自动类型推导，编译器会在`编译环节`通过初始值推导出变量类型，通过`auto`定义的变量必须有初始值；

`auto`关键字的基本使用语法如下:

```c++
// c+11
vector<int> nums;
auto it = nums.begin();
```

注意：编译器推导出来的类型和初始值的类型并不完全一样，编译器会适当地改变结果类型使其更符合初始化规则。

二 `decltype`：类型推导

`decltype`关键词是"declare type"的缩写， 是声明类型的意思。和`auto`的功一样，都用来在编译时期进行自动类型推导。如果希望从表达式中推断出要定义的变量的类型，但是不想用该表达式的值初始化变量，这时就不能再用 `auto`。`decltype` 作用是选择并返回操作数的数据类型。

区别

```c++
auto var = val1 + val2
decltype(val1 + val2) var1 = 0;
```

`auto `根据 = 右边的初始值 `val1 + val2 `推导出变量的类型，并将该初始值赋值给变量` var`, `decltype` 根据` val1 + val2 `表达式推导出变量的类型，变量的初始值和与表达式的值无关。
`auto `要求变量必须初始化，因为它是根据初始化的值推导出变量的类型，而` decltype `不要求，定义变量的时候可初始化也可以不初始化。

三. Lambda表达式

`lamda`表达式，又被成为`lambda`函数或者**匿名函数**

定义为:

```c++
[capture list](parameter list) -> return type
{
	function body;
}
```

- capture list:捕获列表，指的是lambda所在函数中定义的局部变量的列表
- parameter list: 函数的参数列表
- function body: 函数体
- return type： 返回类型

举例子说明:

```c++
#include<iostream>
using namespace std;

int main(){
	int arr[4] = {4, 2, 3, 1};
	// 对arr中的数据进行排序
	sort(arr, arr+4, [=](int x, int y) -> bool{retur x < y;})
	for(int n: arr){
		cout << n << "  ";
	}
	return 0;
}
```

四. 范围`for`语句

举例子：

```c++
unordered_map<int, int> map;
for(auto& [a, b]: map){
	printf("map ( %d ) = %d\n", a,  b);
}
vector<int> res;
for(auto i : res)
	cout << i << " " << endl;
```

五. 右边引用
右值引用：绑定到右值的引用，用 `&&` 来获得右值引用，右值引用只能绑定到要销毁的对象。为了和右值引用区分开，常规的引用称为左值引用。
举例：

```
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int var = 42;
    int &l_var = var;
        int &&r_var = var;
        // error: cannot bind rvalue reference of type 'int&&' to lvalue of type 'int' 错误：不能将右值引用绑定到左值上
	int &&r_var2 = var + 40;// 正确， 将r_var2绑定到求和的结果上。
	return 0;
}
```

六.标准库`move()`函数

`move()` 函数：通过该函数可获得绑定到左值上的右值引用，该函数包括在 utility 头文件中。该知识点会在后续的章节中做详细的说明。

七 智能指针

八 `delete`函数和`default`函数

- `delete` 函数：`= delete` 表示该函数不能被调用。
- `default` 函数：`= default` 表示编译器生成默认的函数，例如：生成默认的构造函数。

```
#include <iostream>
using namespace std;

class A
{
public:
	A() = default; // 表示使用默认的构造函数
	~A() = default;	// 表示使用默认的析构函数
	A(const A &) = delete; // 表示类的对象禁止拷贝构造
	A &operator=(const A &) = delete; // 表示类的对象禁止拷贝赋值
};
int main()
{
	A ex1;
	A ex2 = ex1; // error: use of deleted function 'A::A(const A&)'
	A ex3;
	ex3 = ex1; // error: use of deleted function 'A& A::operator=(const A&)'
	return 0;
}
```

### C And CPP

首先说一下面向对象和面向过程：

面向过程的思路：分析解决问题所需的步骤，用函数把这些步骤依次实现。
面向对象的思路：把构成问题的事务分解为各个对象，建立对象的目的，不是完成一个步骤，而是描述某个事务在解决整个问题步骤中的行为。
区别和联系：

语言自身：C 语言是面向过程的编程，它最重要的特点是函数，通过 main 函数来调用各个子函数。程序运行的顺序都是程序员事先决定好的。C++ 是面向对象的编程，类是它的主要特点，在程序执行过程中，先由主 main 函数进入，定义一些类，根据需要执行类的成员函数，过程的概念被淡化了（实际上过程还是有的，就是主函数的那些语句。），以类驱动程序运行，类就是对象，所以我们称之为面向对象程序设计。面向对象在分析和解决问题的时候，将涉及到的数据和数据的操作封装在类中，通过类可以创建对象，以事件或消息来驱动对象执行处理。

应用领域：C 语言主要用于嵌入式领域，驱动开发等与硬件直接打交道的领域，C++ 可以用于应用层开发，用户界面开发等与操作系统打交道的领域。

C++ 既继承了 C 强大的底层操作特性，又被赋予了面向对象机制。它特性繁多，面向对象语言的多继承，对值传递与引用传递的区分以及 const 关键字，等等。

C++ 对 C 的“增强”，表现在以下几个方面：类型检查更为严格。增加了**面向对象**的机制、**泛型编程的机制**（Template）、异常处理、**运算符重载**、**标准模板库**（STL）、命名空间（避免全局命名冲突）。

### Python And CPP

区别：

语言自身：Python 为脚本语言，解释执行，不需要经过编译；C++ 是一种需要编译后才能运行的语言，在特定的机器上编译后运行。
运行效率：C++ 运行效率高，安全稳定。原因：Python 代码和 C++ 最终都会变成 CPU 指令来跑，但一般情况下，比如反转和合并两个字符串，Python 最终转换出来的 CPU 指令会比 C++ 多很多。首先，Python 中涉及的内容比 C++ 多，经过了更多层，Python 中甚至连数字都是 object ；其次，Python 是解释执行的，和物理机 CPU 之间多了解释器这层，而 C++ 是编译执行的，直接就是机器码，编译的时候编译器又可以进行一些优化。
开发效率：Python 开发效率高。原因：Python 一两句代码就能实现的功能，C++ 往往需要更多的代码才能实现。
书写格式和语法不同：Python 的语法格式不同于其 C++ 定义声明才能使用，而且极其灵活，完全面向更上层的开发者。

## 三、面向对象

### 什么是面向对象

三大特性

- 封装： c++中的`class`将类的各种`属性`和`行为`封装到了一起。
- 继承，子类继承父类的特征和行为，子类有父类的非 private 方法或成员变量，子类可以对父类的方法进行重写，增强了类之间的耦合性，但是当父类中的成员变量、成员函数或者类本身被 final 关键字修饰时，修饰的类不能继承，修饰的成员不能重写或修改。
- 多态：多态就是不同继承类的对象，对同一消息做出不同的响应，基类的指针指向或绑定到派生类的对象，使得基类指针呈现不同的表现方式。

### 重载、重写、隐藏

- 重载：是指同一可访问区内被声明几个具有不同参数列（参数的类型、个数、顺序）的同名函数，根据参数列表确定调用哪个函数，重载不关心函数返回类型。

```c++
class A
{
public:
    void fun(int tmp);
    void fun(float tmp);        // 重载 参数类型不同（相对于上一个函数）
    void fun(int tmp, float tmp1); // 重载 参数个数不同（相对于上一个函数）
    void fun(float tmp, int tmp1); // 重载 参数顺序不同（相对于上一个函数）
    int fun(int tmp);            // error: 'int A::fun(int)' cannot be overloaded 错误：注意重载不关心函数返回类型
};
```

- 隐藏：是指派生类的函数屏蔽了与其同名的基类函数，主要只要同名函数，不管参数列表是否相同，基类函数都会被隐藏。

```c++
#include <iostream>
using namespace std;

class Base
{
public:
    void fun(int tmp, float tmp1) { cout << "Base::fun(int tmp, float tmp1)" << endl; }
};

class Derive : public Base
{
public:
    void fun(int tmp) { cout << "Derive::fun(int tmp)" << endl; } // 隐藏基类中的同名函数
};

int main()
{
    Derive ex;
    ex.fun(1);       // Derive::fun(int tmp)
    ex.fun(1, 0.01); // error: candidate expects 1 argument, 2 provided
    return 0;
}
```

说明：上述代码中 ex.fun(1, 0.01); 出现错误，说明派生类中将基类的同名函数隐藏了。若是想调用基类中的同名函数，可以加上类型名指明 ex.Base::fun(1, 0.01);，这样就可以调用基类中的同名函数。

- 重写(覆盖)：是指派生类中存在重新定义的函数。函数名、参数列表、返回值类型都必须同基类中被重写的函数一致，只有函数体不同。派生类调用时会调用派生类的重写函数，不会调用被重写函数。重写的基类中被重写的函数必须有 virtual 修饰。

  

```
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void fun(int tmp) { cout << "Base::fun(int tmp) : " << tmp << endl; }
};

class Derived : public Base
{
public:
    virtual void fun(int tmp) { cout << "Derived::fun(int tmp) : " << tmp << endl; } // 重写基类中的 fun 函数
};
int main()
{
    Base *p = new Derived();
    p->fun(3); // Derived::fun(int) : 3
    return 0;
}
```

范围区别：对于类中函数的重载或者重写而言，重载发生在同一个类的内部，重写发生在不同的类之间（子类和父类之间）。
参数区别：重载的函数需要与原函数有相同的函数名、不同的参数列表，不关注函数的返回值类型；重写的函数的函数名、参数列表和返回值类型都需要和原函数相同，父类中被重写的函数需要有 virtual 修饰。
virtual 关键字：重写的函数基类中必须有 virtual关键字的修饰，重载的函数可以有 virtual 关键字的修饰也可以没有。

**隐藏和重写，重载的区别：**

- 范围区别：隐藏与重载范围不同，隐藏发生在不同类中。
- 参数区别：隐藏函数和被隐藏函数参数列表可以相同，也可以不同，但函数名一定相同；当参数不同时，无论基类中的函数是否被 virtual 修饰，基类函数都是被隐藏，而不是重写。

## 四、关键字库函数

### explict的作用

作用：用来声明类构造函数是显示调用的，而非隐式调用，可以阻止调用构造函数时进行隐式转换。只可用于修饰单参构造函数，因为无参构造函数和多参构造函数本身就是显示调用的，再加上 explicit 关键字也没有什么意义。

```c
class A {
    private:
        int a;
    public: 
        A(int x) : a(x) {} // 会发生隐式转换 
    	explicit A(int x) : a(x) {} // 不会发生隐式转换

        void print() const {
            cout  << "a = " << a << endl;
        }
};

int main(int argc, char **argv){
    A a = 10; // 发生隐式转换
    a.print(); 
    return 0;
}
```
### C与C++ static的区别
在 C 语言中，使用 static 可以定义局部静态变量、外部静态变量、静态函数
在 C++ 中，使用 static 可以定义局部静态变量、外部静态变量、静态函数、静态成员变量和静态成员函数。因为 C++ 中有类的概念，静态成员变量、静态成员函数都是与类有关的概念。

### Static 的作用

作用： 

`static`定义静态变量、静态函数

- 保持变量内容持久：`static`作用于局部变量，改变了其声明周期，但是没有改变其作用范围。

```c
#include <iostream>
using namespace std;

int fun() 
{
	static int var = 1;
	var += 1;
    return var;
}

int main()
{	
    for(int i = 0; i<10;i++) {
        cout << fun() << "  "; // 2 3 4 5 6 7 8 9 10 11
    }
    return 0;
}
```

- 隐藏：`static`作用于全局变量和函数，改变了全局变量和函数的作用域，使得全局变量和函数只能在定义的文件中使用，在源文件中不具有全局可见性（其他源文件，本身源文件没有变化）
- `static`作用于类的成员变量和成员函数使得类变量或者类成员函数与类相关，任意对象对其无关。

```c
#include <iostream>
using namespace std;
class A {
	private:
    	int var;
		static int s_var; //静态成员变量
	public :
    
    	void show()
        {
            cout << s_var++ << endl;
        }
    	// 静态成员函数不能访问非静态成员变量
    	static void s_show()
        {
            cout << s_var << endl;
        }
};
```

### Static在类中的注意事项

`static`静态成员变量：

- 静态成员变量在类内声明，在类外进行定义和初始化，在类外进行定义和初始化不要出现`static`关键字和`private`、`public`、`protected`访问规则。
- 静态成员变量相当于类作用域中的全局变量，被类的所有对象共享，包括派生类。
- 静态成员变量可以作用成员函数的参数，而普通函数不可以。
- 4.静态数据成员的类型可以是所属类的类型，而普通数据成员的类型只能是该类类型的指针或引用。

`static`成员函数：

- 静态成员函数不能调用非静态成员变量或者非静态成员函数，因为静态成员函数没有 this 指针。静态成员函数做为类作用域的全局函数。
- 静态成员函数不能声明成虚函数（virtual）、`const `函数和 `volatile` 函数。

> 为何static成员函数不能为const函数
>
> 当声明一个非静态成员函数为const时，对this指针会有影响。对于一个Test类中的const修饰的成员函数，this指针相当于Test const *, 而对于非const成员函数，this指针相当于Test *.
> 而static成员函数没有this指针，所以使用const来修饰static成员函数没有任何意义。
> volatile的道理也是如此。
>
> 为何static成员函数不能为virtual
>
> static成员不属于任何类对象或类实例，所以即使给此函数加上virutal也是没有任何意义的。
> 静态与非静态成员函数之间有一个主要的区别。那就是静态成员函数没有this指针。
> 虚函数依靠vptr和vtable来处理。vptr是一个指针，在类的构造函数中创建生成，并且只能用this指针来访问它，因为它是类的一个成员，并且vptr指向保存虚函数地址的vtable.
> 对于静态成员函数，它没有this指针，所以无法访问vptr. 这就是为何static函数不能为virtual.
> 虚函数的调用关系：this -> vptr -> vtable ->virtual function

### static全局变量和普通全局变量的异同

相同：

- 存储方式：普通全局变量和`static`全局变量都是静态存储方式

不同点：

- 作用域：普通全局变量的作用域是整个源程序，当一个源程序由多个源文件组成时，普通全局变量在各个源文件中都是有效的；静态全局变量则限制了其作用域，即只在定义该变量的源文件内有效，在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域限于一个源文件内，只能为该源文件内的函数公用，因此可以避免在其他源文件中引起错误。
- 初始化：静态全局变量只初始化一次，防止其他文件中使用

### define和typedef的区别

- define在预处理的阶段，会进行替换操作，没有正确性检查，只有在编译被展开的时候才会发现错误，`typedef`在编译时处理，有类型检查的功能，用来给一个已经有的类型名字取别名。
- 功能：`typedef` 用来定义类型的别名，方便使用。`#define` 不仅可以为类型取别名，还可以定义常量、变量、编译开关等。
- 作用域：`#define` 没有作用域的限制，只要是之前预定义过的宏，在以后的程序中都可以使用，而 `typedef` 有自己的作用域。
- 指针的操作：`typedef` 和 `#define` 在处理指针时不完全一样

```c
#define TYPE1 int *
typedef int* TYPE2 

TYPE1 p1, p2; // int* p1, p2; p1:int*, p2:int
TYPE2 p3, p4; // int* p1, p2; p1,p2:int *
```

### 使用宏比较大小，以及两个数中最小值

```c
#define MAX(x, y) ((X)>(Y)?(X):(Y))
#define MIN(X, y) ((x)>(y)?(y):(x))
// 为什么使用`()`?
// 如果使用 #define MAX(x,y) (x>y?x:y)
MAX(1+2, 3+4) --> (1+2>3+4?1+2:3+4) // error
// 但是试的时候没问题？
```
### inline的作用以及使用方法
**作用**：

- inline 是一个关键字，可以用于定义内联函数。内联函数，像普通函数一样被调用，但是在调用时并不通过函数调用的机制而是直接在调用点处展开，这样可以大大减少由函数调用带来的开销，从而提高程序的运行效率。

使用方法：

- 类内定义成员函数默认是内联函数
  在类内定义成员函数，可以不用在函数头部加 inline 关键字，因为编译器会自动将类内定义的函数（构造函数、析构函数、普通成员函数等）声明为内联函数，代码如下：
- 类外定义成员函数，若想定义为内联函数，需用关键字声明当在类内声明函数，在类外定义函数时，如果想将该函数定义为内联函数，则可以在类内声明时不加 inline 关键字，而在类外定义函数时加上 inline 关键字。
- 另外，可以在声明函数和定义函数的同时加上 inline；也可以只在函数声明时加 inline，而定义函数时不加 inline。只要确保在调用该函数之前把 inline 的信息告知编译器即可。

内联函数的作用：

- 消除函数调用的开销。
  在内联函数出现之前，程序员通常用 #define 定义一些“函数”来消除调用这些函数的开销。内联函数设计的目的之一，就是取代 #define 的这项功能（因为使用 #define 定义的那些“函数”，编译器不会检查其参数的正确性等，而使用 inline 定义的函数，和普通函数一样，可以被编译器检查，这样有利于尽早发现错误）。
- 去除函数只能定义一次的限制。
  内联函数可以在头文件中被定义，并被多个 .cpp 文件 include，而不会有重定义错误。这也是设计内联函数的主要目的之一。



关于减少函数调用的开销：

- 内联函数一定会被编译器在调用点展开吗？
  错，inline 只是对编译器的建议，而非命令。编译器可以选择忽视 inline。当程序员定义的 inline 函数包含复杂递归，或者 inlinie 函数本身比较长，编译器一般不会将其展开，而仍然会选择函数调用。
- “调用”普通函数时，一定是调用吗？
  错，即使是普通函数，编译器也可以选择进行优化，将普通函数在“调用”点展开。
- 既然内联函数在编译阶段已经在调用点被展开，那么程序运行时，对应的内存中不包含内联函数的定义，对吗？
  错。首先，如第一点所言，编译器可以选择调用内联函数，而非展开内联函数。因此，内存中仍然需要一份内联函数的定义，以供调用。
  而且，一致性是所有语言都应该遵守的准则。普通函数可以有指向它的函数指针，那么，内敛函数也可以有指向它的函数指针，因此，内存中需要一份内联函数的定义，使得这样的函数指针可以存在。
- 关于去除函数只能定义一次的限制：
  下述程序会报错：

```c
// 文件1
#include <iostream>

using namespace std;

void myPrint() {
	cout << "function 1";
}

// 文件2
#include <iostream>

using namespace std;

void myPrint() {
	cout << "function 2";
}

int main() {
	myPrint();  // error，会出现链接时错误， myPrint 函数被定义了两次。
}
```

- 下面的不会报错

```c
// 文件1
#include <iostream>

using namespace std;

inline void myPrint() {
	cout << "inline function 1";
}

// 文件2
#include <iostream>

using namespace std;

inline void myPrint() {
	cout << "inline function 2";
}

int main() {
	myPrint()	// 正常运行;
}
```

### inline 的工作原理



### new的作用

`new`是c++中的关键字，用来动态分配内存空间(堆区)

```c
int *p = new int[5];
```

### new 和malloc如何判断是否申请到内存

- malloc ： 成功申请到内存，返回指向该内存的指针，分配失败则返回`NULL`；
- `new`：内存分配成功，返回指向对象类型的指针；分配失败，抛出`bad_alloc`异常。

### deleta实现原理，以及delete与delete[]的区别

`delete`的实现原理：

- 首先执行该对象的析构函数。
- 进而通过调用`operator delete`的标准函数来释放所占用的内存空间。

`delete`与`delete[]`的区别：

- `delete`用来释放单个对象所占用的空间，只会调用一次。
- `delete[]`用来释放数据空间，会对数组中的每一个成员函数调用一次析构函数。

> 补充：
>
> 对于像int/char/long/int*等等简单数据类型，由于对象没有析构函数，所以用delete和delete []是一样的！都不会造成内存泄露！ 但通常为了规范起见，new []都配套使用delete []。
> 但是如果是C++自定义对象数组就不同了！由于delete p只调用了一次析构函数，剩余的对象不会调用析构函数，所以剩余对象中如果有申请了新的内存或者其他系统资源，那么这部分内存和资源就无法被释放掉了，因此会造成内存泄露或者更严重的问题。

### new与malloc的区别，delete与free的区别

new 和 malloc的区别

![image.png](https://pic.leetcode-cn.com/1644544880-MwtYMy-image.png)

在使用的时候，`delete`、`new`搭配，`malloc`、`free`搭配使用。

- `malloc`、`free`是库函数，而`new`、`delete`是关键字；
- `new`申请空间时候，不需要指定分配空间的大小，编译器会根据数据结构确定大小。
- `new`申请空间时，返回的类型是对象的指针类型，不需要强制转换，而`malloc`则返回的是指针，并不具体，如果分配失败则是`NULL`
- `new`分配失败会抛出异常，而`malloc`则是返回`NULL`
- 对于自定义的类型，new 首先调用 operator new() 函数申请空间（底层通过 malloc 实现），然后调用构造函数进行初始化，最后返回自定义类型的指针；delete 首先调用析构函数，然后调用 operator delete() 释放空间（底层通过 free 实现）。malloc、free 无法进行自定义类型的对象的构造和析构。
- `new` 操作符从自由存储区上为对象动态分配内存，而 `malloc` 函数从堆上动态分配内存。（自由存储区不等于堆）

```c
分配内存的位置：
	malloc 函数从堆上动态分配内存；
	new 从自由存储区，自由存储区可以是内存、栈、堆，甚至不分配，取决于 operator new 的实现
	（所以 malloc 能通过 realloc 直观的重新分配内存，new 没有类似的方法）
返回类型及安全性：
	new 返回对象类型的指针，类型与对象严格匹配，不存在类型转换问题，严格符合安全性
	malloc 返回 void*，需要通过强制类型转换将 void* 指针转换成我们需要的类型，存在安全隐患
内存分配失败时，new 抛出 bad_alloc 异常；malloc 返回 NULL
	（所以内存分配不足时，new 有它的处理办法——客户能够指定处理函数或重新制定分配器，但 malloc 没有类似的办法）
new 不需指定内存大小，malloc 需要显示指定内存大小
new/delete 调用了构造/析构函数；malloc/free 未使用
	（所以operator new /operator delete 的实现可以基于 malloc，把 malloc 当一个模块来用，但反过来不能用 new 来实现 malloc）
new/delete 可被重载；malloc/free 不可
```

### malloc的原理

原理：

- 当开辟的空间小于128k的时候，调用`brk()`函数，通过移动`_enddata`实现。
- 当开辟空间大于 128K 时，调用 `mmap()` 函数，通过在虚拟地址空间中开辟一块内存空间来实现。

底层实现：

- brk() 函数实现原理：向高地址的方向移动指向数据段的高地址的指针 _enddata。
- mmap 内存映射原理：
  - 进程启动映射过程，并在虚拟地址空间中为映射创建虚拟映射区域；
    调用内核空间的系统调用函数 mmap()，实现文件物理地址和进程虚拟地址的一一映射关系；
    进程发起对这片映射空间的访问，引发缺页异常，实现文件内容到物理内存（主存）的拷贝。

### C语言与C++中`Struct`的区别

- c语言中`struct`是用户自定义数据结构，而在c++中`struct`式抽象数据结构，支持成员函数的定义
- c语言中`struct`没有访问权限，是一些变量的集合体，在c++中可以有访问权限。
- c语言中`struct`定义的自定义数据类型，在定义该数据类型的时候要使用`struct A var;`；而在c++中不需要前面的`struct`。

### struct 与 union的区别

`union`是联合体，`struct`是结构体

区别：

1. 联合体和结构体都是由若干个数据类型不同的数据成员组成。使用时，联合体只有一个有效的成员；而结构体所有的成员都有效。
2. 对联合体的不同成员赋值，将会对覆盖其他成员的值，而对于结构体的对不同成员赋值时，相互不影响。
3. 联合体的大小为其内部所有变量的最大值，按照最大类型的倍数进行分配大小；结构体分配内存的大小遵循内存对齐原则。

```c
#include <iostream>
using namespace std;

typedef union
{
    char c[10];
    char cc1; // char 1 字节，按该类型的倍数分配大小
} u11;

typedef union
{
    char c[10];
    int i; // int 4 字节，按该类型的倍数分配大小
} u22;

typedef union
{
    char c[10];
    double d; // double 8 字节，按该类型的倍数分配大小
} u33;

typedef struct s1
{
    char c;   // 1 字节
    double d; // 1（char）+ 7（内存对齐）+ 8（double）= 16 字节
} s11;

typedef struct s2
{
    char c;   // 1 字节
    char cc;  // 1（char）+ 1（char）= 2 字节
    double d; // 2 + 6（内存对齐）+ 8（double）= 16 字节
} s22;

typedef struct s3
{
    char c;   // 1 字节
    double d; // 1（char）+ 7（内存对齐）+ 8（double）= 16 字节
    char cc;  // 16 + 1（char）+ 7（内存对齐）= 24 字节
} s33;

int main()
{
    cout << sizeof(u11) << endl; // 10
    cout << sizeof(u22) << endl; // 12
    cout << sizeof(u33) << endl; // 16
    cout << sizeof(s11) << endl; // 16
    cout << sizeof(s22) << endl; // 16
    cout << sizeof(s33) << endl; // 24

    cout << sizeof(int) << endl;    // 4
    cout << sizeof(double) << endl; // 8
    return 0;
}
```

### struct与class的异同

- `struct`和`class`都可以定义成员函数和成员变量，也都支持继承。
- `struct`中默认访问的级别是`public`，默认的继承级别也是`public`，`class`默认的是`private`，默认的继承也是`private`
- 当 `class `继承 `struct `或者 `struct `继承 `class `时，默认的继承级别取决于 `class `或 `struct `本身， `class`（private 继承），`struct`（public 继承），即取决于派生类的默认继承级别。

```c
#include<iostream>

using namespace std;

class A{
public:
    void funA(){
        cout << "class A" << endl;
    }
};

struct B: A{ // 由于 B 是 struct，A 的默认继承级别为 public
public:
    void funB(){
        cout << "class B" << endl;
    }
};

class C: B{ // 由于 C 是 class，B 的默认继承级别为 private，所以无法访问基类 B 中的 printB 函数

};

int main(){
    A ex1;
    ex1.funA(); // class A

    B ex2;
    ex2.funA(); // class A
    ex2.funB(); // class B

    C ex3;
    ex3.funB(); // error: 'B' is not an accessible base of 'C'.
    return 0;
}
```

### volatile的作用？是否具有原子性对于编译器的影响。

我们可以使用volatile关键字试图阻止过度优化，volatile基本可以做到两件事情：

（1）阻止编译器为了提高速度将一个变量缓存到寄存器内而不写回；（缓存一致性协议、轻量级同步）

（2）阻止编译器调整操作volatile变量的指令排序。

[C/C++ 中 volatile 关键字详解 | 菜鸟教程 (runoob.com)](https://www.runoob.com/w3cnote/c-volatile-keyword.html)

