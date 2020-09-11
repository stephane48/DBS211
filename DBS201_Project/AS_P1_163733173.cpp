#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <iostream>
#include <string>
using namespace std;

struct Employee {
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
};

int menu() {
	int option;
	bool valid = false;
	cout << "*********************HR Menu*********************" << endl;
	cout << "1) Find Employee\n2) Employees Reprot\n3) Add Employee\n4) Update Employee\n5) Remove Emplouee\n0) Exit" << endl;
	do {
		cout << "< ";
		cin >> option;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid input, enter 0 - 5: ";
		}
		else if (option < 0 || option > 5) {
			cout << "Invalid input, enter 0 - 5: ";
		}
		else {
			valid = true;
		}
	} while (!valid);
	return option;
}

int findEmployee(MYSQL* conn, int employeeNumber, struct Employee* emp) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int exequery;
	int result = 0;
	string query = "select distinct e1.employeeNumber, e1.lastName, "\
		"e1.firstName, e1.email, phone, e1.extension, "\
		"coalesce(concat(e2.firstName, ' ', e2.lastname), ' ') as reportsTo, "\
		"e1.jobTitle, city from employees as e1 join offices as o on e1.officeCode = o.officeCode "\
		"left join employees as e2 on e1.reportsTo = e2.employeeNumber "\
		"where e1.employeeNumber = ";
	query.append(to_string(employeeNumber));
	query.append(";");
	const char* q = query.c_str();
	exequery = mysql_query(conn, q);
	if (!exequery) {
		res = mysql_store_result(conn);
		if (res == nullptr) {
			result = 0;
		}
		while (row = mysql_fetch_row(res)) {
			emp->employeeNumber = stoi(row[0]);
			strncpy(emp->lastName, row[1], 50);
			strncpy(emp->firstName, row[2], 50);
			strncpy(emp->email, row[3], 100);
			strncpy(emp->phone, row[4], 50);
			strncpy(emp->extension, row[5], 10);
			strncpy(emp->reportsTo, row[6], 50);
			strncpy(emp->jobTitle, row[7], 50);
			strncpy(emp->city, row[8], 50);
			result = 1;
		}
	}
	else {
		cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
	}

	return result;
}

void displayEmployee(MYSQL* conn, struct Employee emp) {
	int valid = false;
	int employNumber;
	cout << "Enter EmployNumber: ";
	do {
		cin >> employNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid input, enter EmployeeNumber: ";
		}
		else {
			valid = true;
		}
	} while (!valid);
	if (findEmployee(conn, employNumber, &emp)) {
		cout << "employeeNumber=" << emp.employeeNumber << "\n";
		cout << "lastName=" << emp.lastName << "\n";
		cout << "firstName=" << emp.firstName << "\n";
		cout << "email=" << emp.email << "\n";
		cout << "phone=" << emp.phone << "\n";
		cout << "extension=" << emp.extension << "\n";
		cout << "reportsTo=" << emp.reportsTo << "\n";
		cout << "jobTitile=" << emp.jobTitle << "\n";
		cout << "city=" << emp.city << endl;
	}
	else {
		cout << "Employee " << employNumber << " dose not exit.\n";
	}

}

void displayAllEmployees(MYSQL* conn) {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int exequery;
	string query = "select distinct e1.employeeNumber, concat(e1.firstName, ' ', e1.lastName), "\
		"e1.email, phone, e1.extension, coalesce(concat(e2.firstName, ' ', e2.lastname), ' ') as reportsTo "\
		"from employees as e1 join offices as o on e1.officeCode = o.officeCode "\
		"left join employees as e2 on e1.reportsTo = e2.employeeNumber;";
	const char* q = query.c_str();
	exequery = mysql_query(conn, q);
	if (!exequery) {
		res = mysql_store_result(conn);
		if (res == nullptr) {
			cout << "There is no employees' information to be displayed." << endl;
		}
		else {
			cout << "E      EmployeeName         Email                                    Phone                Ext       Manager" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
		}
		while (row = mysql_fetch_row(res)) {
			printf("%-6s %-20s %-40s %-20s %-10s %-20s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
		}
	}
	else {
		cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
	}

}


int main(void) {
	Employee emp = {};
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_squ7", "C)5shAw4k[", "db_squ7", 3306, nullptr, 0);
	if (conn) {
		int option;
		do {
			option = menu();
			switch (option) {
			case 1:
				displayEmployee(conn, emp);
				break;
			case 2:
				displayAllEmployees(conn);
				break;
			case 0:
				cout << "Bye!" << endl;
				break;
			default:
				cout << "Invalit Input" << endl;
			}
		} while (option != 0);
	}
	else {
		cout << "Connection Failed" << mysql_error(conn) << endl;
	}
	mysql_close(conn);
	return 0;
}