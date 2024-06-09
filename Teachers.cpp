#include "Teachers.h"
#include <iostream>
#include <string>
using namespace std;


Teacher::Teacher() :m_id(""), m_name("")//Default constructor
{

}

Teacher::Teacher(const string& id, const string& name) : m_id(id), m_name(name)//constructor
{

}

Teacher::Teacher(const Teacher& other) : m_id(other.m_id), m_name(other.m_name) //copy constructor
{

}

Teacher::~Teacher()//Destructor
{

}

string Teacher::getName() const
{
    return m_name;
}

string Teacher::getID() const
{
    return m_id;
}


void Teacher::setName(string& name)
{
    m_name = name;
}

void Teacher::setID(string& id)
{
    m_id = id;
}

