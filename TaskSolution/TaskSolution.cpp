// TaskSolution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FixedEmployee.h"
#include "HourlyEmployee.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>


void addEmployee(shared_ptr<vector<shared_ptr<Employee>>> empl, shared_ptr<vector<string>> vec);
void show_Employee(shared_ptr<vector<shared_ptr<Employee>>> empl);
void read_file(shared_ptr<vector<shared_ptr<Employee>>> empl);
void save_file(shared_ptr<vector<shared_ptr<Employee>>> empl);
void console_input(string &buff);
void line_parsing(string line, shared_ptr<vector<string>> data);
bool check_input_hourly_rate(string &input);
bool isNumber(string str);
bool search_id_duplicate(vector<int> &vec_id, int id);
int id_Employee(shared_ptr<vector<shared_ptr<Employee>>> empl);

//правило сортровки по имени и среднемесячной заработоной плате
struct
{
	inline bool operator()(shared_ptr<Employee> lhs, shared_ptr<Employee> rhs)
	{
		if (lhs->average_monthly_wage() > rhs->average_monthly_wage())
		{
			return true;
		}
		else if (lhs->average_monthly_wage() == rhs->average_monthly_wage())
		{
			if (strcmp(lhs->get_name().c_str(), rhs->get_name().c_str()) < 0)
			{
				return true;
			}
		}
		return false;
	}
} compare_wage_and_name;

//правило сортировки по возрастанию идентификаторов сотрудников
struct
{
	inline bool operator()(shared_ptr<Employee> lhs, shared_ptr<Employee> rhs)
	{
		return (lhs->get_id() < rhs->get_id());
	}
} compare_desc;


int _tmain(int argc, _TCHAR* argv[])
{
	auto key = ' ';
	auto bMenu = true;
	auto empl = make_shared<vector<shared_ptr<Employee>>>();
	
	while (bMenu)
	{

		cout << "[s] - show Employee;\t[a] - add Employee;\t[r] - read file;\n" <<
			"[w] - write file;\t[c] - clear console;\t[q] - quit;\n>>";

		cin >> key;

		switch (key)
		{
		case 's':
			show_Employee(empl);
			break;
		case 'a':
			addEmployee(empl, NULL);
			break;
		case 'r':
			read_file(empl);
			break;
		case 'w':
			save_file(empl);
			break;
		case 'c':
			system("cls");
			break;
		case 'q':
			bMenu = false;
			break;
		default:
			break;
		}

		cin.clear();
		cin.sync();

	}

	return 0;
}


void addEmployee(shared_ptr<vector<shared_ptr<Employee>>> empl, shared_ptr<vector<string>> vec)
{
	EmplFields emplFields;

	if (vec == NULL)
	{
		auto buff = to_string(0);

		emplFields.empl_id = id_Employee(empl);

		cout << "Enter name Employee: ";

		console_input(emplFields.name);

		while (true)
		{

			cout << "Enter Employee type ([h] - hourly, [f] - fixed): ";

			console_input(buff);

			if (buff.find("h") == string::npos && buff.find("f") == string::npos)
			{
				cout << "-->ALERT!!! Incorrect Employee type." << endl;
			}
			else
			{
				switch (*buff.c_str())
				{
				case 'h':
					emplFields.empl_type = "Hourly";
					break;
				case 'f':
					emplFields.empl_type = "Fixed";
					break;
				default:
					break;
				}
				break;
			}
		}

		while (true)
		{

			cout << ((emplFields.empl_type.find("Hourly") != string::npos) ? "Enter hourly rate: " : "Enter salary: ");

			console_input(buff);

			if (!check_input_hourly_rate(buff))
			{
				cout << "-->ALERT!!! Incorrect hourly rate." << endl;
			}
			else
			{
				emplFields.wage = atof(buff.c_str());
				break;
			}
		}
	}
	else
	{
		emplFields.empl_id = atoi(vec->at(0).c_str());
		emplFields.name = vec->at(1);
		emplFields.wage = atof(vec->at(2).c_str());
		emplFields.empl_type = vec->at(3);
	}

	//добывляем сторудника в коллекцию
	if (emplFields.empl_type.find("Hourly") != string::npos)
	{
		empl->push_back(make_shared<HourlyEmployee>(move(emplFields)));
	}
	else
	{
		empl->push_back(make_shared<FixedEmployee>(move(emplFields)));
	}		 


}


void show_Employee(shared_ptr<vector<shared_ptr<Employee>>> empl)
{
	//сортируем коллекцию
	sort(empl->begin(), empl->end(), compare_wage_and_name);

	auto i = 0;
	auto it = empl->begin();
	auto empl_size = empl->size();

	cout << "======================All emploees======================" << endl;
	for (auto &inf : *empl)
	{
		cout << inf->get_inf(false) << endl;
	}

	cout << "========================================================" << endl;
	cout << "======================First five names==================" << endl;

	while (i < 5 && empl->size() != 0) 
	{
		cout << (*it)->get_name() << endl;
		*it++;
		i++;
	}

	cout << "========================================================" << endl;
	cout << "======================Last three id=====================" << endl;

	i = 0;
	it = empl->begin();
	while (it < empl->end())
	{
		if ((i > empl_size - 4) || (empl_size - 4) < 0)
		{
			cout << (*it)->get_id() << endl;
		}
		*it++;
		i++;
	}
	cout << "========================================================" << endl;
}


int id_Employee(shared_ptr<vector<shared_ptr<Employee>>> empl)
{
	auto i = 0;

	sort(empl->begin(), empl->end(), compare_desc);

	for (auto &id : *empl)
	{
		if (id->get_id() != i)
			return i;
		i++;

	}
	return empl->size();
}


void console_input(string &buff)
{
	cin.clear();
	cin.sync();
	getline(cin, buff);
}


bool check_input_hourly_rate(string &input)
{
	auto found = input.find_first_not_of("01234567890.");

	return found != string::npos ? false : true;
}


void read_file(shared_ptr<vector<shared_ptr<Employee>>> empl)
{
	
	auto line = to_string(0);
	auto data = make_shared<vector<string>>();
	auto error_read_file = false;
	ifstream file("TaskSolution.txt");
	vector<int> temp_id;

	empl->clear();

	if (file.is_open())
	{
		while (getline(file, line))
		{
			//парсинг прочитанной строки для получения информации
			//и на предмет нарушенной структуры файла
			line_parsing(line, data);

			if (data->size() == EmplFields::size()  && !search_id_duplicate(temp_id, atoi(data->at(0).c_str())))
			{
				addEmployee(empl, data);
				temp_id.push_back(atoi(data->at(0).c_str()));
			}
			else
			{
				error_read_file = true;
			}
			data->clear();
			line.clear();
		}
		file.close();
		cout << (error_read_file ? "-->Alert!!! File contains errors" : "-->File successfully opened") << endl;
	}
	else
	{
		cout << "-->Alert!!! Error file open" << endl;
	}
}


void save_file(shared_ptr<vector<shared_ptr<Employee>>> empl)
{
	ofstream file("TaskSolution.txt");
	if (file.is_open())
	{
		for (auto &inf : *empl)
		{
			file << inf->get_inf(true) << endl;
		}
		file.close();
	}
	else
	{
		cout << "-->ALERT!!! Error file open." << endl;
	}
	cout << "-->Saved to file" << endl;
}


void line_parsing(string line, shared_ptr<vector<string>> data)
{
	if (line.find("\t") != string::npos)
	{
		switch (data->size())
		{
		case 0:
			//проверка является ли поле id числом
			if (isNumber(line.substr(0, line.find("\t"))))
			{
				data->push_back(line.substr(0, line.find("\t")));
			}
			break;
		case 1:
			//проверка является ли поле name строкой
			if (!isNumber(line.substr(0, line.find("\t"))))
			{
				data->push_back(line.substr(0, line.find("\t")));
			}
			break;
		case 2:
			//проверка является ли поле wage числом
			if (isNumber(line.substr(0, line.find("\t"))))
			{
				data->push_back(line.substr(0, line.find("\t")));
			}
			break;
		default:
			return;
			break;
		}

		line_parsing(line.substr(line.find("\t") + 1, line.length()), data);

	}
	else
	{
		//проверка является ли поле type строкой
		if (!isNumber(line.c_str()) && line.length() != 0)
		{
			if (line.find("Hourly") != string::npos || line.find("Fixed") != string::npos)
			{
				data->push_back(line.c_str());
			}
		}
		return;
	}
}


bool isNumber(string str)
{
	return (str[0] >= '0' && str[0] <= '9') ? true : false;
}


bool search_id_duplicate(vector<int> &vec_id, int id)
{
	for (auto &i:vec_id)
	{
		if (i == id)
		{
			return true;
		}
	}
	return false;
}


