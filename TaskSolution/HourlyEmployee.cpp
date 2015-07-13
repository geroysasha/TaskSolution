#include "stdafx.h"
#include "HourlyEmployee.h"


HourlyEmployee::~HourlyEmployee()
{
}


double HourlyEmployee::average_monthly_wage()
{
	return (20.8 * (double)8 * this->emplFields.wage);
}