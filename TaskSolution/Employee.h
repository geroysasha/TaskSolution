#pragma once

#include <iostream>
#include <string>

using namespace std;

struct EmplFields
{
	int empl_id = -1;
	double wage = -1.0;
	string name = " ";
	string empl_type = " ";
	static int size(){ return 4; };
};

class Employee
{
public:
	
	Employee(EmplFields &&emplFields)
	{
		this->emplFields = move(emplFields);
	}

	Employee &operator=(EmplFields &&emplFields)
	{
		this->emplFields = move(emplFields);
		return *this;
	}
	virtual ~Employee();
	virtual double average_monthly_wage() = 0;
	int get_id();
	string get_inf(bool for_file);
	string get_name();

protected:

	EmplFields emplFields;
};

