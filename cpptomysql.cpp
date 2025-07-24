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
		// Driver connection to MySql route, user, password.
		con = driver->connect("tcp://localhost:3306", "root", "Administrator1");
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



/*
#include<iostream>
#include<stdlib.h>
#include<mysql_connection.h>
#include<mysql_driver.h>
#include<mysql_error.h>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/prepared_statement.h>

using namespace std;

// For demostraion only. Never save your password in the code.
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "Administrator1";

int main()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch(sql::SQLException e)
	{
		cout << " Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	// Create database if do not exist.
	con->setSchema("quickstartdb");

	// Database named inventory.
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS inventory");
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
	cout << "Finished creating table" << endl;
	delete stmt;

	// Insert data in the rows.
	pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
	pstmt->setString(1, "banana");
	pstmt->setInt(2, 150);
	pstmt->execute();
	cout << "One row inserted" << endl;

	pstmt->setString(1, "orange");
	pstmt->setInt(2, 154);
	pstmt->execute();
	cout << "One row inserted" << endl;

	pstmt->setString(1, "apple");
	pstmt->setInt(2, 100);
	pstmt->execute();
	cout << "One row inserted" << endl;

	delete pstmt;
	delete con;
	system("pause");

	return 0;
}
*/