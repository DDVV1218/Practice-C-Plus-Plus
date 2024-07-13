#include "worker.h"

Worker::Worker(int id, std::string name, int age) : m_id(id), m_name(name), m_age(age) {}
const std::string Worker::m_type = " ";

Employee::Employee(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Employee::ShowInfo()
{
	std::cout << "���: " << this->m_id << ". ����: " << this->m_name;
	std::cout << ". ����: " << this->m_age << ". ";
	std::cout << "��Ա���ͣ�ְ��" << std::endl;
}

std::string Employee::GetType()
{
	return this->m_type;
}

const std::string Employee::m_type = "ְ��";

Manager::Manager(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Manager::ShowInfo()
{
	std::cout << "���: " << this->m_id << ". ����: " << this->m_name;
	std::cout << ". ����: " << this->m_age << ". ";
	std::cout << "��Ա���ͣ�����" << std::endl;
}

std::string Manager::GetType()
{
	return this->m_type;
}

const std::string Manager::m_type = "����";

Boss::Boss(int id, std::string name, int age)
	: Worker(id, name, age) {}

void Boss::ShowInfo()
{
	std::cout << "���: " << this->m_id << ". ����: " << this->m_name;
	std::cout << ". ����: " << this->m_age << ". ";
	std::cout << "��Ա���ͣ��ϰ�" << std::endl;
}

std::string Boss::GetType()
{
	return this->m_type;
}

const std::string Boss::m_type = "�ϰ�";