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
		std::cout << "���������ѡ��: ";
		std::cin >> choice;

		switch (choice)
		{

		case 0: // �˳�ϵͳ
			wm.Exit();
			break;
		case 1: // ���ְ��
			wm.AddInfo();
			wm.OutputInfo();
			break;
		case 2: // ��ʾְ��
			wm.ShowInfo();
			break;
		case 3: // ɾ��ְ��
			wm.DeleteInfo();
			wm.OutputInfo();
			break;
		case 4: // �޸�ְ��
			wm.ModifyPerson();
			wm.OutputInfo();
			break;
		case 5: // ����ְ��
			wm.FindPerson();
			break;
		case 6: // ����ְ��
			wm.SortPerson();
			wm.OutputInfo();
			break;
		case 7: // ����ļ�
			wm.CleanInfo();
			wm.OutputInfo();
			break;
		}
		system("pause");
		system("cls");
	}

	system("pause");

}