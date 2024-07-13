// 管理类负责的内容如下：
// 1. 与用户的沟通菜单界面
// 2. 对职工增删改查的操作
// 3. 与文件的读写交互

#include<fstream>
#include<sstream>
#include "workerManager.h"
#include "worker.h"

// 字符串处理，去除字符两端的空格
std::string& trim(std::string& s);

WorkerManager::WorkerManager(): worker_num(0), workers(NULL){}

WorkerManager::~WorkerManager(){}

void WorkerManager::Show_Menu()
{
	std::cout << "******************************" << std::endl;
	std::cout << "*****欢迎使用职工管理系统******" << std::endl;
	std::cout << "*******0. 退出管理程序********" << std::endl;
	std::cout << "*******1. 增加职工信息********" << std::endl;
	std::cout << "*******2. 显示职工信息********" << std::endl;
	std::cout << "*******3. 删除离职员工********" << std::endl;
	std::cout << "*******4. 修改职工信息********" << std::endl;
	std::cout << "*******5. 查找职工信息********" << std::endl;
	std::cout << "*******6. 按照编号排序********" << std::endl;
	std::cout << "*******7. 清空所有文档********" << std::endl;
	std::cout << "******************************" << std::endl;
}

void WorkerManager::Exit()
{
	std::cout << "欢迎下次使用！" << std::endl;
	system("pause");
	exit(0);			// 无论如何直接退出程序
}

void WorkerManager::OutputInfo()
{
	std::ofstream ofs;
	ofs.open("EmployeesInfo.txt", std::ios::out);

	for (int i = 0; i < worker_num; i++)
	{
		ofs << "序号: " << workers[i]->m_id << ". 姓名: " << workers[i]->m_name;
		ofs << ". 年龄: " << workers[i]->m_age << ". ";
		ofs << "人员类型: " << workers[i]->GetType() << "." << std::endl;
	}

	ofs.close();
}

void WorkerManager::InputInfo()
{
	if (this->workers != NULL)
	{
		std::cout << "公司已录入职工信息，无法重新读入！" << std::endl;
		return;
	}

	std::ifstream ifs;
	ifs.open("EmployeesInfo.txt", std::ios::in);

	if (!ifs.is_open())
	{
		std::cout << "文件无法打开！" << std::endl;
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

		// string 转为 int
		std::istringstream tmp_id(id_str);
		int id;
		tmp_id >> id;

		std::istringstream tmp_age(age_str);
		int age;
		tmp_age >> age;

		Worker* worker = NULL;

		if (type == "职工")
		{
			worker = new Employee(id, name, age);
		}
		else if (type == "经理")
		{
			worker = new Manager(id, name, age);
		}
		else if(type == "老板")
		{
			worker = new Boss(id, name, age);
		}

		if (worker == NULL)
		{
			std::cout << "读取数据时无法判断职工类型！" << std::endl;
			return;
		}

		this->AddPerson(worker);
	}

	ifs.close();
}

void WorkerManager::AddPerson(Worker* wptr)
{

	int size = this->worker_num + 1;
	// 重新构造新的数组，长度为原先的长度 + 1
	Worker** new_workers = new Worker* [size];

	if ((this->worker_num > 0) && (this->workers != NULL))
	{ 
		// 复制原有信息
		for (int i = 0; i < this->worker_num; i++)
		{
			new_workers[i] = this->workers[i];
		}
	}
	
	new_workers[size - 1] = wptr;
	// 数量加一
	this->worker_num += 1;
	this->workers = new_workers;
}

void WorkerManager::ShowInfo()
{
	// 顺序显示所有信息
	for (int i = 0; i < this->worker_num; i++)
	{
		this->workers[i]->ShowInfo();
	}
}

void WorkerManager::AddInfo()
{
	int id;
	std::cout << "请输入他(她)的序号：";
	std::cin >> id;
	std::string name;
	std::cout << "请输入他(她)的名字：";
	std::cin >> name;
	int age;
	std::cout << "请输入他(她)的年龄：";
	std::cin >> age;
	std::string type;
	std::cout << "请输入他(她)的职级：";
	std::cin >> type;

	Worker* worker = NULL;

	if (type == "职工")
	{
		worker = new Employee(id, name, age);
	}
	else if (type == "经理")
	{
		worker = new Manager(id, name, age);
	}
	else if (type == "老板")
	{
		worker = new Boss(id, name, age);
	}

	if (worker == NULL)
	{
		std::cout << "读取数据时无法判断职工类型！" << std::endl;
		return;
	}

	this->AddPerson(worker);
	std::cout << "添加成功！";
	std::cout << "当前公司员工数量为：" << this->worker_num << std::endl;
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

