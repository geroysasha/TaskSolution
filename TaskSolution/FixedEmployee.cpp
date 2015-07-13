#include "stdafx.h"
#include "FixedEmployee.h"


FixedEmployee::~FixedEmployee()
{
}

double FixedEmployee::average_monthly_wage()
{
	return this->emplFields.wage;
}