// �����ฺ����������£�
// 1. ���û��Ĺ�ͨ�˵�����
// 2. ��ְ����ɾ�Ĳ�Ĳ���
// 3. ���ļ��Ķ�д����

#include<fstream>
#include<sstream>
#include "workerManager.h"
#include "worker.h"

// �ַ�������ȥ���ַ����˵Ŀո�
std::string& trim(std::string& s);

WorkerManager::WorkerManager(): worker_num(0), workers(NULL){}

WorkerManager::~WorkerManager(){}

void WorkerManager::Show_Menu()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*****��ӭʹ��ְ������ϵͳ******" << std::endl;
	std::cout << "*******0. �˳��������********" << std::endl;
	std::cout << "*******1. ����ְ����Ϣ********" << std::endl;
	std::cout << "*******2. ��ʾְ����Ϣ********" << std::endl;
	std::cout << "*******3. ɾ����ְԱ��********" << std::endl;
	std::cout << "*******4. �޸�ְ����Ϣ********" << std::endl;
	std::cout << "*******5. ����ְ����Ϣ********" << std::endl;
	std::cout << "*******6. ���ձ������********" << std::endl;
	std::cout << "*******7. ��������ĵ�********" << std::endl;
	std::cout << "******************************" << std::endl;
}

void WorkerManager::Exit()
{
	std::cout << "��ӭ�´�ʹ�ã�" << std::endl;
	system("pause");
	exit(0);			// �������ֱ���˳�����
}

void WorkerManager::OutputInfo()
{
	std::ofstream ofs;
	ofs.open("EmployeesInfo.txt", std::ios::out);

	for (int i = 0; i < worker_num; i++)
	{
		ofs << "���: " << workers[i]->m_id << ". ����: " << workers[i]->m_name;
		ofs << ". ����: " << workers[i]->m_age << ". ";
		ofs << "��Ա����: " << workers[i]->GetType() << "." << std::endl;
	}

	ofs.close();
}

void WorkerManager::InputInfo()
{
	if (this->workers != NULL)
	{
		std::cout << "��˾��¼��ְ����Ϣ���޷����¶��룡" << std::endl;
		return;
	}

	std::ifstream ifs;
	ifs.open("EmployeesInfo.txt", std::ios::in);

	if (!ifs.is_open())
	{
		std::cout << "�ļ��޷��򿪣�" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(ifs, line))
	{
		
		std::istringstream iss(line);
		std::string name;
		std::string age_str;
		std::string id_str;
		std::string type;

		iss.ignore(100, ':');
		std::getline(iss, id_str, '.');
		id_str = trim(id_str);


		iss.ignore(100, ':');
		std::getline(iss, name, '.');
		name = trim(name);
		

		iss.ignore(100, ':');
		std::getline(iss, age_str, '.');
		age_str = trim(age_str);

		iss.ignore(100, ':');
		std::getline(iss, type, '.');
		type = trim(type);

		// string תΪ int
		std::istringstream tmp_id(id_str);
		int id;
		tmp_id >> id;

		std::istringstream tmp_age(age_str);
		int age;
		tmp_age >> age;

		Worker* worker = NULL;

		if (type == "ְ��")
		{
			worker = new Employee(id, name, age);
		}
		else if (type == "����")
		{
			worker = new Manager(id, name, age);
		}
		else if(type == "�ϰ�")
		{
			worker = new Boss(id, name, age);
		}

		if (worker == NULL)
		{
			std::cout << "��ȡ����ʱ�޷��ж�ְ�����ͣ�" << std::endl;
			return;
		}

		this->AddPerson(worker);
	}

	ifs.close();
}

void WorkerManager::AddPerson(Worker* wptr)
{

	int size = this->worker_num + 1;
	// ���¹����µ����飬����Ϊԭ�ȵĳ��� + 1
	Worker** new_workers = new Worker* [size];

	if ((this->worker_num > 0) && (this->workers != NULL))
	{ 
		// ����ԭ����Ϣ
		for (int i = 0; i < this->worker_num; i++)
		{
			new_workers[i] = this->workers[i];
		}
	}
	
	new_workers[size - 1] = wptr;
	// ������һ
	this->worker_num += 1;
	// ɾ��ԭ���������ٵ�Ա������
	delete[] this->workers;
	this->workers = new_workers;
}

void WorkerManager::ShowInfo()
{
	// ˳����ʾ������Ϣ
	for (int i = 0; i < this->worker_num; i++)
	{
		this->workers[i]->ShowInfo();
	}
}

bool WorkerManager::IsRepeated(const int& id)
{
	// �ж��Ƿ�����ظ�
	for (int i = 0; i < this->worker_num; i++)
	{
		if (this->workers[i]->m_id == id)
		{
			return true;
		}
	}

	return false;
}

void WorkerManager::AddInfo()
{
	int id;
	
	while (true)
	{
		std::cout << "��������(��)����ţ�";
		std::cin >> id;

		if (this->IsRepeated(id))
		{
			std::cout << "����빫˾����Ա���ظ���������ѡ������!" << std::endl;
		}
		else { break; }
	}

	std::string name;
	std::cout << "��������(��)�����֣�";
	std::cin >> name;
	int age;
	std::cout << "��������(��)�����䣺";
	std::cin >> age;
	std::string type;
	std::cout << "��������(��)��ְ����";
	std::cin >> type;

	Worker* worker = NULL;

	if (type == "ְ��")
	{
		worker = new Employee(id, name, age);
	}
	else if (type == "����")
	{
		worker = new Manager(id, name, age);
	}
	else if (type == "�ϰ�")
	{
		worker = new Boss(id, name, age);
	}

	if (worker == NULL)
	{
		std::cout << "��ȡ����ʱ�޷��ж�ְ�����ͣ�" << std::endl;
		return;
	}

	this->AddPerson(worker);
	std::cout << "��ӳɹ���";
	std::cout << "��ǰ��˾Ա������Ϊ��" << this->worker_num << std::endl;
}

void WorkerManager::DeleteInfo()
{
	std::cout << "��������Ҫɾ������ְԱ���ı��: ";
	int id;
	std::cin >> id;

	if (! this->IsRepeated(id))
	{
		std::cout << "δ�ҵ������Ϣ!" << std::endl;
		return;
	}

	int size = this->worker_num - 1;
	if (size == 0)
	{ 
		delete[] this->workers;
		this->worker_num = size;
		this->workers = NULL;
	}
	else
	{
		// ���¹���һ������
		Worker** new_workers = new Worker * [size];
		int i = 0, j = 0;
		while (i < size + 1)
		{
			if (this->workers[i]->m_id != id)
			{
				new_workers[j] = this->workers[i];
				j++;
			}
			i++;
		}

		this->worker_num = size;
		delete[] this->workers;
		this->workers = new_workers;
	}

	std::cout << "ɾ��Ա����Ϣ�ɹ�����ǰԱ������Ϊ��" << this->worker_num << std::endl;
}

void WorkerManager::ModifyPerson()
{
	std::cout << "��������Ҫ�޸ĵ�Ա���ı��: ";
	int id;
	std::cin >> id;

	if (!this->IsRepeated(id))
	{
		std::cout << "δ�ҵ������Ϣ!" << std::endl;
		return;
	}

	std::string name;
	std::cout << "��������(��)�����֣�";
	std::cin >> name;
	int age;
	std::cout << "��������(��)�����䣺";
	std::cin >> age;
	std::string type;
	std::cout << "��������(��)��ְ����";
	std::cin >> type;

	for (int i = 0; i < this->worker_num; i++)
	{
		if (this->workers[i]->m_id == id)
		{ 
			Worker* & aimed_worker = this->workers[i]; 
			if (type != aimed_worker->m_type)
			{
				Worker* new_worker = NULL;
				if (type == "ְ��")
				{
					new_worker = new Employee(id, name, age);
				}
				else if (type == "����")
				{
					new_worker = new Manager(id, name, age);
				}
				else if (type == "�ϰ�")
				{
					new_worker = new Boss(id, name, age);
				}

				if (new_worker == NULL)
				{
					std::cout << "��ȡ����ʱ�޷��ж�ְ�����ͣ�" << std::endl;
					return;
				}

				delete aimed_worker;
				aimed_worker = new_worker;

			}
			else
			{
				aimed_worker->m_name = name;
				aimed_worker->m_age = age;
			}
		}
	}

	std::cout << "Ա����Ϣ�޸ĳɹ�! " << std::endl;
	
}

void WorkerManager::FindPerson()
{
	std::cout << "��������Ҫ���ҵ�Ա���ı��: ";
	int id;
	std::cin >> id;

	if (!this->IsRepeated(id))
	{
		std::cout << "δ�ҵ������Ϣ!" << std::endl;
		return;
	}

	for (int i = 0; i < this->worker_num; i++)
	{
		if (this->workers[i]->m_id == id) { this->workers[i]->ShowInfo(); break; }
	}
}

void WorkerManager::CleanInfo()
{
	std::cout << "�Ƿ�ȷ��ɾ��ȫ�����ݣ�ɾ�����޷���ԭ! (y/n)           ";
	char ans;
	std::cin >> ans;

	if (ans == 'y')
	{
		delete[] this->workers;
		this->workers = NULL;
		this->worker_num = 0;
		std::cout << "��ȫ��ɾ��! " << std::endl;
	}
	else if (ans == 'n') { return; }
	else { return; }

}

void WorkerManager::SortPerson()
{
	std::cout << "˳��or���� (�������): ";
	std::string ans;
	std::cin >> ans;
	if (ans == "˳��") 
	{
		for (int i = 0; i < this->worker_num; i++)
		{
			for (int j = 0; j < this->worker_num - i - 1; j++)
			{
				if (this->workers[j]->m_id > this->workers[j + 1]->m_id)
				{
					Worker* tmp_ptr = this->workers[j];
					this->workers[j] = this->workers[j + 1];
					this->workers[j + 1] = tmp_ptr;
				}
			}
		}
	}
	else if (ans == "����")
	{
		for (int i = 0; i < this->worker_num; i++)
		{
			for (int j = 0; j < this->worker_num - i - 1; j++)
			{
				if (this->workers[j]->m_id < this->workers[j + 1]->m_id)
				{
					Worker* tmp_ptr = this->workers[j];
					this->workers[j] = this->workers[j + 1];
					this->workers[j + 1] = tmp_ptr;
				}
			}
		}
	}

	std::cout << "����ɹ�! " << std::endl;
}

std::string& trim(std::string& s)
{
	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}

	return s;
}

