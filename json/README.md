# JSON

## 什么是JSON
JSON(JavaScript )


## Tips

### 头文件的定义

### 宏的定义
测试中，经常这么写：
```
#define EXCEPT_EQ_BASE(equality, expect, actual)\
    do {\
        if(equality) \
            ...\
        else {\
            fprintf(stderr, "%s:%d : except : ", f );\
        }\
    }while(0);

#define EXCEPT_EQ_INT(except, actual)\
    EXCEPT_EQ_BASE((except) == (actual), except, actual)

```
