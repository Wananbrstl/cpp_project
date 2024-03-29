# modern cmake
 从3.x版本之后的`CMake`的新特性，主要是从`director-oriend`到`target-oriend`的转变
主要的特性包括
- target：就是三种目标目标文件
    - 动态库：add_libraries()
    - 静态库：add_libraries()指定参数为`STATIC`
    - 可执行文件：add_executable()
- target相应的properties
    - 编译标识：target_compile_opt()
    - 预处理宏标识：target_compile_defines()
    - 头文件目录：target_link_directoires()
    - 链接：target_link_libraries()
    - 链接标识：target_link_opt()
- target之间的传递性
    - PRIVATE：如果b使用a，那么a只会在b中使用，不会传递到链接了b的目标中
    - PUBLIC：如果b使用a，那么使用b的目标同样可以使用a
    - INTERFACE：只是一个接口，利他主义，自己不会编译成任何东西，只是将这个接口传递下去
- INTERFACE的实现原理
我们还可以从它内部的实现机制来理解INTERFACE是什么

我们这里就以target_include_directories为例，其他的属性同理。

在cmake内部，有两个变量：INCLUDE_DIRECTORIES 和 INTERFACE_INCLUDE_DIRECTORIES 。

这两个变量存储的都是头文件目录。和系统的PATH变量类似，里面可以有多个路径，以分号分割。

但是区别是：INCLUDE_DIRECTORIES 是当前目标搜索的头文件目录，而INTERFACE_INCLUDE_DIRECTORIES 是下一个目标要搜索的头文件目录。

当目标B去搜索头文件的时候，就会在INCLUDE_DIRECTORIES 中搜索。这是简单清晰的。

而假如A引用了B（或者说目标A依赖于目标B），那么INTERFACE_INCLUDE_DIRECTORIES 中的路径就会赋给目标A的INCLUDE_DIRECTORIES。

所以，使用PRIVATE PUBLIC和INTERFACE就能控制是否将当前搜索路径传递给下一个目标。

PRIVATE就是不把当前的INCLUDE_DIRECTORIES 传递给INTERFACE_INCLUDE_DIRECTORIES 。

PUBLIC就是把当前的INCLUDE_DIRECTORIES 传递给INTERFACE_INCLUDE_DIRECTORIES 。

INTERFACE就是自己不使用当前的INCLUDE_DIRECTORIES ，但是把当前的INCLUDE_DIRECTORIES 传递给 INTERFACE_INCLUDE_DIRECTORIES 。

为什么这样改进？
原有的`CMake`过分依赖目录的层级关系，而`modern cmake`的设计可以类比面向对象的设计语言，每个目标(target)就是一个类，VISTABLE对应其可见性
- public: 自己使用，别人也使用
- private: 自己使用，不给别人使用
- interface: 自己不适用，只给别人使用


# 常用命令

## CLI使用命令
`cmake _Bbuild build -G xxx`：使用CMake去指定generator为xxx，可以是`make`或者`ninja`等工具，在`build`文件夹中生成相应内容

`cmake --build build`：使用CMake在build文件夹中构件整个项目，相当于一个统一的API接口，不同的编译器有不同的指令

## 常用的CMake语法
- `cmake_minimum_required(VERSION xx)`（必须）：指定CMake的版本号
- `project langh`（必须）：项目名称，
- `add_executable(target xxx)`
- `include_directories(xxx)`
- `target_link_libraries(target SHARED/STATIC xxx)`
- `target_include_directories(target include_dirs)`
- `target_compile_opt`
- `target_link_opt`
- `target_compile_defines`
- `set(variable xxxx  xxx)`
- `list(<APPEND|LENGTH|REMOVE_ITEM> <list> <elements....>)`
    - e.g: `list(APPEND list1 ${l1} ${l2} ${l3})`
- `file(GLOB <variable> "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)` to find any file
- `aux_source_directories(<dir> <variable>)`
- `add_defines(-Ddefine)` to add define before the execute
- `message(<level> message)`
    - (无) ：重要消息
    - STATUS ：非重要消息
    - `WARNING`：CMake警告，会继续执行
    - `AUTHOR_WARNING`：CMake警告 (dev), 会继续执行
    - `SEND_ERROR`：CMake错误，继续执行，但是会跳过生成的步骤
    - `FATAL_ERROR`：CMake错误，终止所有处理过程
- some predefine variabel
    - `PROJECT_SOURCE_DIR`：CMake根目录
    - `PROJECT_BINARY_DIR`：执行cmake命令的目录
    - `CMAKE_CURRENT_DIR`：当前CMake文件所在的目录
    - `CMAKE_CURRENT_BINARY_DIR`：target编译目录
    - `EXCUTABLE_OUTPUT_PATH`：重新定义目标二进制文件存放的位置
    - `LIBRARY_OUTPUT_PATH`：重新定义目标链接库存在目录
    - `PROJECT_NAME`：项目名称
    - `CMAKE_BINARY_DIR`：项目实际构件路径，如果在`build`目录中进行构件，那么得到的就是这个目录



# reference 
[知乎](https://zhuanlan.zhihu.com/p/493493849)

[b站视频1](https://www.bilibili.com/video/BV1MP4y127ha/?vd_source=0e276d55dbd9a04fc2b56c3d534b885d)

[b站视频2](https://www.bilibili.com/video/BV14h41187FZ/?spm_id_from=333.337.search-card.all.click&vd_source=0e276d55dbd9a04fc2b56c3d534b885d)

[博客](https://subingwen.cn/cmake/CMake-primer/)

[githubt reference](https://github.com/richardchien/modern-cmake-by-example#%E7%9B%B4%E6%92%AD%E6%97%B6%E7%9A%84-qa)
