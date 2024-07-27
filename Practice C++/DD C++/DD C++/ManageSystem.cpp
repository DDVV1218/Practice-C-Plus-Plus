/*
	1. �����ϵ�ˣ���ͨѶ¼��������ˣ���Ϣ�������������Ա����䡢��ϵ�绰����ͥסַ��������¼100��
	2. ��ʾ��ϵ�ˣ���ʾͨѶ¼��������ϵ����Ϣ
	3. ɾ����ϵ�ˣ�������������ɾ��ָ����ϵ��
	4. ������ϵ�ˣ����������鿴ָ����ϵ����Ϣ
	5. �޸���ϵ�ˣ��������������޸�ָ����ϵ��
	6. �����ϵ�ˣ����ͨѶ¼��������Ϣ
	7. �˳�ͨѶ¼���˳���ǰʹ�õ�ͨѶ¼
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

	struct PersonInfo djh = { "���Һ�", 23, "��", 13381896639, "�Ϻ��к����" };
	addBook->InfoArrays[0] = djh;
	addBook->a_size += 1;


	while (true)
	{
		showMenu();

		cout << "������ѡ�";
		cin >> select;
		switch (select)
		{
		case 1:
			// �����ϵ��
			AddPerson(addBook->InfoArrays, &(addBook->a_size));
			break;
		case 2:
		{
			// ��ʾ��ϵ��
			if (addBook->a_size == 0)
			{
				cout << "ͨѶ¼Ϊ�գ�" << endl;
			}
			showAddress(addBook);
			break;
		}

		case 3:
		{			
			// ɾ����ϵ��
			string del_name;
			cout << "��������Ҫɾ������ϵ��������";
			cin >> del_name;
			deletePerson(addBook, del_name);
			break;
		}

		case 4:
		{
			// ������ϵ��
			string find_name;
			cout << "��������Ҫ���ҵ���ϵ��������";
			cin >> find_name;
			findPerson(addBook, find_name);
			break;
		}

		case 5:
			// �޸���ϵ��
		{
			string change_name;
			cout << "��������Ҫ�޸ĵ���ϵ��������";
			cin >> change_name;
			changePerson(addBook, change_name);
			break;
		}
		case 6:
			// �����ϵ��
			cleanAddress(addBook);
			break;
		case 0:
			// �˳�ͨѶ¼
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
		default:
			cout << "��������������������룺" << endl;
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
	// ��ʾ�˵�

	cout << "*************************" << endl;
	cout << "***** 1�������ϵ�� *****" << endl;
	cout << "***** 2����ʾ��ϵ�� *****" << endl;
	cout << "***** 3��ɾ����ϵ�� *****" << endl;
	cout << "***** 4��������ϵ�� *****" << endl;
	cout << "***** 5���޸���ϵ�� *****" << endl;
	cout << "***** 6�������ϵ�� *****" << endl;
	cout << "***** 0���˳�ͨѶ¼ *****" << endl;
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

	cout << "���������ƣ�";
	cin >> name;
	newInfo.name = name;

	cout << "�������Ա�";
	cin >> sex;
	newInfo.sex = sex;

	cout << "���������䣺";
	cin >> age;
	newInfo.age = age;

	cout << "�������ֻ����룺";
	cin >> phonenumber;
	newInfo.phone_number = phonenumber;

	cout << "������סַ��";
	cin >> address;
	newInfo.address = address;
	cout << endl;

	infoarray[*p_num] = newInfo;
	(*p_num)++;
	cout << "��ӳɹ�����ǰͨѶ¼����Ϊ " << *p_num << endl;
}

void showAddress(struct Address* p_book)
{
	for (int i = 0; i < p_book->a_size; i++)
	{
		cout << "������" << p_book->InfoArrays[i].name << ". ";
		cout << "�Ա�" << p_book->InfoArrays[i].sex << ". ";
		cout << "���䣺" << p_book->InfoArrays[i].age << ". ";
		cout << "�绰��" << p_book->InfoArrays[i].phone_number << ". ";
		cout << "סַ��" << p_book->InfoArrays[i].address << ". ";
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
		cout << "���޴��ˣ�" << endl << endl;
		return;
	};
	
	for (int j = del_index; j < p_book->a_size; j++)
	{
		p_book->InfoArrays[j] = p_book->InfoArrays[j + 1];
	};
	
	p_book->a_size -= 1;
	cout << "ɾ���ɹ�����ǰͨѶ¼����Ϊ " << p_book->a_size << "." << endl << endl;
}

void findPerson(Address* p_book, string find_name)
{
	bool flag = false;

	for (int i = 0; i < p_book->a_size; i++)
	{
		if (p_book->InfoArrays[i].name == find_name)
		{
			flag = true;
			cout << "������" << p_book->InfoArrays[i].name << ". ";
			cout << "�Ա�" << p_book->InfoArrays[i].sex << ". ";
			cout << "���䣺" << p_book->InfoArrays[i].age << ". ";
			cout << "�绰��" << p_book->InfoArrays[i].phone_number << ". ";
			cout << "סַ��" << p_book->InfoArrays[i].address << ". ";
			cout << endl;
			cout << endl;
			break;
		};
	};

	if (!flag) cout << "���޴��ˣ�" << endl << endl;
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

			cout << "���������ƣ�";
			cin >> name;
			p_book->InfoArrays[i].name = name;

			cout << "�������Ա�";
			cin >> sex;
			p_book->InfoArrays[i].sex = sex;

			cout << "���������䣺";
			cin >> age;
			p_book->InfoArrays[i].age = age;

			cout << "�������ֻ����룺";
			cin >> phonenumber;
			p_book->InfoArrays[i].phone_number = phonenumber;

			cout << "������סַ��";
			cin >> address;
			p_book->InfoArrays[i].address = address;
			cout << endl;
			break;
		};
	};

	if (!flag) cout << "���޴��ˣ�" << endl << endl;
}

void cleanAddress(Address* p_book)
{
	p_book->a_size = 0;
	cout << "ͨѶ¼�����" << endl << endl;
}