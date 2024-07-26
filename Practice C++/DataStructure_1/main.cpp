#include<iostream>

template <typename T>
struct BSNode
{
	BSNode* left;
	BSNode* right;
	T val;

	BSNode() :left(nullptr), right(nullptr), val(T()) {};
	BSNode(T val) : left(nullptr), right(nullptr), val(val) {};
};

void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;

}

template <typename T>
class BSTree	
	// 二叉搜索树：又称作排序搜索树，具有以下性质：
	//	1. 左子树的节点值小于根节点
	//  2. 右子树的节点值大于根节点
	//  3. 子树都为二叉搜索树
{

public:
	typedef BSNode<T> Node;

	BSTree() :root(nullptr) {};
	bool Insert(const T val)
		// 插入元素
	{
		if (root == nullptr)
			// 若树为空，则直接指定根节点
		{
			root = new Node();
			root->val = val;
		}
		else
			// 若树不为空，插入数据
		{
			Node* parent = nullptr;
			Node* cur = root;
			while (cur != nullptr)
				// 循环寻找插入位置，需要维护一个父节点，因为需要链接
			{
				if (cur->val > val)
				{
					parent = cur;
					cur = cur->left;
				}
				else if (cur->val < val)
				{
					parent = cur;
					cur = cur->right;
				}
				else { std::cout << "Repeated Number " << val << std::endl; return false; }
			}

			// 跳出循环后，当前的cur为nullptr，插入的元素的父节点应该是parent
			Node* new_node = new Node(val);
			if (parent->val > val){ parent->left = new_node; }
			else { parent->right = new_node; }
		}
		
		return true;
	}

	void show()
		// 打印二叉搜索树，使用前序遍历，即左子树、根节点、右子树的方式递归
	{
		_show(root);
	}

	bool Delete(const T val)
		// 删除树中的元素
		// 四种情况：
		//		1. 被删除元素没有孩子节点
		//		2. 被删除元素只有一个孩子节点
		//		3. 被删除元素有两个孩子节点
	{
		// 首先要找到被删除的元素
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr)
		{
			if (cur->val < val)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->val > val)
			{
				parent = cur;
				cur = cur->left;
			}
			else { break; }
		}
		// 跳出循环时，要么cur为nullptr，要么为val的结点
		if (cur == nullptr) { std::cout << "No Nodes Deleted" << std::endl; return false; }

		// 情况一：
		if (cur->right == nullptr && cur->left == nullptr)
		{
			if (cur == parent->left) { parent->left = nullptr; }
			else if (cur == parent->right){ parent->right = nullptr; }
			delete cur;
		}
		// 情况二：父节点原本指向孩子节点，现在指向孩子节点的节点
		else if (cur->right == nullptr || cur->left == nullptr)
		{
			if (cur == parent->left)
			{
				if (cur->left == nullptr) { parent->left = cur->right; }
				else if (cur->right == nullptr) { parent->left = cur->left; }
			}
			else if (cur == parent->right)
			{
				if (cur->left == nullptr) { parent->right = cur->right; }
				else if (cur->right == nullptr) { parent->right = cur->left; }
			}
		}
		// 情况三：被删除节点有左右子节点，因此需要找到一个替代被删除节点的根节点，例如被删除节点左子树的最大值（或者被删除节点右子树的最小值）
		else
		{
			// 第一步，找到被删除节点右子树的最小值（右子树的最左端的值）
			Node* tmp_parent = cur;
			Node* new_cur = cur->right;
			while (new_cur->left != nullptr)
			{
				tmp_parent = new_cur;
				new_cur = new_cur->left;
			}
			// 此处已经找到了最左端的值，new_cur指向
			swap(cur->val, new_cur->val);
			// 交换值之后删除元素
			if (new_cur == tmp_parent->left){ tmp_parent->left = new_cur->right; }
				// 这一步主要是为了防止tmp_parent为根节点，则new_cur为根节点的右节点
			else if (new_cur == tmp_parent->right){ tmp_parent->right = new_cur->right; }
			delete new_cur;
		}
		return true;
	}

	bool Delete_recursion(const T val)
		// 递归法进行元素删除
	{
		return _Delete_recursion(root, val);
	}
	bool Find(const T val) 
	// 查找是否有元素存在
	{
		return _Find(root, val);
	}

	bool Insert_recursion(const T val)
		// 使用递归的想法，灵活使用引用的特点，可以修改本身变量的信息
	{
		return _Insert_recursion(root, val);
	}
private:

	bool _Delete_recursion(Node*& root, const T val)
	{
		Node* del = root;
		if (root == nullptr) { return false; }
		else if (root->val > val) { return _Delete_recursion(root->left, val); }
		else if (root->val < val) { return _Delete_recursion(root->right, val); }
		else
		{
			// 当前root储存的地址对应的Node的val是我们需要删除的，但需要注意的是！！！
			// 由于我们传入的时root->left或者root->right的引用，我们其实修改的是前一个节点的left属性或right属性
			// 因此可以直接进行修改，其实修改的就是父节点的属性

			if (root->left == nullptr) { root = root->right; }
			else if (root->right == nullptr) { root = root->left; }
			else
			{
				// 寻找右子树的最左节点替换，root当前存放的是需要删除的节点的地址，但是由于引用，它也代表了父节点的属性
				Node* min = root->right;
				while (min->left)
				{
					min = min->left;
				}
				swap(root->val, min->val);
				// 交换后，仍需要删除右子树最左端的元素，但是由于整个树不是一个BSTree了，因此需要只对右子树进行递归，右子树目前是一个BStree
				// 因为右子树中除了本身要删除的val，其他元素都大于val，因此递归一定会找到此元素
				return _Delete_recursion(root->right, val);
			}
			delete del;
			return true;
		}

	}

	bool _Insert_recursion(Node*& root, const T val)
	{
		// 返回值
		if (root == nullptr)
		{
			root = new Node(val);
			return true;
		}

		if (root->val > val) { return _Insert_recursion(root->left, val); }
		else if (root->val < val) { return _Insert_recursion(root->right, val); }

		return false;
	}

	void _show(Node*& root)
	{
		if (root == nullptr)
		{
			return;
		}

		_show(root->left);
		std::cout << root->val << " " << std::endl;
		_show(root->right);
	}
	
	bool _Find(Node*& root, const T val)
	{
		// 使用递归的思想，前序递归，先判断自身是否符合
		if (root == nullptr) { return false; }

		if (root->val == val) { return true; }
		else if (root->val > val) { return _Find(root->left, val); }
		else if (root->val < val) { return _Find(root->right, val); }
	}

	Node* root;
};


int main()
{
	BSTree<int> mytree;
	mytree.Insert_recursion(1);
	mytree.Insert_recursion(9);
	mytree.Insert_recursion(5);
	mytree.Insert_recursion(6);
	mytree.Insert_recursion(2);
	mytree.Insert_recursion(8);
	mytree.Insert_recursion(7);
	mytree.show();

	mytree.Delete_recursion(5);
	mytree.show();

	if (mytree.Find(9)) {

		std::cout << "true" << std::endl;
	}
}