#include<iostream>
#include "workerManager.h"
#include "worker.h"

int main()
{

	WorkerManager wm;
	int choice = 0;

	wm.InputInfo();

	// Worker* dd = new Boss(1, "DD", 22);
	// wm.AddPerson(dd);
	// wm.OutputInfo();
	// delete dd;
	// exit(1);


	while (true)
	{
		wm.Show_Menu();
		std::cout << "请输入你的选择: ";
		std::cin >> choice;

		switch (choice)
		{

		case 0: // 退出系统
			wm.Exit();
			break;
		case 1: // 添加职工
			wm.AddInfo();
			wm.OutputInfo();
			break;
		case 2: // 显示职工
			wm.ShowInfo();
			break;
		case 3: // 删除职工
			break;
		case 4: // 修改职工
			break;
		case 5: // 查找职工
			break;
		case 6: // 排序职工
			break;
		case 7: // 清空文件
			break;
		}
		system("pause");
		system("cls");
	}

	system("pause");

}