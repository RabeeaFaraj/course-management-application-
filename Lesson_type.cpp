#include "Lesson_type.h"
#include <iostream>
#include <string>


using namespace std;

Lesson_type::Lesson_type() : m_Group_number(""), m_Day(""), m_Beginning_time(""), m_Duration(""), m_Lecturer(""), m_Class("")//Default constructor
{

}

Lesson_type::Lesson_type(const string& group_number, const string& day, const string& beginning_time, const string& duration
    , const string& lecturer, const string& Class) :
    m_Group_number(group_number), m_Day(day), m_Beginning_time(beginning_time)
    , m_Duration(duration), m_Lecturer(lecturer), m_Class(Class)   //constructor
{

}

Lesson_type::Lesson_type(const Lesson_type& other)    // CC
    : m_Group_number(other.m_Group_number), m_Day(other.m_Day), m_Beginning_time(other.m_Beginning_time)
    , m_Duration(other.m_Duration), m_Lecturer(other.m_Lecturer), m_Class(other.m_Class)
{

}

Lesson_type::~Lesson_type()//Destructor
{

}

string Lesson_type::getGroup_number() const
{
    return m_Group_number;
}

string Lesson_type::getDay() const
{
    return m_Day;
}
string Lesson_type::getBeginning_time() const
{
    return m_Beginning_time;
}

string Lesson_type::getDuration() const
{
    return m_Duration;
}

string Lesson_type::getLecturer() const
{
    return m_Lecturer;
}

string Lesson_type::getClass() const
{
    return m_Class;
}

void Lesson_type::setGroup_number(string& Group_number)
{
    m_Group_number = Group_number;
}

void Lesson_type::setDay(string& Day)
{
    m_Day = Day;
}
void Lesson_type::setBeginning_time(string& Beginning_time)
{
    m_Beginning_time = Beginning_time;
}
void Lesson_type::setDuration(string& Duration)
{
    m_Duration = Duration;
}
void Lesson_type::setLecturer(string& Lecturer)
{
    m_Lecturer = Lecturer;
}
void Lesson_type::setClass(string& Class)
{
    m_Class = Class;
}


