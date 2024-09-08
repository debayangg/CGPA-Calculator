# CGPA Calculator
## Description
The CGPA Calculator is a C++ program that allows users to manage student information and calculate CGPA (Cumulative Grade Point Average). This program interacts with a MySQL database to store and retrieve student details and grades. It provides options to add new student details, calculate the CGPA of a student, and print all students' CGPA.
## Features
* **Add Student:** Enter details for a new student, including ID, name, and grades for various subjects.
* **Find CGPA:** Calculate and display the CGPA of a student based on their grades.
* **Print All Students' Data:** Display all students' details along with their CGPA.
## Requirements
* MySQL database server
* MySQL Connector/C++ (for database connectivity)
* C++ compiler (e.g., g++)
## Setup
1. **Install MySQL:**
   Ensure that MySQL is installed and running on your system. Create a MySQL user and grant necessary privileges.
2. **Install MySQL Connector/C++:**
   Download and install the MySQL Connector/C++ from the [official MySQL website](https://dev.mysql.com/downloads/connector/cpp/).
3. **Configure Database Credentials:**
   Create the `creds.h` file with your MySQL username and password in the following format:
   ```c++
   #include<string>

   namespace creds
   {
     std::string username = "username";
     std::string password = "password";
   };
   ```
5. **Compile the Program:**
   Use a C++ compiler to compile the program. For example, using `g++`:
   ```bash
   g++ -o CGPACalculator CGPACalculator.cpp -lmysqlcppconn
   ```
6. **Run the Program:**
   Execute the compiled program:
   ```bash
   ./CGPACalculator
   ```
## Usage
1. **Add Student:**
   - Select option 1 to enter new student details.
   - Provide the student's ID, first name, last name, and grades for each subject.
2. **Find CGPA:**
   - Select option 2 to find the CGPA of a student.
   - Enter the student ID to view their CGPA.
3. **Print All Students' Data:**
   - Select option 3 to display all students' details and CGPA.
4. **Exit:**
   - Select option 4 to exit the program.
## File Structure
* `CGPACalculator.cpp`: Main C++ source file containing the program logic.
* `CGPACalculator.h`: Header file for the `CGPACalculator` class.
* `creds.h`: File containing database credentials.
## Error Handling
* SQL errors are handled and printed to the console. Ensure that your MySQL server is running and the database credentials are correct.
## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
