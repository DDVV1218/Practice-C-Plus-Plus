## 编译过程

1. **Preprocessing**：预处理过程，将Source Code转化为后缀为`.i, .ii`的文件

   预处理过程主要进行文件包括（替换`#include`）、宏定义替换（`#define`及预定义宏）以及条件编译（指定对应代码是否编译）。条件编译通常是为了防止重复的代码块被重复编译降低程序运行效率，通常在头文件中使用。

   ```C++
   // 条件编译例子
   #ifndef _A_H_			// 若没有定义_A_H
   #define _A_H_			// 定义_A_H
   // contents of head file for A
   #endif
   ```

2. **Compilation**：编译，将`.i, .ii`文件通过编译器 (gcc, g++) 生成`.s`文件

   编译阶段主要进行语法分析、词法分析和语义分析，并且将代码优化后生成相应的汇编代码文件。

   编译阶段还会产生一个**符号表**，结合三个分析添加、填充和检查符号表的信息。

   符号表中主要包括符号的地址值、类型、占用空间的大小以及作用域。

3. **Assemble**：汇编，将`.s`文件处理为二进制的可重定向的机器码`.o, .obj`文件

4. **Linking**：链接，将一个项目中不同的`.o`文件链接起来，生成可执行机器代码`.exe`文件

   由于每个`.cpp`文件都会经过汇编产生`.obj`文件，每个`.o`文件都有自己的**Text、BSS和Data段**，链接器首先将多个二进制文件相应的段进行合并，建立映射关系并且合并符号表，进行符号解析，完成后给符号分配虚拟地址；分配地址后，将虚拟地址和符号对应起来，使得代码段的指令可以根据符号的地址执行相应的操作，最终由链接器生成可执行文件。

   - 静态链接：每个exe文件都会包含此静态库的二进制obj文件
   - 动态链接：每个exe文件在执行时，都会先使用小型连接器去和 **<font color='Magenta'>Dynamic Linkable Library</font>** 动态链接库进行链接，然后再进行程序的运行。



## C/C++内存四区

在程序运行之前，可执行文件`.exe`通常由 **<font color='skyblue'>BSS段、Data段和Text段</font>** 组成

- **Text**：又被称为代码区，主要存放source code转化而来的二进制机器码，方便操作系统读取运行

- **BSS**：Better Save Space，被称为未初始化数据区，用来存放程序中未初始化的全局变量和静态变量。此处的未初始化，也包括初始化为0的情况。由于这部分区域只需要记载地址起始位置和结束位置，不需要储存具体的值（因为都初始化为0），所以可以节省可执行文件在内存中的空间。
- **Data**：已初始化数据区，存放已经初始化的全局变量和全局静态变量

**Data**和**BSS**在程序运行后，又被统称为数据区或者全局区。

程序运行开始后，操作系统把物理硬盘的代码加载到运行内存当中，并开辟四个区域，其中包括代码区、全局区、堆区和栈区。紧接着程序找到`main()`函数入口并开始运行。

- 栈区：由编译器自动释放，存放函数的参数值、局部变量等。每当一个函数被调用时，<u>函数的返回类型</u>和一些调用的信息被存放在栈上。然后这个被调用的函数再为它的自动变量和临时变量在栈上分配空间。**<font color='skyblue'>栈区是从高地址位向低地址位</font>**增长的，是一块连续的内存区域。最大容量时系统预先定义好的。
- 堆区：用于动态分配内存，地址范围位于BSS和栈中间的地址区域。由程序员申请分配和释放。堆的地址位从**<font color='skyblue'>低地址位向高地址位</font>**增长，采用链式储存结构，因此分配的空间是<u>不连续</u>的！！！当申请堆空间时，库函数是按照一定的算法搜索可用的足够大的空间，因此堆的效率相对较低。

```C++
int dd_1 = 1;							// 全局变量，在DATA段
static int dd_2 = 2;					// 静态变量，在DATA段
extern int dd_3;						// 未初始化的全局变量，在BSS段
static int dd_4 = 0;					// 初始化位0的静态变量，在BSS段

int main()
{
    int dd_4;							// 局部变量，在栈上
    return 0;							// 返回值，在函数被调用开辟栈区时就创建了该地址
}
```



## Static关键字

`static`用于指定变量类型为静态变量，可以分为全局变量、局部变量和成员变量。

1. 全局静态变量：该全局变量的作用域仅限于定义的文件当中，不能在其他文件访问

2. 局部静态变量：在函数体内部定义，且只在函数被第一次调用时分配内存空间和初始化，分配的内存空间位于全局数据区，根据初始化的值不同存储在BSS段或DATA段

3. 静态成员变量：被类的所有实例共享，不属于类的单独实例内存空间当中。可以通过类名的方式直接引用。此外，由于类的定义在实例化前不会分配内存，因此**<font color='skyblue'><u>静态成员变量在类内定义，需要在类外显式初始化</u></font>**。

   需要注意的是，静态变量的定义一般不放在头文件中，防止多次重复初始化。

`static`也可以修饰类的成员函数，该函数被称为类的静态成员函数。

- 静态成员函数只能够调用类的静态成员变量，且在类外定义时不需要加入`static`关键字



## Const关键字

`const`：指明变量或对象的值时不能被更新的，引入目的是为了取代预编译指令。

`const`修改全局变量是储存在全局区，修饰局部变量时储存在栈区。`const`修饰的对象一旦创建后其值便不能再更改。由于类的数据成员只有声明，因此如果`const`修饰类的数据成员，那么使用构造函数来初始化此对象。

`const`修饰的全局变量仅在本文件内有效，如果其他文件也要使用，需要加入`extern`修饰。

`constexpr`：C++11引入的关键字，用于定义编译时就能确定值的常量表达式，要求表达式的值在编译的时候已知

`const`和`static`结合，通常用于定义类的静态常量成员。静态常量成员类内声明，类外定义

```C++
class DD
{
public:
    static const int dd;
}

const int DD:dd = 1;
```

！！！需要注意的是，在C++11版本之后，如果静态常量成员是**<font color='Magenta'>整形或者枚举类型</font>**，则可以在类内初始化！

1. 与引用相关

   `const`与`&`搭配又被称作常量引用，常量引用不能直接修改被引用的值；

   常量引用的对象可以是常量也可以是变量，但普通引用的对象不能是常量，如下例

   ```C++
   int i = 42;
   const int &r1 = i;
   const int &r2 = 42;
   const int &r3 = r1 * 2;
   int &r4 = r1 * 2;								// Error: 左边是变量，右边是常量
   ```

2. 与指针相关

   需要区分指针常量和常量指针......

   ```C++
   // 常量指针：指向常量的指针不能用于改变其所指对象的值，对指针修饰的变量类型增加const修饰
   const double pi = 3.1415;
   const double *cptr = &pi;
   
   // 指针常量：指针储存的值是一个常量，不能改变（此地址不能改变），对指针加入const修饰
   int dd = 1;
   int *const vv = &dd;
   // vv不可以修改
   ```

3. 与函数参数相关

   与赋值时的要求比较一致，因为形参在函数调用时也是在栈上按照形参的类型和传入的实参的值进行了初始化。标准即形参若为`const`类型，可以用常量或者变量赋值；但形参为变量类型，不能用`const`对象传入

4. 与函数返回值相关

   `const`修饰值时，返回值的类型是`const 数据类型`，可以由变量或者`const`的变量去初始化或赋值

   `const`修饰指针时，返回值可以是指针常量也可以是常量指针

   `const`修饰引用时，返回的是一个常量引用类型，即引用的对象和引用的对象的属性都不可以被改变

5. 与函数相关

   `const`限定函数只可以存在于成员函数中，表明该函数不会修改类的成员变量。`const`限定符放在函数成员的末尾，声明和定义都要加入

   ```C++
   class DD
   {
   public:
       int VV() const;
   }
   
   int DD:VV() const {};
   ```

## vector容器

1. `vector`是表示**可变大小数组**的序列容器
2. `vector`采用**连续存储空间**来储存元素，可以使用索引下标进行访问
3. 当新元素插入的时候，原数组需要被重新分配大小来增加储存空间，因此`vector`会分配一些额外的空间以适应可能的增长，因此需要区分`size`和`capacity`的区别
4. 与其他动态序列容器相比 (`deque, list, forward_list`)，`vector`在访问元素时更加高效，在末尾添加和删除元素相对高效；对于其他不在末尾删除和插入的操作，效率太低

```C++
// 定义，其中Alloc为创建一个内存池来加快内存分配的速度
template <class T, class Alloc = allocator<T> >;
```

### 构造函数

```C++
// (1). 默认构造，无参初始化
explicit vector(const allocator_type& alloc = allocator_type());
// example:
vector<int> v1;
```

```C++
// (2). 指定数量的元素初始化
explicit vector(size_type n, const value_type& val = value_type(),
               const allocator_type& alloc = allocator_type());
// example:
vector<int> v2(10, 1.0);
```

`size_type`在 C++ 中代表**无符号整型**，类似 `unsigned int`

`value_type`指的是模板手中的第一个参数`T`

```C++
// (3). 使用迭代器初始化，传入迭代器的起始位置和结束位置
template <class InputIterator>
vector (InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type());
// example:
vector<int> v3 = {1, 2, 3, 4, 5};
vector<int>::iterator it1 = v.begin() + 1;
vector<int> v4(it1, v.end() - 1);
for (auto v: v4) { std::cout << v << std::endl; }
// output: 2, 3, 4
```

```C++
// (4). 拷贝构造
vector(const vector& x);
```

### 数据插入

插入数据时，如果插入后的`size`大于当前的`capacity`，便会自动重新分配内存构造新的`vector`

1. `void push_back(const value_type& val)`：在末尾插入元素

2. 
   ```C++
   // (1). single element
   iterator insert(iterator position, const value_type& val);
   // (2). fill
   void insert(iterator position, size_type n, const value_type& val);
   // (3). range
   template<class InputIterator>
   void insert(iterator position, InputIterator first, InputIterator last);
   ```

3. `void resize(size_type n, value_type val = value_type());`：当重新构造的长度小于原本长度时，会删除多余的数据，当大于原本长度时，会填充默认的数据

4. ```C++
   //（1）range
   template<class InputIterator>
   void assign(InputIterator first, InputIterator last);
   // (2) fill
   void assigh(size_type n, const value_type& val);
   ```

### 数据删除

1. `void pop_back();`: 删除`vector`中的最后一个数据

2. `erase()`删除指定位置内的所有数据

   ```C++
   // (1) single value
   iterator erase(iterator position);
   iterator erase(iterator first, iterator last);
   ```

3. `void erase();`：删除所有数据

### vector其他性质

1. `size_type size() const;`：当前的元素个数

2. `size_type capacity() const;`：当前的容量大小

3. `bool empty() const;`：判断当前容器是否为空

4. 获取元素的方式有2种，使用运算符`[]`或`at()`

   ```C++
   // (1) []
   reference operator[](size_type n);
   // (2) at
   reference at(size_type n);
   ```

5. `front()`返回第一个元素的引用，`back()`返回最后一个元素的引用

## Stack（栈）

```C++
template<class T, class Container = deque<T>> class stack;
```

栈这种数据结构使用`LIFO`的技术，即`Last In First Out`。所有插入和删除的操作都是在栈顶进行的

常见用法与函数：

- `empty()`：检测栈是否为空
- `size()`：返回栈容器的大小
- `top()`：访问栈顶的元素
- `push()`：在栈顶压入元素
- `pop()`： 弹出栈顶元素（删除栈顶元素）
- `emplace()`：同`push()`插入元素

## Queue（队列）

```C++
template<class T, class Container = deque<T>> class queue;
```

队列这种数据结构使用`FIFO`技术，即`First In First Out`。队首的元素最先从队尾插入，也最先被弹出队首

常见用法和函数：

- `empty()`：检查队列是否为空
- `size()`：返回队列容器的大小
- `push_back()`：向容器队尾插入元素
- `pop_front()`：从容器头部弹出元素
- `front()`：返回队首元素
- `back()`：返回队首元素

## Dueue（双向队列）

在`Queue`的基础上，实现了两端均可以压入和弹出元素

常见用法和函数：

- `push_back()`：在队尾插入元素
- `push_front()`：在队首插入元素
- `pop_back()`：在队尾弹出元素
- `pop_front()`：在队首弹出元素
- `front()`：返回队首元素
- `back()`：返回队尾元素

## 哈希表：unordered_map

```C++
// key_type是键的类型，value_type是值的类型
unordered_map<key_type, value_type> mp;
```

- `mp.insert({key, value})`：向哈希表中插入键值对

- `mp.count(value)`：计算哈希表中value出现的次数
- `mp[key]`：访问哈希表中`key`下对应的`value`的值
- `mp.erase(key)`：删除哈希表中的键值对
- `mp.find(key)`：查找键为`key`的值，若不存在，返回`mp.end()`，因此可以使用`auto`关键字定义变量

- 对`unordered_map`进行循环

```C++
for (auto& [a, b] : mp){ expressions };
```

`unordered_map`不保证元素的顺序，与`std::map`相比，在元素数量较少时可能占用更多内存.



## 二叉搜索树

### 二叉搜索树的性能分析

由于插入和删除操作都需要首先查找，因此查找效率代表了二叉搜索树中各个操作的性能

**<font color='DeepSkyBlue'>最优情况下</font>**：二叉搜索树为完全二叉树（左右十分平均），平均查找次数为 **<font color='Violet'>O(log(N))</font>**

**<font color='DeepSkyBlue'>最差情况下</font>**：二叉搜索树为单支树（或类似单支），平均查找次数为 **<font color='Violet'>O(N)</font>**

## 平衡二叉树

- 由于二叉搜索树在不平衡时的效率较低，因此提出了平衡二叉树
- 定义平衡系数为节点左右子树的高度之差的绝对值，平衡二叉树在满足二叉搜索树的基础上，还需要满足每个节点的平衡系数小于1，保证整棵树的平衡性，从而提高二叉搜索树的效率
- 平衡二叉树在插入和删除操作时都会将整棵树平衡化，因此需要进行旋转调整，具体的调整情况有`LL`、`RR`、`RL`和`LR`四种，究其根本是通过旋转根节点和子树的方式使得两边的高度差中和

二叉搜索树在每次插入和删除时都需要进行平衡旋转的操作，在插入操作时需要对插入节点向上追溯的**<u>最小不平衡子树</u>**进行调整；而删除操作需要向上追溯**<u>所有不平衡子树</u>**进行调整。

二叉搜索树的效率大致为 **<font color='Violet'>O(log(N))</font>**

## 红黑树

红黑树是具备某些特性的二叉搜索树，但是它更加接近于平衡（没有平衡二叉树那么严格平衡）

红黑树需要满足五大特性：

1. 节点是<font color='red'>红色</font>或者<font color='skyblue'>黑色</font>的
2. 根节点一定是<font color='skyblue'>黑色</font>的
3. 叶子节点（外部节点、空节点）都是<font color='skyblue'>黑色</font>的，这里的叶子节点指的是最底层的空节点，需要注意
4. <font color='red'>红色</font>节点的父节点和子节点都是<font color='skyblue'>黑色</font>的，从根节点开始不能连续出现两个<font color='red'>红色</font>节点
5. 从任意节点到叶子节点的所有路径都包含相同数目的<font color='skyblue'>黑色</font>节点

其他衍生的规律有：

1. 从根节点到叶节点的最长路径不大于最短路径的2倍
2. 有 $n$ 个内部结点的红黑树高度 $h \le 2\log{(n+1)}$

红黑树的效率不会高于**<font color='Violet'>O(log(N))</font>**

## Set容器

`set`容器可以看作是具有`key`结构的二叉搜索树。因此`set`不仅可以用来储存数据，也可以对储存的数据进行排序和去重，保证了数据的**有序性**和**唯一性**。此外，`set`容器属于**关联式容器**，即元素之间不是通过内存中连续储存（比如`vector`），而是通过某种其他关系连接起来的。

```C++
template <class T,						// set::key_type/value_type
		  class Compare = less<T>,		// set::key_compare/value_compare
          class Alloc = allocator<T>	// set::allocator_type
         > class set;
```

其中多了一个`Compare`类型，因为`set`具有排序性，因此需要传递一个排序的标准。

### 构造函数

```C++
// (1) 显示构造
explicit set (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());

// (2) 范围构造
template <class InputIterator>
set(InputIterator first, InputIterator last,
    const key_compare& comp = key_compare(),
    const allocator_type& alloc = allocator_type());
// Examples:
vector<int> dd = {1, 2, 3, 4};
set<int> example(dd.begin() + 1, dd.end() - 1);	// example = {2, 3}

// (3) 拷贝构造
set (const set& x);
```

### 数据插入

数据插入主要使用`insert`方法，函数重载有三种：

​	（1）插入一个值

​	（2）在指定的迭代器位置插入一个值

​	（3）插入一个迭代器范围内的值

```C++
// (1) single value
pair<iterator, bool> insert (const value_type& val);
// (2) with hint
iterator insert (iterator position, const value_type& val);
// (3) range
template <class InputIterator>
void insert(InputIterator first, InputIterator last);
```

### 数据查找

数据查找使用`find`方法，返回类型为`iterator`，若找不到对应值，会返回`set.end()`一个指向末尾的迭代器

```C++
iterator find (const value_type& val) const;
// Example:
vector<int> dd = {1, 2, 3, 4, 5};
set<int> vv(dd.begin(), dd.end());
set<int>::iterator re_find = vv.find(6);	// re_find = dd.end();
```

### 数据删除

数据删除使用`erase`方法，可以指定删除的位置、具体值以及一个范围

```C++
// (1) position
void erase(iterator position);
// (2) target value
size_type erase(const value_type& val);		// 删除成功返回1，否则返回0
// (3) range
void erase(iterator first, iterator last);
```

### 数据计数

在`set`中的计数主要为了查找元素是否存在于`set`中，使用`count`实现

```C++
size_type count(const value_type& val);     // 查找成功返回1，否则返回0
```

### 数据上下界

`lower_bound`和`upper_bound`分别用来获得`set`中，不小于目标值的位置起点和大于目标值位置起点

```C++
iterator lower_bound(const value_type& val) const;
iterator upper_bound(const value_type& val) const;

// Examples:
vector<int> v = { 1,4,3,8,7,10,11,13,6};
set<int> tmp(v.begin(), v.end());
set<int>::iterator it_begin = tmp.lower_bound(5);
cout << *it_begin << endl;									// 由于set中没有5, out: 6
set<int>::iterator it_end = tmp.upper_bound(8);
cout << *it_end << endl;									// out: 10

```

### 其他性质

- `begin()`：返回容器第一个元素
- `end()`：返回容器第二个元素
- `clear()`：删除所有元素
- `empty()`：判断容器是否为空
- `max_size()`：返回容器可能包含的最大元素数目
- `size()`：返回当前容器的元素个数

### 比较函数

`set`中默认是通过`std::less()`来比较`key`的，若要自定义比较函数（类或者结构体），需要对`<`操作符或者`()`操作符进行重载，满足严格弱序化（永远让相同的元素返回`false`）。

`set`中每插入一个元素时，会首先将已有元素作为左操作数，插入元素作为右操作数进行比较；其次再更换顺序比较。若两次比较结果均为`false`，则判断元素相同，不予插入。

- （1）元素不是结构体

  ```C++
  // 自定义比较函数myComp，重载()运算符
  struct myComp{
      bool operator()(const your_type& a, const your_type& b){
          return a.data > b.data;
      }
  }
  set<int, myComp> s;
  ```

- （2）元素是结构体

  ```C++
  // 在结构体中重载 < 运算符
  struct Person{
  public:
      int id;
      int age;
      
      bool operator<(const Person& right) const {
          if (id == right.id) {return false};
          else
          {
              if (age != right.age)
              {
                  return age > right.age;
              }
              else
              {
                  return id > right.id;
              }
          }
      }
  }
  set<Person> dd
  ```

### multiset容器

`multiset`容器与`set`比较相似，底层也是由二叉搜索树实现的，但是它可以储存多个相同的值，在二叉搜索树中既可以放在根节点的左边，也可以放在根节点的右边。

在使用`count`方法时，`multiset`会具体返回查找元素的数量，不只限制于`0`和`1`。

在使用`find`方法时，会返回第一个找到的value的位置。







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





## 运算符优先级

- 后缀自增减`a++/a--`高于前缀自增减`++a/--a`高于比较运算符`>=/<=/==`







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



## 作用域

### 普通变量

1. 局部作用域（Local Scope）：函数内部声明的变量，作用域仅仅限于函数内部，称为局部变量

   储存：栈区；生命周期：被定义的函数内

2. 全局作用域（Global Scope）：函数外部定义的普通变量，作用域限定在整个文件范围内，称作全局变量。全局变量可以被文件内任何函数访问，也可以在其他文件中通过`extern`关键字进行引用

   储存：全局数据区；生命周期：整个程序的生命周期

3. 命名空间作用域（Namespace Scope）：普通变量在命名空间内声明的情况下，作用域限定在该命名空间内，称作命名空间作用域变量。

### 静态变量

1. 静态全局变量：静态全局变量声明在程序所有函数之外，作用域与全局变量相似，但是**<u>仅仅限于定义它的文件当中，不能被其他文件使用，即使被`extern`也不可以！</u>**

   但是需要注意的是，如果该文件被`#include`到了另一个文件中，也是可以使用的，因为`#include`本质是将文件代码全部复制到当下文件中。

   储存：全局数据区；作用域：当前文件；生命周期：整个程序的生命周期

2. 静态局部变量：声明在某个函数体中，其他函数不能使用。且所有函数公用一个静态局部变量，第一次调用函数之后，再次声明此静态变量只会调用已有内存中的数据。

   储存：全局数据区；作用域：当前文件的当前函数内；生命周期：整个程序的生命周期

   ```C++
   void Static()
   {
   	static int n = 1;
       n *= 2;
   }
   
   int main()
   {
   	Static();				// n = 2
       Static();				// n = 4
       Static();				// n = 8
       Static();				// n = 16
   }
   ```

### 类的静态成员

会一直存在于程序的整个生命周期中，声明方法为`static 数据类型 成员变量名`。静态成员变量属于类，该类的所有实例化对象共享一个静态成员变量。由于静态变量储存在全局数据区，且不需要类的实例化去生成，因此需要在***<u><font color='DeepSkyBlue'>类内声明，类外定义</font></u>***！

```C++
class Data
{
public:
    int n;
    static int m;
}
// 类外定义
int Data::m = 0;
```

### 类的静态成员函数

既然提到了类的静态成员，就顺带记录一下类的静态成员函数，也需要依照***<u><font color='DeepSkyBlue'>类内声明，类外定义</font></u>***的要求。

定义的规则为`static 返回值类型 函数名(参数);`，声明的形式和普通成员函数的类外定义是一致的。

静态成员函数可以直接引用类的静态成员变量（不需要加入类名或者实例的限定）

### 静态数据的储存

**<font color='DeepSkyBlue'>全局（静态）储存区</font>**：分为DATA段（全局初始化区）和BSS段（全局未初始化区）。DATA存放初始化的全局变量和静态变量；BSS段存放全局未初始化的全局变量和静态变量。程序结束运行时会自动释放。

BSS段在程序执行之前会被系统自动清0，所以未初始化的全局变量和静态变量在程序执行之前已经为0。储存在全局（静态）数据区的变量**<u><font color='Salmon'>会在程序运行开始时就完成初始化，也是唯一的一次初始化</font></u>**。

## 箭头运算符重载 ->

箭头运算符左变量的类型只能是两类：指向一个类的指针，类对象

按照箭头运算符左端变量的类型，可以将结果分为两类：

1. 若左值为一个类的指针，那么箭头运算符会调用指针所指对象的属性或者函数
2. 若左值为一个类对象，那么该对象需要重载箭头运算符，且返回值需要是一个类的指针或者一个类对象（套娃，又返回最开始左值的要求了）；紧接着，会对返回值再次调用箭头运算符，直到出现指针从而按照第一类标准运行

```C++
struct F
{
    void func() { printf("F::func()\n"); }
};

struct E
{
    F m_f;
    F* operator->() { return &m_f; }    //返回m_f对象的地址
};


struct D
{
    E m_e;
    E operator->() { return m_e; }  //返回m_e对象，该对象重载了->操作符
};

int main(void)
{
    D d;
    d->func();  //等价于d.operator->().operator->()->func()，打印F::func()

    return 0;
}
```

## 智能指针

智能指针是一种利用对象的声明周期来管理资源的技术，遵循的原理是**<font color='red'>RAII(Resouce Acquisition Is Initialization)</font>**

智能指针的提出是为了解决传统的`new/delete`中，忘记调用或无法调用`delete`从而引发内存泄露的问题

智能指针不是一个指针，而是一个类，在对象构造时调用构造函数获取资源，在对象生命周期结束时，编译器自动调用析构函数来释放资源

智能指针的拷贝问题：指针的拷贝通常需要深拷贝，因为涉及到动态申请资源的指令，防止因为浅拷贝而删除资源时导致剩余指针为野指针的情况。但是，如果又希望多个指针指向同一块内存区域，就需要浅拷贝。因此，智能指针中的`auto_ptr`和`shared_ptr`可以解决这个问题：

- `auto_ptr`采用管理权转移的方法进行赋值的拷贝和构造，当拷贝构造完成后，用于拷贝构造传参的对象指针会被更改为`nullptr`，赋值也等同于拷贝构造；这种方法非常危险，大多数生产中不再使用
- `shared_ptr`是C++11标准库中新纳入的智能指针，可以通过引用计数的方法，解决拷贝和赋值的问题

`unique_ptr`直接将拷贝构造和赋值禁止，没有买卖就没有杀害

### Shared_ptr

|                       接口函数                        |                             功能                             |
| :---------------------------------------------------: | :----------------------------------------------------------: |
| `shared_ptr(T* ptr = nullptr, Del del = Delete<T>())` | 构造函数，`del`为定制删除器，是一个仿函数对象，用于不同情况下的资源释放操作 |
|            `shared_ptr(shared_ptr<T>& sp)`            |                         拷贝构造函数                         |
|     `shared_ptr<T>& operator=(shared_ptr<T>& sp)`     |                      赋值运算符重载函数                      |
|                   `T& operator*()`                    |                     解引用操作符重载函数                     |
|                   `T* operator->()`                   |                    成员访问操作符重载函数                    |
|                      `T* get()`                       |              获取`shared_ptr`内部管理资源的指针              |
|                `long int use_count()`                 | 获取引用计数（当前智能指针管理的资源被多少智能指针共同管理） |
|                    `bool unique()`                    |        判断当前智能指针管理的资源是否只有它本身在管理        |

- `shared_ptr`在循环引用中，也会发生内存泄漏的问题，根本在于只是析构了第一层智能指针，由于智能指针计数不为0，导致真正的指针指向的对象没有被删除

  ```C++
  struct Node
  {
  	int _val;
  	std::shared_ptr<Node> _prev;
  	std::shared_ptr<Node> _next;
   
  	~Node()
  	{
  		std::cout << "~Node()" << std::endl;
  	}
  };
   
  int main()
  {
  	std::shared_ptr<Node> n1(new Node);
  	std::shared_ptr<Node> n2(new Node);
   
  	n1->_next = n2;
  	n2->_prev = n1;
   
  	return 0;
      // 返回后，先析构n2，再析构n1。由于析构n2的时候，n2指向的对象还有个智能指针（存在于n1中）指向它，因此n2本身指向的Node没有被删除；析构n1时，同样的道理，导致n1指向的对象没有被删除。
  }
  ```

- 通常使用`weak_ptr`来避免引用计数，它不参与资源的管理和释放，不能使用解引用和箭头来获取指向对象的信息，它的作用仅为避免引用计数。`weak_ptr`提供`lock()`、`expire()`函数来返回其中的指针或判断指针所指对象是否为空

## 刷题Tips

### 最大值最小值

有的题目中需要找到最大值或者最小值，因此我们需要提前初始化一个较小或者较大的值，以便于后续的比较和更新。在`python`中可以使用`float("inf")`来表示，在`C++`中可以如下表示：

```C++
#define MaxN 0x3f3f3f3f
#define MinN 0xc0c0c0c0
```

