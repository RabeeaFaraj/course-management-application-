#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include "Teachers.h" 
#include "Course.h"
#include "Lesson_type.h"
#include "General_system.h"
#include "Admin_user.h"
#include "Schedule.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <exception>
#include <filesystem>

using namespace std;


#define DAYS 7
#define HOURS 10


Admin_user::Admin_user(void) : General_System()// Default constructor
{

}

Admin_user::~Admin_user()//Destructor
{

}

void Admin_user::AddCourse(map<string, Course>& courses, string course_id, string course_name, string head_lecturer, string points)
{
    Course course(course_id, course_name, head_lecturer, points);
    courses[course_id] = course;
}

void Admin_user::RmCourseId(map<string, Course>& courses, string& course_id)
{
    int c_size = course_id.size();
    if (c_size < 14)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        cout << course_id.substr(9, c_size) << endl;
        courses.erase(course_id.substr(9, c_size));
    }
}

void Admin_user::AddStudent(map<string, Student>& students, string student_id, string student_name, string password)
{
    Student student(student_id, student_name, password);
    students[student_id] = student;
}

void Admin_user::RmStudentId(map<string, Student>& students, string& student_id)
{
    int c_size = student_id.size();
    if (c_size < 10)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        cout << student_id.substr(10, c_size) << endl;
        students.erase(student_id.substr(10, c_size));
    }
}

void Admin_user::AddLecturer(map<string, Teacher>& teachers, string lectuer_id, string lecturer_name)
{
    Teacher teacher(lectuer_id, lecturer_name);
    teachers[lectuer_id] = teacher;
}

void Admin_user::RmLecturerId(map<string, Teacher>& teachers, string& lecturer_id)
{
    int c_size = lecturer_id.size();
    if (c_size < 11)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        cout << lecturer_id.substr(11, c_size) << endl;
        teachers.erase(lecturer_id.substr(11, c_size));
    }
}

void Admin_user::Search(string search_txt)
{
    int c_size = search_txt.size();
    if (c_size < 7)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        string search_text = search_txt.substr(7, c_size);
        // Iterate and print elements up to the chunkSize or until the end is reached
        for (auto it = coursesMap.begin(); it != coursesMap.end(); ++it)
        {
            if (it->second.getLecturerName() == search_text || it->second.getCourseID() == search_text
                || it->second.getCourseName() == search_text || it->second.getCreditPoints() == search_text)
            {
                cout << "Courses:" << endl;
                cout << it->second << endl << endl;
            }
        }
        for (auto it = teachersMap.begin(); it != teachersMap.end(); ++it)
        {
            if (it->second.getID() == search_text || it->second.getName() == search_text)
            {
                cout << "Teachers:" << endl;
                cout << it->second << endl << endl;
            }
        }
        for (auto it = studentsMap.begin(); it != studentsMap.end(); ++it)
        {
            if (it->second.getID() == search_text || it->second.getName() == search_text
                || it->second.getPassword() == search_text)
            {
                cout << "Students:" << endl;
                cout << it->second << endl << endl;
            }
        }
    }   
}

void Admin_user::AddLesson(map<string, vector<Lesson_type>>& lessons, string lesson_key, string group_number,
    string day, string beginning_time, string duration, string lecturer, string Class)
{
    Lesson_type lesson(group_number, day, beginning_time, duration, lecturer, Class);
    lessons[lesson_key].push_back(lesson);
}

void Admin_user::RmLesson(map<string, vector<Lesson_type>>& lessons, string id_gnum)
{
    int c_size = id_gnum.size();
    string course_id = id_gnum.substr(9, 5);
    string group_num = id_gnum.substr(15, 2);
    string lab_key = course_id + "_labs.csv";
    string lec_key = course_id + "_lectures.csv";
    string tut_key = course_id + "_tutorials.csv";

    // Find the iterator pointing to the element to erase
    auto it_lab = lessons[lab_key].begin();
    while (it_lab != lessons[lab_key].end()) {
        if (it_lab->getGroup_number() == group_num) {
            it_lab = lessons[lab_key].erase(it_lab);
        }
        else {
            ++it_lab;
        }
    }
    auto it_lec = lessons[lec_key].begin();
    while (it_lec != lessons[lec_key].end()) {
        if (it_lec->getGroup_number() == group_num) {
            it_lec = lessons[lec_key].erase(it_lec);
        }
        else {
            ++it_lec;
        }
    }
    auto it_tut = lessons[tut_key].begin();
    while (it_tut != lessons[tut_key].end()) {
        if (it_tut->getGroup_number() == group_num) {
            it_tut = lessons[tut_key].erase(it_tut);
        }
        else {
            ++it_tut;
        }
    }

    //printing the speciefic lessons after remove
    for (auto it = lessons[lab_key].begin(); it != lessons[lab_key].end(); ++it)
    {
        cout << *it << endl;
    }
    for (auto it = lessons[lec_key].begin(); it != lessons[lec_key].end(); ++it)
    {
        cout << *it << endl;
    }
    for (auto it = lessons[tut_key].begin(); it != lessons[tut_key].end(); ++it)
    {
        cout << *it << endl;
    }
}

void Admin_user::AddLessonFun()
{
    string course_id;
    string l_c = "_";
    string csv = ".csv";
    cout << "Enter a 5-digit course number: ";
    int cnt = 1;
    while (true) {
        cnt = 0;
        cin >> course_id;
        cin.ignore();
        // checking if the course already exists
        for (auto it = lesson_typeMap.begin(); it != lesson_typeMap.end(); ++it) {
            if (it->first.substr(0, 5) == course_id) {
                cnt++;
            }
        }
        if (cnt == 0)
        {
            cout << "Course not exists,try again: ";
            continue;
        }
        else
        {
            cout << "This course exists..." << endl;
            break;
        }
    }
    cout << "Course ID entered successfully: " << course_id << endl;
    cout << endl << "Enter type of lesson(lectures/tutorials/labs): ";
    string lesson_type;
    while ((lesson_type != "lectures") && (lesson_type != "tutorials") && (lesson_type != "labs"))
    {
        cin >> lesson_type;
        cin.ignore();
        if ((lesson_type != "lectures") && (lesson_type != "tutorials") && (lesson_type != "labs"))
            cout << endl << "type of lesson should be -> (lectures/tutorials/labs), try agian: ";
    }
    string lesson_key = course_id + l_c + lesson_type + csv;
    string group_number;
    string lab_key = lesson_key.substr(0, 5) + "_labs.csv";
    string tutorial_key = lesson_key.substr(0, 5) + "_tutorials.csv";
    string lec_key = lesson_key.substr(0, 5) + "_lectures.csv";
    cout << endl << "Enter group_number of two digits only: ";
    int cnt_rep = 1;
    while (group_number.length() != 2 || cnt_rep != 0)
    {
        cnt_rep = 0;
        cin >> group_number;
        cin.ignore();
        // Check if each character of the course_id is a digit
        for (unsigned int i = 0; i < group_number.length(); ++i) {
            if (!isdigit(group_number[i])) {
                cnt_rep++;
                break;
            }
        }
        if (cnt_rep != 0)
        {
            cout << "You didn't enter a 2-digit number, try again: ";
            continue;
        }
        // Check if the course_id is exactly 5 characters long
        if (group_number.length() != 2) {
            cout << "You didn't enter a 2-digit number, try again: ";
        }
        for (auto it = lesson_typeMap[lab_key].begin(); it != lesson_typeMap[lab_key].end(); ++it)
        {
            if (it->getGroup_number() == group_number)
            {
                cout << endl << "this group number already exists,try again: ";
                cnt_rep++;
                break;
            }
        }
        for (auto it = lesson_typeMap[tutorial_key].begin(); it != lesson_typeMap[tutorial_key].end(); ++it)
        {
            if (it->getGroup_number() == group_number)
            {
                cout << endl << "this group number already exists,try again: ";
                cnt_rep++;
                break;
            }
        }
        for (auto it = lesson_typeMap[lec_key].begin(); it != lesson_typeMap[lec_key].end(); ++it)
        {
            if (it->getGroup_number() == group_number)
            {
                cout << endl << "this group number already exists,try again: ";
                cnt_rep++;
                break;
            }
        }
    }
    string day;
    cout << endl << "Enter a day: ";
    if (cin.peek() == '\n')
    {
        cin.get(); // Clear the newline character if present
    }
    getline(cin, day);
    string beginning_time;
    cout << endl << "Enter a beginning_time of the lesson: ";
    if (cin.peek() == '\n')
    {
        cin.get(); // Clear the newline character if present
    }
    getline(cin, beginning_time);
    string duration;
    cout << endl << "Enter a duration of the lesson: ";
    if (cin.peek() == '\n')
    {
        cin.get(); // Clear the newline character if present
    }
    getline(cin, duration);
    string lecturer;
    cout << endl << "Enter name of lecturer: ";
    if (cin.peek() == '\n')
    {
        cin.get(); // Clear the newline character if present
    }
    getline(cin, lecturer);
    string l_Class;
    cout << endl << "Enter name of class: ";
    if (cin.peek() == '\n')
    {
        cin.get(); // Clear the newline character if present
    }
    getline(cin, l_Class);
    AddLesson(lesson_typeMap, lesson_key, group_number, day, beginning_time, duration, lecturer, l_Class);
    cout << endl << lesson_key + ":" << endl;
    //printing
    for (auto it = lesson_typeMap[lesson_key].begin(); it != lesson_typeMap[lesson_key].end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}


