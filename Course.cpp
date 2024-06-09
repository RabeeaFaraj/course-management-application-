#include "Course.h"
#include <iostream>
#include <string>

using namespace std;

Course::Course() : m_courseID(""), m_courseName(""), m_lecturerName(""), m_creditPoints("")//Default constructor
{

}

Course::Course(const string& courseID, const string& courseName, const string& lecturerName, const string& creditPoints)
    : m_courseID(courseID), m_courseName(courseName), m_lecturerName(lecturerName), m_creditPoints(creditPoints)//constructor
{

}

Course::Course(const Course& other)
    : m_courseID(other.m_courseID), m_courseName(m_courseName), m_lecturerName(other.m_lecturerName), m_creditPoints(other.m_creditPoints)//copy constructor
{

}

Course::~Course()//Destructor
{

}

string Course::getCourseID() const
{
    return m_courseID;
}

string Course::getCourseName() const
{
    return m_courseName;
}

string Course::getLecturerName() const
{
    return m_lecturerName;
}

string Course::getCreditPoints() const
{
    return m_creditPoints;
}

void Course::setCourseID(string& courseID)
{
    m_courseID = courseID;
}

void Course::setCourseName(string& courseName)
{
    m_courseName = courseName;
}

void Course::getLecturerName(string& lecturerName)
{
    m_lecturerName = lecturerName;
}

void Course::setCreditPoints(string& creditPoints)
{
    m_creditPoints = creditPoints;
}

