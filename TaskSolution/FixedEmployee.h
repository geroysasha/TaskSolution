#pragma once

#include "Employee.h"

class FixedEmployee : public Employee
{
public:
	FixedEmployee(EmplFields &&emplFields) :
		Employee(move(emplFields)){}

	FixedEmployee &operator=(EmplFields &&emplFields)
	{
		Employee::operator=(move(emplFields));
		return *this;
	}
	virtual ~FixedEmployee();
	double average_monthly_wage();
};

