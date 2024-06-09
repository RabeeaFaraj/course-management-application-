#ifndef _COURSE_H_
#define _COURSE_H_
#include <iostream>
#include <string>
using namespace std;

class Course {
private:
    string m_courseID;
    string m_courseName;
    string m_lecturerName;
    string m_creditPoints;

public:
    Course();
    Course(const string& courseID, const string& courseName, const string& lecturerName, const string& creditPoints);
    Course(const Course& other);
    ~Course();
    string getCourseID() const;
    string getCourseName() const;
    string getLecturerName() const;
    string getCreditPoints() const;
    void setCourseID(string& courseID);
    void setCourseName(string& courseName);
    void getLecturerName(string& lecturerName);
    void setCreditPoints(string& creditPoints);

    // Overload operator<< to enable printing of Student objects
    friend ostream& operator<<(ostream& os, const Course& course) {
        os << "Course_id: " << course.m_courseID << ", Course Name: "
            << course.m_courseName << ", head_lecturer: " << course.m_lecturerName
            << ", points: " << course.m_creditPoints;
        return os;
    }
};
#endif