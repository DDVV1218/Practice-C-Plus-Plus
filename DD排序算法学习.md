# 排序算法总结

## 一、插入排序

把待插入的元素逐个插入到一个已经排序好的有序序列中，直到所有记录都插入完成

最直观的例子：整理扑克牌

实现该算法时，使用指针从尾部开始遍历，若插入元素排在该元素之前，则将该元素向后移动，直到插入该元素

插入排序算法的时间复杂度为 <font color='PaleGreen'>$O(n^2)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(1)$</font> 

```C++
void InsertSort(int* arr, int size)
    // arr为需要排序的数组，size为该数组的大小
    // 从arr的第一个元素开始，对每个元素直接插入法
{
    for (int i = 0; i < size - 1; i++)
    {
        // 单趟插入排序
        // 基本思想：[0, end]区间的序列有序，向其中插入
        int end = i;
        int tmp_val = arr[end + 1]; // 待插入的元素
        while (end >= 0)
        {
            if (tmp_val < arr[end])
            {
                arr[end + 1] = arr[end];
                end--;
            }
            else
            {
                arr[end + 1] = arr[end];
                arr[end] = tmp_val;
                break;
            }
        }
        if (end == -1) {arr[0] = tmp_val;}
    }
}
```

## 二、希尔排序

希尔排序法又称作缩小增量法，基本思想如下：

1. 先选定一个整数，把待排序文件中的所有记录分组
2. 所有距离为该整数的样本分在一个组内，对组内进行插入排序
3. 然后缩小整数的值，不断重复上述过程
4. 当整数为1时，即为最终的插入排序，结束后完成希尔排序

- 当选定的整数（又称作GAP）大于1时，都是预排序过程，使得整个数组接近有序。数组越有序，直接插入法的效率越高

- 希尔排序是一个不稳定排序法，不稳定意为相同大小的元素经过排序后的前后顺序有可能改变

希尔排序的时间复杂度约为<font color='PaleGreen'>$O(n^2{1.25})-O(1.6*n^{1.25})$</font>，空间复杂度为<font color='PaleGreen'>$O(1)$</font>

```C++
void ShellSort(int* arr, int size)
{
    int gap = 1;
    while (gap < size / 3)
    {
        gap = 3 * gap + 1;
    }
    
    while (gap >= 1)
    {
        for (int i = gap; i < length; i++)
        // 对GAP分的组进行直接插入排序
        {
            for (int j = i; j >= gap; j -= gap)
            {
                if (arr[j] < arr[j - gap]) {std::swap(arr[j], arr[j - gap]);}
            }
        }
        gap /= 3;
    }

}
```

## 三、选择排序

选择排序在未排序的序列中找到最大（小）元素，存放在序列的起始位置，以此类推直到元素排序完毕

选择排序算法的时间复杂度为 <font color='PaleGreen'>$O(n^2)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(1)$</font> 

```C++
void SelectSort(int* arr, int size)
    // 假设由小到大排列
{
    for (int i = 0; i < size; i++)
    {
        int min_value = arr[i];
        int min_index = i;
        for (int j = i; j < size; j++)
        {
            if (arr[j] < min_value)
            {
                min_value = arr[j];
                min_index = j;
            }
		}
        
        std::swap(arr[i], arr[min_index]);
	}
}
```

## 四、冒泡排序

冒泡排序和选择排序的思路很接近，只不过是通过左右元素的比较，将定义下较大的元素向队尾移动，每次循环都会将最大的元素移到列表最后，从而实现排序

冒泡排序算法的时间复杂度为 <font color='PaleGreen'>$O(n^2)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(1)$</font> 

```C++
void BubbleSort(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) {std::swap(arr[j], arr[j + 1]);}
		}
    }
}
```

## 五、快速排序

快速排序法是对冒泡排序法的一种改进，本质上是二分法的思想

通过一次循环将要排序的数据分割成独立的两部分，其中一部分的所有数据都要比另一部分要小。然后再按照此方法对这两部分数据分别进行快速排序，可以使用递归的方式进行

通常来说，需要设定一个分隔值，使得分隔值左边的数据都小于分隔值，分隔值右边的数据都大于分隔值，需要做的就是将分隔值在一次循环遍历中放在正确的位置，并在这个过程中左右移动元素

分隔值一般可以取最左侧或者最右侧的元素

快速排序算法的时间复杂度为 <font color='PaleGreen'>$O(nlog(n))$</font> ，空间复杂度为 <font color='PaleGreen'>$O(nlog(n))$</font> 

```C++
void QuickSort(int* arr, int high, int low)
{
    if (low >= high) { return; } // 防止出现当 i = low或high时，low > high的情况
    int i = low, j = high;
    int target = arr[low];
    while (i < j)
    {
        // 右侧寻找小于标定值的元素
        while (i < j && arr[j] >= target) { j--; }
        while (i < j && arr[i] <= target) { i++; }
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[low], arr[i]);
    QuickSort(arr, low, i - 1);
    QuickSort(arr, i + 1, high);
    
}
```

## 六、计数排序

计数排序适用于范围集中且重复数据较高的数据，其核心在于将输入的数据值转化为键储存在额外开辟的空间中。因此计数排序要求输入的数据必须有**<u>确定的范围的整数</u>**

快速排序算法的时间复杂度为 <font color='PaleGreen'>$O(n+k)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(k)$</font> 

```C++
void CountSort(int* arr, int length)
{
    int min_val = arr[0], max_val = arr[0];
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max_val) { max_val = arr[i]; }
        if (arr[i] < min_val) { min_val = arr[i]; }
    }
    
    // 开辟一个新的空间
    int* new_array = new int[max_val - min_val + 1];
    // 计数
    for (int i = 0; i < length; i++)
    {
        new_array[arr[i] - min_val]++;
    }
    
    // 回写排序
    int k = 0;
    for (int j = 0; j < (max_val - min_val + 1); j++)
    {
        while (new_array[j]--)
        {
            arr[k++] = j + min;
        }
    }
    
}
```

## 堆排序

堆（Heap）时一类特殊的数据结构，可以被看作是一颗完全二叉树的数组对象

堆的性质有以下两点：

1. 堆中某个节点的值总是不大于或不小于其父节点的值
2. 堆总是一颗完全二叉树

若索引从1开始标注，由上至下从左至右标注符合堆特性的完全二叉树，设树的深度为 $k$，且 $k$ 层所有的结点都连续集中在最左侧，可以得到如下规律：

1. `parent(i) = i / 2`
2. `left child(i) = 2 * i`
3. `right child(i) = 2 * i  + 1`

当有一个新的元素要插入堆中时，先将其放置在最后的位置，再逐层向上比较更新父节点的值

```C++
// 以最大堆为例子
void HeapShiftUp(vector<int>& arr, int val)
{
    vector.push_back(val);
    cur_ind = arr.size() - 1;
    while (cur_ind > 0)
    {
        // 父节点索引
    	int parent_index = (cur_ind + 1) / 2 - 1;
    	// 比较大小
    	if (arr[parent_index] < arr[cur_ind]) 
        {
            std::swap(arr[parent_index], arr[cur_ind]);
            cur_ind = parent_index;
        }
        else { break; }
    }
}
```

若只有堆顶元素不符合要求，其子树均为最大堆（最小堆），可将堆顶元素逐步下放

```C++
// 以最大堆为例子
void HeapShiftDown(vector<int>& arr)
{
    int cur = 0;
    while (cur < arr.size())
    {
		int max_ind = (arr[2 * cur] > arr[2 * cur + 1]) ? 2 * cur : 2 * cur + 1;
        if (arr[cur] < arr[max_ind])
        {
            std::swap(arr[cur], arr[max_ind]);
            cur = max_ind;
        }
    }
}
```

















