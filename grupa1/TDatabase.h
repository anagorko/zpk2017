#ifndef TDATABASE_H
#define TDATABASE_H
#include <stdlib.h>
#include <iostream>

#include <vector>           # Possibility to use Vectors
#include <string>           # Possibility to use Strings

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

class TDatabase
{

    public:
        TDatabase(string login, string password, string tcp, string schema);
        vector <double> read_double(string statement);
        vector <string> read_string(string statement);
        void write(vector <string> dates, vector <string> values, string tablename);
    private:
    sql::Connection *con;
	sql::Driver    *driver;
	sql::Statement  *stmt;
	sql::ResultSet  *res;

};

#endif // TDATABASE_H
