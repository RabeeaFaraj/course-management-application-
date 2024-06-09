#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student() : Teacher(m_id, m_name), m_password("")//Default constructor
{

}

Student::Student(const string& id, const string& name, const string& password) : Teacher(id, name), m_password(password)//constructor
{

}

Student::Student(const Student& other) : Teacher(other.m_id, other.m_name), m_password(other.m_password)//copy constructor
{

}

Student::~Student()//Destructor
{

}

string Student::getPassword() const
{
    return m_password;
}

void Student::setPassword(string& password)
{
    m_password = password;
}