## 哈希表：unordered_map

```C++
unordered_map<typename1, typename2> mp;
```



- `mp.count(value)`：计算哈希表中value出现的次数



- 对`unordered_map`进行循环

```C++
for (auto& [a, b] : mp){ expressions };
```





## 排序算法

```C++
#include<algorithm>
bool is_sorted (ForwardIterator first, ForwardIterator last);
bool is_sorted (ForwardIterator first, ForwardIterator last, Compare comp);
```

其中，`ForwardIterator`是正向迭代器，例如`vector`数据类型可以直接使用`vector.begin()`或`vector.end()`。

`comp`用来指定判断标准，自定义大小顺序的比较，返回值为`bool`。











## typedef关键字与结构体定义

关键在于，若使用`typedef`定义结构体，结构体结束后的名称作为结构体的别名类型；与之相反，若不使用`typedef`定义结构体，则结构体定义后的名称作为变量使用。

```C++
// 使用typedef
typedef struct Student
{
    int a;
}Stu;
// Stu作为Student的别名，属于类型名称
// 进行变量初始化
Stu student_1;

// 不使用typedef
struct Teacher
{
    int b;
}Tea;

// 直接可以使用Tea
Tea.b = 3;
```









## 类模板

- 类模板的定义，定义前需要指定template中的类型参数

```C++
template <typename T>
class A
{
public:
    A();
    A(int i);
    A(int a[], int size);
    return_type A_func( params_list );
    T* list;
}
```

- 类模板实例化时，需要指定具体的模板类型

```C++
A<int> a;
```

- 类模板的成员函数在类外定义时，由于类模板的成员函数是一个普通的成员函数，类模板的每个实例（具体类型）都有自己版本的成员函数，因此**<u>在类外定义成员函数时也需要加入模板信息</u>**。

```C++
template <typename T>
return_type A<T>::A_func( params_list ){ expressions; }
```

- 若类外定义具体的构造函数和析构函数，也需要加入模板信息，只是一如既往不需要返回值类型

```C++
template <typename T>
A<T>::A(){};
```





## 类的前向声明

- 用途：类之间的互相使用，但是需要提前声明。

- C++的类可以进行前向声明。但是，仅仅进行前向声明而没有定义的类是不完整的，这样的类，**只能用于定义指针、引用、以及用于函数形参的指针和引用。**而不能定义对象(因为此时编译器只知道这是个类，还不知道这个类的大小有多大)，也不能访问类的对象，任何形式的访问都不允许(因为此时根本不知道有些什么成员)。等到类正式定义以后，就可以以各种方式使用该类了。

