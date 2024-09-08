#ifndef CGPA_CALCULATOR_H
#define CGPA_CALCULATOR_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <string>
#include <vector>

class CGPACalculator{
    public:
        sql::Connection* con;
        CGPACalculator();
        ~CGPACalculator();

        void addStudent();
        void getStudentCGPA();
        void getAllStudentData();
    
    private:
        sql::Connection* setupDB();
        bool checkTableExists(std::string name, sql::Statement* stmt);
};

#endif