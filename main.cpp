#include "CGPACalculator.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int menuChoice=0;
    CGPACalculator calculator;
    while(menuChoice!=4)
    {
        cout<<"--------- CGPA Calculator ---------"<<endl;
        cout<<"Options:"<<endl;
        cout<<"1.Enter new student details"<<endl;
        cout<<"2.Find CGPA of a student"<<endl;
        cout<<"3.Print all students CGPA"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice:"<<endl;

        cin>>menuChoice;

        switch (menuChoice)
        {
        case 1: calculator.addStudent();
            break;
        case 2: calculator.getStudentCGPA();
            break;
        case 3: calculator.getAllStudentData();
            break;
        case 4: 
            break;
        default: cout<<"Option "<<menuChoice<<" is not valid"<<endl;
            exit(0);
            break;
        }
    }

    return 0;
}