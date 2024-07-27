#include<iostream>
using namespace std;

class Student
{
public:
	Student()
	{
		cout << "构造函数" << endl;
	}

	Student(int age)
	{
		S_age = age;
	}

	Student(const Student& new_student)
	{
		cout << "拷贝构造函数" << endl;
		S_age = new_student.S_age;
	}

public:
	void print_age_address()
	{
		cout << (int)&S_age << endl;
	}

public:
	int S_age;
};

void Test()
{

	Student s_1 = Student(10);
	s_1.print_age_address();

	Student s_2 = Student(s_1);
	s_2.print_age_address();

}

int main()
{
	Test();
	system("pause");
}