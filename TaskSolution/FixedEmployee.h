#pragma once

#include "Employee.h"

class FixedEmployee : public Employee
{
public:
	FixedEmployee() :
		Employee(){}

	FixedEmployee(FixedEmployee &&obj) :
		Employee(move(obj)){}

	FixedEmployee &operator=(EmplFields &&emplFields)
	{
		cout << "USE move assigmant fixed" << endl;
		Employee::operator=(move(emplFields));
		return *this;
	}
	virtual ~FixedEmployee();
	double average_monthly_wage();
};

