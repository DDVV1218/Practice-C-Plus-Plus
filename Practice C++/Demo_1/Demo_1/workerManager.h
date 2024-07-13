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

	// �ж���ӵ�Ա��������Ƿ����ظ�
	bool IsRepeated(const int& id);

	// ��ӵ���Ա����Ϣ
	void AddPerson(Worker* wptr);

	// ɾ��Ա������Ϣ
	void DeleteInfo();

	// ��ʾԱ����Ϣ
	void ShowInfo();

	// �޸�ְ����Ϣ
	void ModifyPerson();

	// ����ְ����Ϣ
	void FindPerson();

	// ����ְ����Ϣ
	void SortPerson();

	// ��������ĵ�
	void CleanInfo();

	// �˳�ϵͳ
	void Exit();

	// ��������
	~WorkerManager();

public:

	Worker** workers;	// ����ָ�룬�����д������Ա��ʵ����ָ��
	int worker_num;		// ��˾Ա������

};