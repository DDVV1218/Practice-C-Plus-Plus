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

## 刷题Tips

### 最大值最小值

有的题目中需要找到最大值或者最小值，因此我们需要提前初始化一个较小或者较大的值，以便于后续的比较和更新。在`python`中可以使用`float("inf")`来表示，在`C++`中可以如下表示：

```C++
#define MaxN 0x3f3f3f3f
#define MinN 0xc0c0c0c0
```

