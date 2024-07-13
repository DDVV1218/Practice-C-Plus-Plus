#include "worker.h"

Worker::Worker(int id, std::string name, int age) : m_id(id), m_name(name), m_age(age) {}
const std::string Worker::m_type = " ";

Employee::Employee(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Employee::ShowInfo()
{
	std::cout << "序号: " << this->m_id << ". 姓名: " << this->m_name;
	std::cout << ". 年龄: " << this->m_age << ". ";
	std::cout << "人员类型：职工" << std::endl;
}

std::string Employee::GetType()
{
	return this->m_type;
}

const std::string Employee::m_type = "职工";

Manager::Manager(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Manager::ShowInfo()
{
	std::cout << "序号: " << this->m_id << ". 姓名: " << this->m_name;
	std::cout << ". 年龄: " << this->m_age << ". ";
	std::cout << "人员类型：经理" << std::endl;
}

std::string Manager::GetType()
{
	return this->m_type;
}

const std::string Manager::m_type = "经理";

Boss::Boss(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Boss::ShowInfo()
{
	std::cout << "序号: " << this->m_id << ". 姓名: " << this->m_name;
	std::cout << ". 年龄: " << this->m_age << ". ";
	std::cout << "人员类型：老板" << std::endl;
}

std::string Boss::GetType()
{
	return this->m_type;
}

const std::string Boss::m_type = "老板";