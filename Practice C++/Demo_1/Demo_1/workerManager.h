#pragma once			// ��ֹͷ�ļ��ظ�����
#include<iostream>
#include "worker.h"

class WorkerManager
{
public:

	// ���캯��
	WorkerManager();

	// չʾ�˵�
	void Show_Menu();

	// OutputԱ����Ϣ��txt�ļ�
	void OutputInfo();

	// InputԱ����Ϣ��txt�ļ�
	void InputInfo();

	// ���Ա����Ϣ
	void AddInfo();

	// ��ӵ���Ա����Ϣ
	void AddPerson(Worker* wptr);

	// ��ʾԱ����Ϣ
	void ShowInfo();

	// �˳�ϵͳ
	void Exit();

	// ��������
	~WorkerManager();

public:

	Worker** workers;	// ����ָ�룬�����д������Ա��ʵ����ָ��
	int worker_num;		// ��˾Ա������

};