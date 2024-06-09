#include "Schedule.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Schedule::Schedule() :Lesson_type(m_Group_number, m_Day, m_Beginning_time, m_Duration, m_Lecturer, m_Class), m_course_id(""), m_lesson("") //Default constructor
{

}

Schedule::Schedule(const string& course_id, const string& lesson, const string& group_number, const string& day, const string& beginning_time, const string& duration
    , const string& lecturer, const string& Class) : Lesson_type(group_number, day, beginning_time, duration, lecturer, Class)
    , m_course_id(course_id), m_lesson(lesson)   //constructor
{

}

Schedule::Schedule(const Schedule& other)    // CC
    : m_course_id(other.m_course_id), m_lesson(other.m_lesson), Lesson_type(other.m_Group_number, other.m_Day, other.m_Beginning_time
        , other.m_Duration, other.m_Lecturer, other.m_Class)
{

}

Schedule::~Schedule()//Destructor
{

}

string Schedule::getCourseID() const
{
    return m_course_id;
}

void Schedule::setCourseID(string& course_id)
{
    m_course_id = course_id;
}

string Schedule::getLesson() const
{
    return m_lesson;
}

void Schedule::setLesson(string& lesson)
{
    m_lesson = lesson;
}

string Schedule::toCSVString() const {
    return m_course_id + "," + m_lesson + "," + m_Group_number + "," + m_Day + "," + m_Beginning_time + "," +
        m_Duration + "," + m_Lecturer + "," + m_Class;
}

Schedule Schedule::fromCSVString(const string& csvString) {
    stringstream ss(csvString);
    string course_id, lesson, group_number, day, beginning_time, duration, lecturer, class_room;

    getline(ss, course_id, ',');
    getline(ss, lesson, ',');
    getline(ss, group_number, ',');
    getline(ss, day, ',');
    getline(ss, beginning_time, ',');
    getline(ss, duration, ',');
    getline(ss, lecturer, ',');
    getline(ss, class_room, ',');


    return Schedule(course_id, lesson, group_number, day, beginning_time, duration, lecturer, class_room);
}