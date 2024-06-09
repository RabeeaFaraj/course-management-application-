#ifndef _STUDENT_H_
#define _STUDENT_H_
#include "Teachers.h"

class Student : public Teacher {
private:
    string m_password;

public:
    Student();
    Student(const string& id, const string& name, const string& password);
    Student(const Student& other);
    ~Student();
    string getPassword() const;
    void setPassword(string& password);


    // Overload operator<< to enable printing of Student objects
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Student ID: " << student.m_id << ", Name: " << student.m_name << ", Password: " << student.m_password;
        return os;
    }
};
#endif