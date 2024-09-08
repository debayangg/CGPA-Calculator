#include "CGPACalculator.h"
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "creds.h"
#include <map>

using namespace std;

CGPACalculator::CGPACalculator() {
    con = setupDB();
}

CGPACalculator::~CGPACalculator() {
    delete con;
}

bool CGPACalculator::checkTableExists(string name, sql::Statement* stmt) {
    try {
        string query = "SHOW TABLES LIKE '" + name + "'";
        sql::ResultSet* res = stmt->executeQuery(query);
        
        bool exists = res->next();
        delete res;
        return exists;
    } catch (sql::SQLException &e) {
        cout << "SQL Error: " << e.what() << endl;
        return false;
    }
}

sql::Connection* CGPACalculator::setupDB() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", creds::username, creds::password);
        sql::Statement* stmt = con->createStatement();

        string dbName = "CGPACalculator";
        string query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '" + dbName + "';";
        sql::ResultSet* res = stmt->executeQuery(query);

        if (res->next()) {
            con->setSchema(dbName);
        } else {
            stmt->execute("CREATE DATABASE " + dbName);
            con->setSchema(dbName);
        }

        if (!checkTableExists("STUDENTS", stmt)) {
            query = "CREATE TABLE STUDENTS ( "
                    "STUDENT_ID INT PRIMARY KEY, "
                    "FIRST_NAME VARCHAR(50), "
                    "LAST_NAME VARCHAR(50) "
                    ");";
            stmt->executeUpdate(query);
        }

        if (!checkTableExists("GRADES", stmt)) {
            query = "CREATE TABLE GRADES ("
                    "GRADE_ID INT, "
                    "STUDENT_ID INT, "
                    "GRADE INT, "
                    "FOREIGN KEY (STUDENT_ID) REFERENCES STUDENTS(STUDENT_ID) "
                    ");";
            stmt->executeUpdate(query);
        }

        delete res;
        delete stmt;
        return con;
    } catch (sql::SQLException &e) {
        cout << "SQL Error: " << e.what() << " " << e.getErrorCode() << " " << e.getSQLState() << endl;
        return NULL;
    }
}

void CGPACalculator::addStudent() {
    try {
        int student_id, SubjectNumber;
        string first_name, last_name;

        cout << "Enter student ID:" << endl;
        cin >> student_id;
        cout << "Enter first name of student:" << endl;
        cin >> first_name;
        cout << "Enter last name of student:" << endl;
        cin >> last_name;
        cout << "Enter number of subjects Student# " << student_id << " has enrolled in:" << endl;
        cin >> SubjectNumber;

        sql::Statement* stmt = con->createStatement();

        string query = "INSERT INTO STUDENTS VALUES("
                    + to_string(student_id) + ", '"
                    + first_name + "', '"
                    + last_name + "');";
        stmt->executeUpdate(query);

        for (int i = 1; i <= SubjectNumber; i++) {
            int subject_id, grade;
            cout << "Enter Subject ID:" << endl;
            cin >> subject_id;
            cout << "Enter Subject Grade:" << endl;
            cin >> grade;

            query = "INSERT INTO GRADES VALUES("
                    + to_string(subject_id) + ", "
                    + to_string(student_id) + ", "
                    + to_string(grade) + ");";
            stmt->executeUpdate(query);
        }
        delete stmt;
    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CGPACalculator::getStudentCGPA() {
    try {
        string id;
        cout << "Enter student id:" << endl;
        cin >> id;
        sql::Statement* stmt = con->createStatement();
        
        string query = "SELECT GRADE FROM GRADES WHERE STUDENT_ID = " + id + ";";
        sql::ResultSet* res = stmt->executeQuery(query);
        
        int totalGrades = 0;
        int numberOfGrades = 0;
        
        while (res->next()) {
            totalGrades += res->getInt("GRADE");
            numberOfGrades++;
        }
        
        if (numberOfGrades > 0) {
            float cgpa = static_cast<float>(totalGrades) / numberOfGrades;
            cout << "CGPA for student with ID " << id << " is: " << cgpa << endl;
        } else {
            cout << "No grades found for student with ID " << id << endl;
        }
        
        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void CGPACalculator::getAllStudentData() {
    try {
        sql::Statement* stmt = con->createStatement();
        
        string query = "SELECT s.STUDENT_ID, s.FIRST_NAME, s.LAST_NAME, COALESCE(g.GRADE, 0) AS GRADE "
                       "FROM STUDENTS s "
                       "LEFT JOIN GRADES g ON s.STUDENT_ID = g.STUDENT_ID;";
        
        sql::ResultSet* res = stmt->executeQuery(query);
        
        map<int, pair<string, string>> studentDetails;
        map<int, pair<int, int>> studentGrades;

        while (res->next()) {
            int student_id = res->getInt("STUDENT_ID");
            string first_name = res->getString("FIRST_NAME");
            string last_name = res->getString("LAST_NAME");
            int grade = res->getInt("GRADE");

            studentDetails[student_id] = {first_name, last_name};
            studentGrades[student_id].first += grade;
            studentGrades[student_id].second++;
        }
        
        for (const auto& student : studentDetails) {
            int student_id = student.first;
            float averageGrade = studentGrades[student_id].second > 0
                                 ? static_cast<float>(studentGrades[student_id].first) / studentGrades[student_id].second
                                 : 0.0f;

            cout << "ID:"<< student_id << "\t" << "Name:" << student.second.first << " " << student.second.second
                 << "\t" << "CGPA:" << averageGrade << endl;
        }

        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}
