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

快速排序算法的时间复杂度为 <font color='PaleGreen'>$O(nlogn)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(nlogn)$</font> 

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
        // 这两行的等于号非常重要，如果不加等于号，碰到重复的数字，容易无法走出循环
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[low], arr[i]);		// 切记不要忘记交换最初的target，因为target没有移动
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

## 七、堆排序

堆（Heap）时一类特殊的数据结构，可以被看作是一颗完全二叉树的数组对象

堆的性质有以下两点：

1. 堆中某个节点的值总是不大于或不小于其父节点的值
2. 堆总是一颗完全二叉树

**<u>*若索引从1开始标注*</u>**，由上至下从左至右标注符合堆特性的完全二叉树，设树的深度为 $k$，且 $k$ 层所有的结点都连续集中在最左侧，可以得到如下规律：

1. `parent(i) = i / 2`
2. `left child(i) = 2 * i`
3. `right child(i) = 2 * i  + 1`

**<u>*若索引从0开始标注*</u>**，由上至下从左至右标注符合堆特性的完全二叉树，设树的深度为 $k$，且 $k$ 层所有的结点都连续集中在最左侧，可以得到如下规律：

1. `parent(i) = (i + 1) / 2 - 1 = i / 2`
2. `left child(i) = 2 * i + 1`
3. `right child(i) = 2 * i + 2`

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
        int max_ind;
        if (2 * cur + 2 >= arr.size()) { max_ind = 2 * cur + 1; }
        else if (2 * cur + 1 >= arr.size()) { continue; }
        else
        {
        	max_ind = (arr[2 * cur + 1] > arr[2 * cur + 2]) ? 2 * cur + 1 : 2 * cur + 2;
            if (arr[cur] < arr[max_ind])
            {
                std::swap(arr[cur], arr[max_ind]);
                cur = max_ind;
            }
        }
    }
}
```

给定一个无序的数组，可以使用`Heapify`让其堆化，从而成为最大堆（最小堆）。`Heapify`算法的主要思想为：从最后一个叶子节点开始，倒着对每个叶子节点做`ShiftDown`操作，这个算法的时间复杂度为 <font color='PaleGreen'>$O(n)$</font>

```C++
void ShiftDown(int* arr, int start, int end)
    // 从start位置开始到end位置的树进行shiftdown
{
    int size = end - start + 1;
    int cur = start;
    while (cur * 2 + 1 > end)	// 直到没有叶子节点
    {
        int max_ind;
        if (cur * 2 + 2 <= end)
        {
            // 当左右子节点都存在
            max_ind = (arr[2 * cur + 1] > arr[2 * cur + 2]) ? 2 * cur + 1 : 2 * cur + 2;
        }
        else
        {
            max_ind = 2 * cur + 1;
        }
        
        if (arr[max_ind] > arr[cur]) 
        {
            std::swap(arr[max_ind], arr[cur]);
            cur = max_ind;
        }
        else { break; }
    }
}

void Heapify(int* arr, int size)
{
    // 找到最后一个叶子节点
    int last_leaf_index = size / 2 - 1;
    // 倒着对每个叶子节点做shiftdown
    for (int i = last_leaf_index; i >= 0; i--)
    {
        ShiftDown(arr, i, size - 1);
    }
}
```

这个算法之所以时间复杂度是O(N)，是因为每次的`ShiftDown`都需要交换元素，考虑每层元素可能被交换的最多次数，第 $j$ 层（从第1层开始，一共$K$层）被交换的最多次数为 $K-j$ 次，而第$j$层的元素数目最多为$2^{j-1}$个，因此可以通过求和的方式，如下所示：
$$
S(k)=2^0(k-1)+2^1(k-2)+...+2^{k-1}(0)
$$
利用错位相减法求和，最终得到：
$$
S(k)=2^k-k-1
$$
根据元素总数和层数的关系：
$$
N = 2^k - 1
$$
因此可以得到时间复杂度的计算：
$$
S(N)=N-\log_2{(N+1)}=O(N)
$$

- 下面回到正题：堆排序

我们知道，大根堆的根节点为最大值，小根堆的根节点为最小值，因此我们可以通过将无序数组`Heapify`后，将根节点与最后的叶节点交换位置，从而将最大值放置在数组最后。紧接着在剩下的数组中重复此过程（所做的也就是将队首的元素`ShiftDown`即可）

堆排序算法的时间复杂度为 <font color='PaleGreen'>$O(nlogn)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(1)$</font> 

```C++
void HeapSort(int* arr, int size)
{
    // 首先对数组进行堆化
    Heapify(arr, size);
    for (int i = 0; i < size - 1; i++)
        // 其次交换最大元素与最后元素
    {
        std::swap(arr[0], arr[size - i - 1]);
        // 除去最后i+1个元素后ShiftDown
        ShiftDown(arr, 0, size - i - 2);
    }
    
}
```

## 八、归并排序

归并排序是建立再归并操作上的一种有效的排序算法，该算法采用分治法。主要思想为：将原序列分解成多个子序列，使得子序列有序，再合并有序的子序列使之成为更长的有序子序列。

归并排序算法的时间复杂度为 <font color='PaleGreen'>$O(nlogn)$</font> ，空间复杂度为 <font color='PaleGreen'>$O(n)$</font> 

```C++
void Merge(int* arr, int* result, int start, int mid, int end)
    // 合并两个有序数组
{
    int i = start, j = mid + 1, k = start;
    while (i != mid + 1 && j != end + 1)
    {
        if (arr[i] > arr[j])
        {
            result[k++] = arr[j++];
        }
        else if (arr[i] < arr[j])
        {
            result[k++] = arr[i++];
        }
    }
    while (i != mid + 1){ result[k++] = arr[i++]; }
    while (j != end + 1){ result[k++] = arr[j++]; }
    for (int z = start; z <= end; z++) { arr[z] = result[z]; }
}

void MergeSort(int* arr, int* result, int start, int end)
{
    int mid_idx;
    if (start < end)
    {
        mid_idx = start + (start - end) / 2;		// 防止内存溢出
        MergeSort(arr, result, start, mid_idx);
        MergeSort(arr, result, mid_idx + 1, end);
        Merge(arr, result, start, mid_idx, end);
    }
}
```

## 其他问题

> STL里sort算法用的是什么排序算法？

并非所有STL容器都需要用到`sort`算法。首先，关系型容器拥有自动排序功能，因为底层采用RB-Tree；其次，序列式容器中的`stack`、`queue`和`priority-queue`都有特定的出入口，不允许用户对元素排序；剩下的`vector`、`deque`都适用`sort`算法。

实现逻辑：STL的sort算法，在数据量大时采用`QuickSort`快速排序法，分段归并排序。一旦分段后的数据量小于某个门槛，为避免快速排序法的递归调用带来过大的额外负荷，就改用`Insertion Sort`插入排序。如果递归层次过深，还会改用`Heap Sort`堆排序。

> 为什么快速排序比堆排序性能好？

第一、堆排序访问数据的方式没有快速排序好

对于快速排序来说，数据是**<u>顺序访问</u>**的。而对于堆排序来说，数据是跳着访问的，这样对CPU缓存是不友好的。

第二、对于同样的数据，排序过程中，堆排序的数据交换次数要多于快速排序

**排序过程是由两个基本的操作组成的——<u>比较和交换</u>**。快速排序交换的次数不会比逆序度多。但是堆排序的第一步就是建堆，这个过程会打乱数据原有的相对选择顺序，导致数据有序度降低。



## LeetCode

> LeetCode 215 & LCR 076 ：数组中的第K个最大元素
>
> 给定整数数组 `nums` 和整数 `k`，请返回数组中第 `k` 个最大的元素。
>
> 请注意，你需要找的是数组排序后的第 `k` 个最大的元素，而不是第 `k` 个不同的元素。

- 第一种解法是使用暴力排序，使用选择排序每次将最大的元素放置在起始的位置，此方法时间复杂度较高
- 第二种解法是巧妙运用快速排序，由于每次快速排序都会将数组分成两部分，且双指针重合的索引的值固定下来，因此可以通过判断此索引是否符合结果要求，根据大小关系选择其中一部分进行递归寻找
- 第三种解法是使用堆排序，构建最大堆，根据要求弹出前K-1个最大值，然后返回堆首的元素

```C++
// The Second Solution: Quick Sort
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return SearchForKth(nums, 0, nums.size() - 1, nums.size() + 1 - k);
    }

    int QuickSort_S(vector<int>&arr, int start, int end)
    // 快速排序法
    {
        int i = start, j = end;
        int target = arr[start];
        while (i < j)
        {
            while (i < j && arr[j] >= target) { j--; } 
            while (i < j && arr[i] <= target) { i++; }
            if (i < j)
            {
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i], arr[start]);
        
        return i;
    }

    int SearchForKth(vector<int>&arr, int start, int end, int key)
    // 寻找数组中第K大的数，使用快速排序法，时间复杂度为O(n)
    {
        int result = QuickSort_S(arr, start, end);
        if (result == key - 1) { return arr[result]; }
        else
        {
            if (result < key - 1) { return SearchForKth(arr, result + 1, end, key); }
            else { return SearchForKth(arr, start, result - 1, key); }
        }
    }
};

// The Third Solution: Heap Sort
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        heapify(nums, 0, nums.size() - 1);
        while (k-- > 1)
        {
            pop_head(nums);
            shiftdown(nums, 0, nums.size() - 1);
        }
        return nums[0];
    }

    void pop_head(vector<int>& nums)
    {
        swap(nums[0], nums[nums.size() - 1]);
        nums.pop_back();
    }

    void heapify(vector<int>& nums, int start, int end)
    {
        int last_leaf_idx = end / 2;
        for (int i = last_leaf_idx; i >= 0; i--)
        {
            shiftdown(nums, i, end);
        }
    }

    void shiftdown(vector<int>& nums, int start, int end)
    {
        int cur = start;
        int max_idx;
        while (2 * cur + 1 <= end)
        {
            int left = 2 * cur + 1;
            int right = 2 * cur + 2;
            if (right <= end)
            {
                max_idx = (nums[left] > nums[right]) ? left : right;
            }
            else { max_idx = left; }

            if (nums[cur] < nums[max_idx]) { swap(nums[cur], nums[max_idx]); }
            
            cur = max_idx;
        }
    }
};
```









