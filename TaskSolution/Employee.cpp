#include "stdafx.h"
#include "Employee.h"


Employee::~Employee()
{

}


int Employee::get_id()
{
	return emplFields.empl_id;
}


string Employee::get_inf(bool for_file)
{
	return (for_file) ? 
		to_string(emplFields.empl_id) + "\t" + emplFields.name + "\t" + to_string(emplFields.wage) + "\t" + emplFields.empl_type 
		:
		to_string(emplFields.empl_id) + "\t" + emplFields.name + "\t" + to_string(this->average_monthly_wage());
}


string Employee::get_name()
{
	return emplFields.name;
}
