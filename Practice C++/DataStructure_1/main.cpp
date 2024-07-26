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
	// �������������ֳ��������������������������ʣ�
	//	1. �������Ľڵ�ֵС�ڸ��ڵ�
	//  2. �������Ľڵ�ֵ���ڸ��ڵ�
	//  3. ������Ϊ����������
{

public:
	typedef BSNode<T> Node;

	BSTree() :root(nullptr) {};
	bool Insert(const T val)
		// ����Ԫ��
	{
		if (root == nullptr)
			// ����Ϊ�գ���ֱ��ָ�����ڵ�
		{
			root = new Node();
			root->val = val;
		}
		else
			// ������Ϊ�գ���������
		{
			Node* parent = nullptr;
			Node* cur = root;
			while (cur != nullptr)
				// ѭ��Ѱ�Ҳ���λ�ã���Ҫά��һ�����ڵ㣬��Ϊ��Ҫ����
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

			// ����ѭ���󣬵�ǰ��curΪnullptr�������Ԫ�صĸ��ڵ�Ӧ����parent
			Node* new_node = new Node(val);
			if (parent->val > val){ parent->left = new_node; }
			else { parent->right = new_node; }
		}
		
		return true;
	}

	void show()
		// ��ӡ������������ʹ��ǰ��������������������ڵ㡢�������ķ�ʽ�ݹ�
	{
		_show(root);
	}

	bool Delete(const T val)
		// ɾ�����е�Ԫ��
		// ���������
		//		1. ��ɾ��Ԫ��û�к��ӽڵ�
		//		2. ��ɾ��Ԫ��ֻ��һ�����ӽڵ�
		//		3. ��ɾ��Ԫ�����������ӽڵ�
	{
		// ����Ҫ�ҵ���ɾ����Ԫ��
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
		// ����ѭ��ʱ��ҪôcurΪnullptr��ҪôΪval�Ľ��
		if (cur == nullptr) { std::cout << "No Nodes Deleted" << std::endl; return false; }

		// ���һ��
		if (cur->right == nullptr && cur->left == nullptr)
		{
			if (cur == parent->left) { parent->left = nullptr; }
			else if (cur == parent->right){ parent->right = nullptr; }
			delete cur;
		}
		// ����������ڵ�ԭ��ָ���ӽڵ㣬����ָ���ӽڵ�Ľڵ�
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
		// ���������ɾ���ڵ��������ӽڵ㣬�����Ҫ�ҵ�һ�������ɾ���ڵ�ĸ��ڵ㣬���类ɾ���ڵ������������ֵ�����߱�ɾ���ڵ�����������Сֵ��
		else
		{
			// ��һ�����ҵ���ɾ���ڵ�����������Сֵ��������������˵�ֵ��
			Node* tmp_parent = cur;
			Node* new_cur = cur->right;
			while (new_cur->left != nullptr)
			{
				tmp_parent = new_cur;
				new_cur = new_cur->left;
			}
			// �˴��Ѿ��ҵ�������˵�ֵ��new_curָ��
			swap(cur->val, new_cur->val);
			// ����ֵ֮��ɾ��Ԫ��
			if (new_cur == tmp_parent->left){ tmp_parent->left = new_cur->right; }
				// ��һ����Ҫ��Ϊ�˷�ֹtmp_parentΪ���ڵ㣬��new_curΪ���ڵ���ҽڵ�
			else if (new_cur == tmp_parent->right){ tmp_parent->right = new_cur->right; }
			delete new_cur;
		}
		return true;
	}

	bool Delete_recursion(const T val)
		// �ݹ鷨����Ԫ��ɾ��
	{
		return _Delete_recursion(root, val);
	}
	bool Find(const T val) 
	// �����Ƿ���Ԫ�ش���
	{
		return _Find(root, val);
	}

	bool Insert_recursion(const T val)
		// ʹ�õݹ���뷨�����ʹ�����õ��ص㣬�����޸ı����������Ϣ
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
			// ��ǰroot����ĵ�ַ��Ӧ��Node��val��������Ҫɾ���ģ�����Ҫע����ǣ�����
			// �������Ǵ����ʱroot->left����root->right�����ã�������ʵ�޸ĵ���ǰһ���ڵ��left���Ի�right����
			// ��˿���ֱ�ӽ����޸ģ���ʵ�޸ĵľ��Ǹ��ڵ������

			if (root->left == nullptr) { root = root->right; }
			else if (root->right == nullptr) { root = root->left; }
			else
			{
				// Ѱ��������������ڵ��滻��root��ǰ��ŵ�����Ҫɾ���Ľڵ�ĵ�ַ�������������ã���Ҳ�����˸��ڵ������
				Node* min = root->right;
				while (min->left)
				{
					min = min->left;
				}
				swap(root->val, min->val);
				// ����������Ҫɾ������������˵�Ԫ�أ�������������������һ��BSTree�ˣ������Ҫֻ�����������еݹ飬������Ŀǰ��һ��BStree
				// ��Ϊ�������г��˱���Ҫɾ����val������Ԫ�ض�����val����˵ݹ�һ�����ҵ���Ԫ��
				return _Delete_recursion(root->right, val);
			}
			delete del;
			return true;
		}

	}

	bool _Insert_recursion(Node*& root, const T val)
	{
		// ����ֵ
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
		// ʹ�õݹ��˼�룬ǰ��ݹ飬���ж������Ƿ����
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