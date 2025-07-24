/*
	Project:	cpptomysql.
	File:		cpptomysql.cpp
	Date:		December 23th, 2024.
	Author:		(C) Software Engineer. Howard Fernando Del Angel Leija.
	Contact:	ferdelangel92@gmail.com
	Version:	1.0
*/

// Directory.
#include<iostream>
#include<stdlib.h>
#include<mysql_connection.h>
#include<mysql_driver.h>
#include<mysql_error.h>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/prepared_statement.h>

using namespace std;

int main()
{
	try {
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;

		driver = sql::mysql::get_mysql_driver_instance();
		// Driver connection to MySql root, username, password.
		con = driver->connect("root", "username", "password");
		// Database name.
		con->setSchema("test");

		sql::Statement* stmt;
		stmt = con->createStatement();

		// Create table in SQL.
		string createTableSQL
			= "CREATE TABLE IF NOT EXISTS Course (""id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,""COURSES VARCHAR(255) NOT NULL"")";

		stmt->execute(createTableSQL);

		string insertDataSQL
			= "INSERT INTO Course (courses) VALUES " "('MySQL'), ('HTML'), ('AWS'), ('Cisco')";

		stmt->execute(insertDataSQL);

		// SQL query to retrieve data from the table.
		string selectDataSQL = "SELECT * FROM courses";

		sql::ResultSet* res
			= stmt->executeQuery(selectDataSQL);

		// Loop through the result set and display data.
		int count = 0;
		while (res->next()) {
			cout << " Course " << ++count << ": "
				<< res->getString("courses") << endl;
		}

		delete res;
		delete stmt;
		delete con;

	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}

	return 0;
}