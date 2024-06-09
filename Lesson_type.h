#ifndef _LESSON_TYPE_H_
#define _LESSON_TYPE_H_
#include <iostream>
#include <string>


using namespace std;

class Lesson_type {
protected:
    string m_Group_number;
    string m_Day;
    string m_Beginning_time;
    string m_Duration;
    string m_Lecturer;
    string m_Class;

public:
    Lesson_type();
    Lesson_type(const string& group_number, const string& day, const string& beginning_time, const string& duration
        , const string& lecturer, const string& Class);
    Lesson_type(const Lesson_type& other);
    ~Lesson_type();
    string getGroup_number() const;
    string getDay() const;
    string getBeginning_time() const;
    string getDuration() const;
    string getLecturer() const;
    string getClass() const;
    void setGroup_number(string& Group_number);
    void setDay(string& Day);
    void setBeginning_time(string& Beginning_time);
    void setDuration(string& Duration);
    void setLecturer(string& Lecturer);
    void setClass(string& Class);

    // Overload operator<< to enable printing of Student objects virtual
    friend ostream& operator<<(ostream& os, const Lesson_type& csv) {
        os << "Group number: " << csv.m_Group_number << ", Day: " << csv.m_Day << ", Beginning time: " << csv.m_Beginning_time
            << ", Duration: " << csv.m_Duration << ", Lecturer: " << csv.m_Lecturer << ", Class: " << csv.m_Class;
        return os;
    }
};
#endif
