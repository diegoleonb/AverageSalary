#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Model/Employee.cpp"
#include "json.hpp"
#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

using json = nlohmann::json;

double averageSalary(const std::vector<Employee>& employees)
{
	try
	{
		if (employees.size() == 0)
		{
			return 0;
		}
		else 
		{
			double sum = 0;
			for (const auto& employee : employees)
			{
				sum += employee.salary;
			}
			return sum / employees.size();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in averageSalary: " << ex.what() << std::endl;
		return 0;
	}
}

Employee getEmployeeWithHighestSalary(const std::vector<Employee>& employees)
{
	try
	{
		if (employees.size() == 0)
		{
			return Employee();
		}
		else
		{
			return *std::max_element(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {return a.salary < b.salary; });
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in getEmployeeWithHighestSalary: " << ex.what() << std::endl;
		return Employee();
	}
}

void sortEmployees(std::vector<Employee>& employees)
{
	try
	{
		std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {return a.id < b.id; });
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in sortEmployees: " << ex.what() << std::endl;
	}
}

std::string getFileExtension(const std::string& filename)
{
	try
	{
		std::size_t i = filename.rfind('.', filename.length());
		if (i != std::string::npos) {
			return(filename.substr(i + 1, filename.length() - i));
		}
		return("");
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in getFileExtension: " << ex.what() << std::endl;
		return ("");
	}
}

std::vector<Employee> readEmployeesFromJSON(const std::string& filename)
{
	try
	{
		std::ifstream file(filename);
		json data;
		file >> data;

		if (!file) 
		{
			std::cerr << "Error in readEmployeesFromJSON: " << std::endl;
			return std::vector<Employee>();
		}
		else
		{
			std::vector<Employee> employees;
			for (const auto& employee : data["employees"])
			{
				employees.push_back(Employee{ 
					employee["name"], 
					employee["id"], 
					employee["department"], 
					employee["salary"] 
				});
			}
			return employees;
		}
		
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in readEmployeesFromJSON: " << ex.what() << std::endl;
		return std::vector<Employee>();
	}
}

std::vector<Employee> readEmployeesFromXML(const std::string& filename)
{
	try
	{
		pugi::xml_document document;
		pugi::xml_parse_result result = document.load_file(filename.c_str());
		if (!result)
		{
			std::cerr << "Error in readEmployeesFromXML: " << std::endl;
			return std::vector<Employee>();
		}
		else
		{
			std::vector<Employee> employees;
			for (pugi::xml_node employee = document.child("employees").child("employee"); employee; employee = employee.next_sibling("employee"))
			{
				employees.push_back(Employee{ 
					employee.child_value("name"), 
					std::stoi(employee.child_value("id")), 
					employee.child_value("department"), 
					std::stod(employee.child_value("salary")) 
				});
			}
			return employees;
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error in readEmployeesFromXML: " << ex.what() << std::endl;
		return std::vector<Employee>();
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}
	std::string filename = argv[1];
	std::string extension = getFileExtension(filename);
	std::vector<Employee> employees;
	if (extension == "json")
	{
		employees = readEmployeesFromJSON(filename);
	}
	else if (extension == "xml")
	{
		employees = readEmployeesFromXML(filename);
	}
	else
	{
		std::cerr << "Error: Invalid file extension. Only JSON or XML is accepted." << std::endl;
		return 1;
	}
	if (employees.empty())
	{
		std::cerr << "Error: No employees found." << std::endl;
		return 1;
	}
	std::cout << "Average salary: " << averageSalary(employees) << std::endl;
	Employee highestSalaryEmployee = getEmployeeWithHighestSalary(employees);
	std::cout << "Employee with highest salary: " << highestSalaryEmployee.id << " | " << highestSalaryEmployee.name << " | " << highestSalaryEmployee.department << " with " << highestSalaryEmployee.salary << std::endl;
	sortEmployees(employees);
	for (const auto& employee : employees)
	{
		std::cout << employee.id << " | " << employee.name << " | " << employee.department << " | " << employee.salary << std::endl;
	}
	return 0;
    
}
