#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_
#include "Lesson_type.h"

class Schedule : public Lesson_type {
private:
    string m_course_id;
    string m_lesson;

public:
    Schedule();
    Schedule(const string& course_id, const string& lesson, const string& group_number, const string& day, const string& beginning_time, const string& duration
        , const string& lecturer, const string& Class);
    Schedule(const Schedule& other);
    ~Schedule();
    string getCourseID() const;
    void setCourseID(string& course_id);
    string getLesson() const;
    void setLesson(string& lesson);
    string toCSVString() const;
    static Schedule fromCSVString(const string& csvString);
    //void printlessons(map<int, vector<Schedule>>& schedule_typeMap);

    // Overload operator<< to enable printing of Student objects
    friend ostream& operator<<(ostream& os, const Schedule& csv) {
        os << "Course ID: " << csv.m_course_id << ", Lesson type: " << csv.m_lesson << ", Group number: " << csv.m_Group_number << ", Day: " << csv.m_Day << ", Beginning time: " << csv.m_Beginning_time
            << ", Duration: " << csv.m_Duration << ", Lecturer: " << csv.m_Lecturer << ", Class: " << csv.m_Class;
        return os;
    }
};
#endif