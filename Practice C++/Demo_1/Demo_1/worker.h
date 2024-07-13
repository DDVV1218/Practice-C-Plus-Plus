#pragma once
#include<iostream>
#include<string>

class Worker
{

public:

	Worker(int id, std::string name, int age);

	virtual void ShowInfo() = 0;
	virtual std::string GetType() = 0;
	
	int m_id;
	std::string m_name;
	int m_age;
	static const std::string m_type;
	
};

class Employee : public Worker
{
public:

	Employee(int id, std::string name, int age);
	void ShowInfo();
	std::string GetType();

	static const std::string m_type;
};

class Manager : public Worker
{
public:

	Manager(int id, std::string name, int age);
	void ShowInfo();
	std::string GetType();

	static const std::string m_type;
};

class Boss : public Worker
{
public:

	Boss(int id, std::string name, int age);
	void ShowInfo();
	std::string GetType();

	static const std::string m_type;
};