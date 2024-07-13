#pragma once			// 防止头文件重复包含
#include<iostream>
#include "worker.h"

class WorkerManager
{
public:

	// 构造函数
	WorkerManager();

	// 展示菜单
	void Show_Menu();

	// Output员工信息至txt文件
	void OutputInfo();

	// Input员工信息至txt文件
	void InputInfo();

	// 添加员工信息
	void AddInfo();

	// 添加单个员工信息
	void AddPerson(Worker* wptr);

	// 显示员工信息
	void ShowInfo();

	// 退出系统
	void Exit();

	// 析构函数
	~WorkerManager();

public:

	Worker** workers;	// 二级指针，数组中储存的是员工实例的指针
	int worker_num;		// 公司员工数量

};