/*
	1. 添加联系人：向通讯录里添加新人，信息包括（姓名、性别、年龄、联系电话、家庭住址），最多记录100人
	2. 显示联系人：显示通讯录里所有联系人信息
	3. 删除联系人：按照姓名进行删除指定联系人
	4. 查找联系人：按照姓名查看指定联系人信息
	5. 修改联系人：按照姓名重新修改指定联系人
	6. 清空联系人：清空通讯录中所有信息
	7. 退出通讯录：退出当前使用的通讯录
*/

#include<iostream>
#include<string>
using namespace std;
#define MAX_NUM 1000

struct PersonInfo
{
	string name;
	int age;
	string sex;
	long long phone_number;
	string address;
};

struct Address
{
	struct PersonInfo InfoArrays[MAX_NUM];
	int a_size;
};

void showMenu();
void AddPerson(struct PersonInfo infoarray[], int* p_num);
void showAddress(struct Address* p_book);
void deletePerson(struct Address* p_book, string del_name);
void findPerson(Address* p_book, string find_name);
void changePerson(Address* p_book, string change_name);
void cleanAddress(Address* p_book);

int main_MS() {

	int select = 0;
	struct Address* addBook = new Address();
	addBook->a_size = 0;

	struct PersonInfo djh = { "董家豪", 23, "男", 13381896639, "上海市虹口区" };
	addBook->InfoArrays[0] = djh;
	addBook->a_size += 1;


	while (true)
	{
		showMenu();

		cout << "请输入选项：";
		cin >> select;
		switch (select)
		{
		case 1:
			// 添加联系人
			AddPerson(addBook->InfoArrays, &(addBook->a_size));
			break;
		case 2:
		{
			// 显示联系人
			if (addBook->a_size == 0)
			{
				cout << "通讯录为空！" << endl;
			}
			showAddress(addBook);
			break;
		}

		case 3:
		{			
			// 删除联系人
			string del_name;
			cout << "请输入需要删除的联系人姓名：";
			cin >> del_name;
			deletePerson(addBook, del_name);
			break;
		}

		case 4:
		{
			// 查找联系人
			string find_name;
			cout << "请输入需要查找的联系人姓名：";
			cin >> find_name;
			findPerson(addBook, find_name);
			break;
		}

		case 5:
			// 修改联系人
		{
			string change_name;
			cout << "请输入需要修改的联系人姓名：";
			cin >> change_name;
			changePerson(addBook, change_name);
			break;
		}
		case 6:
			// 清空联系人
			cleanAddress(addBook);
			break;
		case 0:
			// 退出通讯录
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
		default:
			cout << "你的输入有误，请重新输入：" << endl;
			break;
		}

		system("pause");
		system("cls");
	};

	system("pause");
	delete addBook;
	return 0;
}

void showMenu() {
	// 显示菜单

	cout << "*************************" << endl;
	cout << "***** 1、添加联系人 *****" << endl;
	cout << "***** 2、显示联系人 *****" << endl;
	cout << "***** 3、删除联系人 *****" << endl;
	cout << "***** 4、查找联系人 *****" << endl;
	cout << "***** 5、修改联系人 *****" << endl;
	cout << "***** 6、清空联系人 *****" << endl;
	cout << "***** 0、退出通讯录 *****" << endl;
	cout << "*************************" << endl;

}

void AddPerson(struct PersonInfo infoarray[], int* p_num)
{
	struct PersonInfo newInfo = PersonInfo();

	string name;
	string sex;
	int age;
	long long phonenumber;
	string address;

	cout << "请输入名称：";
	cin >> name;
	newInfo.name = name;

	cout << "请输入性别：";
	cin >> sex;
	newInfo.sex = sex;

	cout << "请输入年龄：";
	cin >> age;
	newInfo.age = age;

	cout << "请输入手机号码：";
	cin >> phonenumber;
	newInfo.phone_number = phonenumber;

	cout << "请输入住址：";
	cin >> address;
	newInfo.address = address;
	cout << endl;

	infoarray[*p_num] = newInfo;
	(*p_num)++;
	cout << "添加成功，当前通讯录容量为 " << *p_num << endl;
}

void showAddress(struct Address* p_book)
{
	for (int i = 0; i < p_book->a_size; i++)
	{
		cout << "姓名：" << p_book->InfoArrays[i].name << ". ";
		cout << "性别：" << p_book->InfoArrays[i].sex << ". ";
		cout << "年龄：" << p_book->InfoArrays[i].age << ". ";
		cout << "电话：" << p_book->InfoArrays[i].phone_number << ". ";
		cout << "住址：" << p_book->InfoArrays[i].address << ". ";
		cout << endl;
	};
	cout << endl;
}

void deletePerson(struct Address* p_book, string del_name)
{
	bool flag = false;
	int del_index;

	for (int i = 0; i < p_book->a_size; i++)
	{
		if (p_book->InfoArrays[i].name == del_name)
		{
			del_index = i;
			flag = true;
			break;
		};
	};

	if (!flag)
	{
		cout << "查无此人！" << endl << endl;
		return;
	};
	
	for (int j = del_index; j < p_book->a_size; j++)
	{
		p_book->InfoArrays[j] = p_book->InfoArrays[j + 1];
	};
	
	p_book->a_size -= 1;
	cout << "删除成功，当前通讯录容量为 " << p_book->a_size << "." << endl << endl;
}

void findPerson(Address* p_book, string find_name)
{
	bool flag = false;

	for (int i = 0; i < p_book->a_size; i++)
	{
		if (p_book->InfoArrays[i].name == find_name)
		{
			flag = true;
			cout << "姓名：" << p_book->InfoArrays[i].name << ". ";
			cout << "性别：" << p_book->InfoArrays[i].sex << ". ";
			cout << "年龄：" << p_book->InfoArrays[i].age << ". ";
			cout << "电话：" << p_book->InfoArrays[i].phone_number << ". ";
			cout << "住址：" << p_book->InfoArrays[i].address << ". ";
			cout << endl;
			cout << endl;
			break;
		};
	};

	if (!flag) cout << "查无此人！" << endl << endl;
}

void changePerson(Address* p_book, string change_name)
{
	bool flag = false;

	for (int i = 0; i < p_book->a_size; i++)
	{
		if (p_book->InfoArrays[i].name == change_name)
		{
			flag = true;
			string name;
			string sex;
			int age;
			long long phonenumber;
			string address;

			cout << "请输入名称：";
			cin >> name;
			p_book->InfoArrays[i].name = name;

			cout << "请输入性别：";
			cin >> sex;
			p_book->InfoArrays[i].sex = sex;

			cout << "请输入年龄：";
			cin >> age;
			p_book->InfoArrays[i].age = age;

			cout << "请输入手机号码：";
			cin >> phonenumber;
			p_book->InfoArrays[i].phone_number = phonenumber;

			cout << "请输入住址：";
			cin >> address;
			p_book->InfoArrays[i].address = address;
			cout << endl;
			break;
		};
	};

	if (!flag) cout << "查无此人！" << endl << endl;
}

void cleanAddress(Address* p_book)
{
	p_book->a_size = 0;
	cout << "通讯录已清空" << endl << endl;
}