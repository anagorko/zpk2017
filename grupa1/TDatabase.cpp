#include "TDatabase.h"
#include <stdlib.h>
#include <iostream>
#include <vector>           # Possibility to use Vectors
#include <string>           # Possibility to use Strings
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

TDatabase::TDatabase(string login, string password, string tcp, string schema) {
		driver = get_driver_instance();
		con = driver->connect(tcp, login, password);
		con->setSchema(schema);
		stmt = con->createStatement();

	}

vector<double> TDatabase::read_double(string statement){
		vector<double> tab;
		res = stmt->executeQuery(statement);
		while (res->next()) {
			tab.push_back(res->getDouble(1));
		}
		return tab;
	}

vector<string> TDatabase::read_string(string statement){
		vector<string> tab;
		res = stmt->executeQuery(statement);
		while (res->next()) {
			tab.push_back(res->getString(1));
		}
		return tab;
}

void TDatabase::write(vector <string> dates, vector <string> values, string tablename) {
		string val;
		string date;
		string statement;

		statement = "drop table if exists temp_table";
		stmt->execute(statement);
		statement = "Create table mysql.temp_table as Select * from mysql." + tablename + " LIMIT 0";
		stmt->execute(statement);

		for (int i = 0; i < values.size(); i++) {
			statement = "INSERT INTO mysql.temp_table VALUES (";
			val = values[i];
			date = dates[i];
			statement = statement + "'" + date + "'" + "," + val + ",current_date,datediff('" + date + "','1993-05-20'))";
			stmt->execute(statement);
		}

		statement = "delete from mysql." + tablename + " where booking_date = current_date";
		stmt->execute(statement);
		statement = "Insert into mysql." + tablename + " Select * from mysql.temp_table";
		stmt->execute(statement);

	}
