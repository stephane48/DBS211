#include <mysql.h>
#include <iostream>
#include<cctype>
#include<cstring>
#include <iomanip>

using namespace std;

int main(void) {

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res = nullptr;
	conn = mysql_init(0);
	int exequery;
	int exequery2;

	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_skamdem-kamguia", "Mm(9xC4ql]", "db_skamdem-kamguia", 3306, nullptr, 0);
		

	if (conn) {
		cout << "successful connection to database" << endl;

		string query = "select employees.employeeNumber, employees.firstName, employees.lastName, offices.phone, employees.extension from employees, offices where offices.officeCode = 1 and offices.officeCode = employees.officeCode"; //first select statement for Q1
		const char* q = query.c_str(); 
		exequery = mysql_query(conn, q);

		if (!exequery) {
			res = mysql_store_result(conn);
		}
		if (res == nullptr) {
			cout << "The query did not return a result." << endl;
		}
		else {
			cout << "The query successfully returned a result." << endl; 
		}
		cout << "*************** Employee Report ****************" << endl;
		cout << "Employee Report:" << endl;
		while (row = mysql_fetch_row(res)) {
			cout << " ID: " << row[0];
			cout << setw(10); 
			cout << " Name: " << row[1] << " " << row[2];
			cout << setw(26 - strlen(row[1]) - strlen(row[2]));;
			cout << " Phone: " << row[3];
			cout << setw(12);
			cout << " Extension: " << row[4];
			cout << endl;
		}
		string query2 = "SELECT e.employeeNumber, e.firstName, e.lastName, e.extension, o.phone FROM employees e JOIN offices o ON e.officeCode = o.officeCode WHERE e.employeeNumber IN(SELECT reportsTo FROM employees) ORDER BY employeeNumber";
		const char* q2 = query2.c_str();
		exequery2 = mysql_query(conn, q2);

		if (!exequery2) {
			res = mysql_store_result(conn);
		}
		if (res == nullptr) {
			cout << "The query did not return a result." << endl;
		}
		
		cout << "Manager Report:" << endl;
		while (row = mysql_fetch_row(res)) {
			cout << " ID: " << row[0];
			cout << setw(10);
			cout << " Name: " << row[1] << " " << row[2];
			cout << setw(26 - strlen(row[1]) - strlen(row[2]));;
			cout << " Phone: " << row[3];
			cout << setw(12);
			cout << " Extension: " << row[4];
			cout << endl;
		}
	}
		else {
			cout << "Connection Failed" << mysql_error(conn) << endl;
		}

	delete conn;
	return 0;
}
