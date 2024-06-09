#ifndef _TEACHER_H_
#define _TEACHER_H_
#include <iostream>
#include <string>
using namespace std;

class Teacher {
protected:
    string m_id;
    string m_name;
public:
    Teacher();//Default constructor
    Teacher(const string& id, const string& name);//constructor
    Teacher(const Teacher& other);
    ~Teacher();
    string getName() const;
    string getID() const;
    void setName(string& name);
    void setID(string& id);

    // Overload operator<< to enable printing of Student objects
    friend ostream& operator<<(ostream& os, const Teacher& teacher) {
        os << "Teacher ID: " << teacher.m_id << ", Name: " << teacher.m_name;
        return os;
    }
};
#endif



