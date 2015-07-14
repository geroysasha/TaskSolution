#pragma once

#include "Employee.h"

class HourlyEmployee : public Employee
{
public:
	HourlyEmployee() :
		Employee(){}

	HourlyEmployee(HourlyEmployee &&obj) :
		Employee(move(obj)){}

	HourlyEmployee &operator=(EmplFields &&emplFields)
	{
		Employee::operator=(move(emplFields));
		return *this;
	}

	virtual ~HourlyEmployee();
	double average_monthly_wage();
};

