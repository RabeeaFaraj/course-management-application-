#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include "Teachers.h" 
#include "Course.h"
#include "Lesson_type.h"
#include "General_system.h"
#include "Student_user.h"
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
namespace fs = filesystem;
int General_System::schedule_key = 0;

#define DAYS 7
#define HOURS 10

General_System::General_System(void) :student_user(nullptr), admin_user(nullptr)// Default constructor
{
    string path = "."; // Current directory. Adjust as needed.
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                string extension = entry.path().extension().string();
                string filename = entry.path().filename().string();
                if (extension == ".csv") {
                    if (filename == "Students.csv") {
                        loadStudents(filename, studentsMap);
                    }
                    else if (filename == "Teachers.csv") {
                        loadTeachers(filename, teachersMap);
                    }
                    else if (filename == "Courses.csv") {
                        loadCourses(filename, coursesMap);
                    }
                    else {
                        loadlesson_type(filename, lesson_typeMap);
                    }
                }
            }
        }
    }
    catch (const filesystem::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "General error: " << e.what() << endl;
    }
}

General_System::General_System(const General_System& other)    // CC
    : lesson_typeMap(other.lesson_typeMap), studentsMap(other.studentsMap), teachersMap(other.teachersMap)
    , coursesMap(other.coursesMap), schedule_typeMap(other.schedule_typeMap)
{
    if (other.student_user) {
        student_user = new Student_user(*dynamic_cast<Student_user*>(other.student_user));
    }
    else {
        student_user = nullptr;
    }
    if (other.admin_user) {
        admin_user = new Student_user(*dynamic_cast<Student_user*>(other.admin_user));
    }
    else {
        admin_user = nullptr;
    }
}

General_System::~General_System()//Destructor
{
    /*if (student_user) {
        delete student_user;
    }*/
    delete student_user;
    /*if (admin_user) {
        delete admin_user;
    }*/
    delete admin_user;
}

void General_System::Generator(void)
{
    admin_user = new Admin_user;
    Admin_user Admin;
    string exitAll, exitch, pass, c_pass = "admin";
    while (exitAll != "exit")
    {
        cout << "choose your status:" << endl << "1.admin" << endl << "2.student" << endl << "3.exit" << endl;
        string x = "0", y = "0";
        while (x != "1" && x != "2" && x != "3")
        {
            cin >> x;
            cin.ignore();
            if (x != "1" && x != "2" && x != "3")
            {
                cout << "you didn't choose 1 or 2 or 3, try again:" << endl;
            }
        }
        if (x == "3")
        {
            break;
        }
        if (x == "1")
        {
            cout << "enter your password: ";
            while (pass != c_pass)
            {
                cin >> pass;
                cin.ignore();
                if (pass != c_pass)
                    cout << "worng password, please enter the right password:" << endl;
            }
            cout << "do you want to change password" << endl << "1.yes" << endl << "2.no" << endl;
            while (y != "1" && y != "2")
            {
                cin >> y;
                if (y != "1" && y != "2")
                    cout << "you didn't choose 1 or 2, try again:" << endl;
            }
            if (y == "1")
            {
                cout << "choose a new password:" << endl;
                cin >> c_pass;
                cin.ignore();
            }
            string choice;
            while (choice != "exit")
            {
                cout << "Write down one of the options below:" << endl << "Print<course_id>" << endl << "PrintCourses" << endl
                    << "AddCourse" << endl << "RmCourse<course_id>" << endl << "AddLecturer" << endl
                    << "RmLecturer<lecturer_id>" << endl << "AddStudent" << endl << "RmStudent<student_id>" << endl << "AddLesson" << endl
                    << "RmLesson<course_id><group_number>" << endl << "Search<search_text>" << endl << "exit" << endl;
                if (cin.peek() == '\n')
                {
                    cin.get(); // Clear the newline character if present
                }
                getline(cin, choice);
                cout << endl;
                if (choice == "PrintCourses")
                {
                    PrintCourses(coursesMap);
                }
                else if (choice == "AddCourse")
                {
                    string course_id;
                    int len = 5;
                    cout << "Enter a 5-digit course number: ";
                    while (true) {
                        cin >> course_id;
                        cin.ignore();
                        // checking if the course already exists
                        if (Valid_id(course_id, coursesMap, len)) {
                            break;
                        }
                    }
                    cout << endl << "Course ID entered successfully: " << course_id << endl;
                    string course_name;
                    cout << endl << "Enter name of course: ";
                    if (cin.peek() == '\n')
                    {
                        cin.get(); // Clear the newline character if present
                    }
                    getline(cin, course_name);
                    cout << endl << "Enter name of head_lecturer: ";
                    string head_lecturer;
                    if (cin.peek() == '\n')
                    {
                        cin.get(); // Clear the newline character if present
                    }
                    getline(cin, head_lecturer);
                    cout << endl << "Enter number of points between 1-5: ";
                    string points;
                    do
                    {
                        cin >> points;
                        if (points != "1" && points != "2" && points != "3" && points != "4" && points != "5")
                            cout << endl << "you didnt enter number between 1-5,try again: ";
                    } while (points != "1" && points != "2" && points != "3" && points != "4" && points != "5");
                    Admin.AddCourse(coursesMap, course_id, course_name, head_lecturer, points);
                    cout << "Courses:\n";
                    printMap(coursesMap);
                    cout << endl;
                }
                else if (choice.substr(0, 5) == "Print")
                {
                    PrintCourseId(coursesMap, choice);
                }
                else if (choice.substr(0, 8) == "RmCourse")
                {
                    Admin.RmCourseId(coursesMap, choice);
                    cout << "Courses:\n";
                    printMap(coursesMap);
                    cout << endl;
                }
                else if (choice == "AddStudent")
                {
                    string student_id;
                    int len = 9;
                    cout << "Enter student ID: ";
                    while (true) {
                        cin >> student_id;
                        cin.ignore();
                        // checking if the course already exists
                        if (Valid_id(student_id, studentsMap, len)) {
                            break;
                        }
                    }
                    cout << endl << "Student ID entered successfully: " << student_id << endl;
                    cout << endl << "Enter name of student: ";
                    string student_name;
                    if (cin.peek() == '\n')
                    {
                        cin.get(); // Clear the newline character if present
                    }
                    getline(cin, student_name); // Read the entire line, including spaces
                    cout << endl << "Enter password: ";
                    string password;
                    if (cin.peek() == '\n')
                    {
                        cin.get(); // Clear the newline character if present
                    }
                    getline(cin, password);
                    Admin.AddStudent(studentsMap, student_id, student_name, password);
                    cout << "Students:\n";
                    printMap(studentsMap);
                    cout << endl;
                }
                else if (choice.substr(0, 9) == "RmStudent")
                {
                    Admin.RmStudentId(studentsMap, choice);
                    cout << "Students:\n";
                    printMap(studentsMap);
                    cout << endl;
                }
                else if (choice == "AddLecturer")
                {
                    string Lecturer_id;
                    int len = 9;
                    cout << "Enter Lecturer ID: ";
                    while (true) {
                        cin >> Lecturer_id;
                        cin.ignore();
                        // checking if the course already exists
                        if (Valid_id(Lecturer_id, teachersMap, len)) {
                            break;
                        }
                    }
                    cout << endl << "Teacher ID entered successfully: " << Lecturer_id << endl;
                    string Lecturer_Name;
                    cout << "Enter the Name of the Lecturer: ";
                    if (cin.peek() == '\n')
                    {
                        cin.get(); // Clear the newline character if present
                    }
                    getline(cin, Lecturer_Name);
                    cout << Lecturer_Name << endl;
                    Admin.AddLecturer(teachersMap, Lecturer_id, Lecturer_Name);
                    cout << "Teachers:\n";
                    printMap(teachersMap);
                    cout << endl;
                }
                else if (choice.substr(0, 10) == "RmLecturer")
                {
                    Admin.RmLecturerId(teachersMap, choice);
                    cout << "Teachers:\n";
                    printMap(teachersMap);
                    cout << endl;
                }
                else if (choice.substr(0, 6) == "Search")
                {
                    admin_user->Search(choice);
                }
                else if (choice == "AddLesson")
                {
                    Admin.AddLessonFun();
                }
                else if (choice.substr(0, 8) == "RmLesson")
                {
                    Admin.RmLesson(lesson_typeMap, choice);
                }
                else if (choice == "exit")
                {
                    break;
                }
                else
                    cout << "you didn't write one of the options below, try again... " << endl << endl;
            }
        }
        if (x == "2")
        {
            string id, password = "0";
            int cnt = 0;
            cout << "Plaese enter your ID: ";
            do
            {
                cin >> id;
                cout << endl;
                for (auto it = studentsMap.begin(); it != studentsMap.end(); ++it)
                {
                    if (it->first == id)
                    {
                        cout << "Hello " << studentsMap[id].getName() << endl;
                        cnt = 1;
                        break;
                    }
                }
                if (cnt == 0)
                {
                    cout << "your ID is wrong!!! " << endl << "try again: ";
                }
            } while (cnt != 1);
            cout << "plaese enter your password: ";
            while (studentsMap[id].getPassword() != password)
            {
                cin >> password;
                if (studentsMap[id].getPassword() != password)
                {
                    cout << "your password is wrong!!! " << endl << "try again: ";
                }
            }
            string choice = "";
            while (choice != "exit")
            {
                cout << "Write down one of the actions below:" << endl << "Print<course_id>" << endl << "PrintCourses" << endl
                    << "Schedule" << endl << "exit" << endl;
                if (cin.peek() == '\n')
                {
                    cin.get(); // Clear the newline character if present
                }
                getline(cin, choice);
                cout << endl;
                if (choice == "PrintCourses")
                {
                    PrintCourses(coursesMap);
                }
                else if (choice.substr(0, 5) == "Print")
                {
                    PrintCourseId(coursesMap, choice);
                }
                else if (choice == "Schedule")
                {
                    funSchedule(id);
                }
            }
        }
    }
    try
    {
        saveStudents("Students.csv", studentsMap);
    }
    catch (const exception& e) {
        cerr << "Error in destructor while saving students: " << e.what() << endl;
    }

    try {
        saveTeachers("Teachers.csv", teachersMap);
    }
    catch (const exception& e) {
        cerr << "Error in destructor while saving teachers: " << e.what() << endl;
    }

    try {
        saveCourses("Courses.csv", coursesMap);
    }
    catch (const exception& e) {
        cerr << "Error in destructor while saving courses: " << e.what() << endl;
    }

    try {
        saveLessonTypes("LessonTypes.csv", lesson_typeMap);
    }
    catch (const exception& e) {
        cerr << "Error in destructor while saving lesson types: " << e.what() << endl;
    }
    exitAll = "exit";
}

void General_System::funSchedule(string id)
{
    student_user = new Student_user;
    Student_user Stu_user;
    string choice = " ";
    schedule_typeMap = Stu_user.readCSV(id + ".csv");
    schedule_key = schedule_typeMap.size();
    while (choice != "Back")
    {
        cout << "Write down one of the actions below:" << endl << "Print<schedule_id>" << endl << "PrintAll" << endl
            << "AddSchedule" << endl << "RmSchedule<schedule_id>" << endl << "Add<schedule><courses_id><group_id>" << endl
            << "Rm<schedule><courses_id><group_id>" << endl << "search<course_id>" << endl << "RmAllSchedule" << endl <<
            "check_Day/Time" << endl << "ReadySchedule<year><semester>" << endl << "Back" << endl;
        if (cin.peek() == '\n')
        {
            cin.get(); // Clear the newline character if present
        }
        getline(cin, choice);
        cout << endl;
        if (choice == "PrintAll")
        {
            Stu_user.Printall(schedule_typeMap);
        }
        else if (choice.substr(0, 5) == "Print")
        {
            Stu_user.PrintSchedule(choice, schedule_typeMap);
        }
        else if (choice == "AddSchedule")
        {
            schedule_key++;
            schedule_typeMap[schedule_key];
            cout << "Add an empty Schedule" << endl << endl;
        }
        else if (choice.substr(0, 3) == "Add")
        {
            Stu_user.Add_less_sch(choice, lesson_typeMap, schedule_typeMap);
        }
        else if (choice.substr(0, 10) == "RmSchedule")
        {
            Stu_user.RemoveSchedule(choice, schedule_typeMap);
        }
        else if (choice == "RmAllSchedule")
        {
            Stu_user.deleteAllSchedules(schedule_typeMap);
        }
        else if (choice.substr(0, 2) == "Rm")
        {
            Stu_user.RemoveLesson(choice, schedule_typeMap);
        }
        else if (choice.substr(0, 6) == "search")
        {
            student_user->Search(choice);
        }
        else if (choice == "Back")
        {
            Stu_user.writeCSV(schedule_typeMap, id + ".csv");
            break;
        }
        else if (choice == "check_Day/Time")
        {
            Stu_user.checkForOverlapsInLessons(lesson_typeMap);
        }
        else if (choice.substr(0, 13) == "ReadySchedule")
        {
            Stu_user.AddSchedule();
            auto newScheduleMap = Stu_user.getReadySchedule(choice);

            // Merge new schedules wit' di existing ones
            for (const auto& newSchedule : newScheduleMap)
            {
                auto& existingSchedules = schedule_typeMap[newSchedule.first];

                // Add new schedules to existing schedules
                existingSchedules.insert(existingSchedules.end(), newSchedule.second.begin(), newSchedule.second.end());
            }
        }
        else
            cout << "you didn't write one of the options below, try again... " << endl << endl;
    }
}

void General_System::loadStudents(const string& filename, map<string, Student>& students) {
    ifstream file(filename);
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, password;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, password, ',');
        Student student(id, name, password);
        students[id] = student;
    }
    file.close();
}

//----------------------------------------------------------------------------------------------
void General_System::loadTeachers(const string& filename, map<string, Teacher>& teachers) {
    ifstream file(filename);
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name;
        getline(ss, id, ',');
        getline(ss, name, ',');
        Teacher teacher(id, name);
        teachers[id] = teacher;
    }
    file.close();
}

//----------------------------------------------------------------------------------------------
void General_System::loadCourses(const string& filename, map<string, Course>& courses) {
    ifstream file(filename);
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, lecturer, credits;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, lecturer, ',');
        getline(ss, credits, ',');
        Course course(id, name, lecturer, credits);
        courses[id] = course;
    }
    file.close();
}

//----------------------------------------------------------------------------------------------
void General_System::loadlesson_type(const string& filename, map<string, vector<Lesson_type>>& lesson_types) {
    ifstream file(filename);
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string group_number, day, beginning_time, duration, lecturer, Class;
        getline(ss, group_number, ',');
        getline(ss, day, ',');
        getline(ss, beginning_time, ',');
        getline(ss, duration, ',');
        getline(ss, lecturer, ',');
        getline(ss, Class, ',');
        Lesson_type lesson_type(group_number, day, beginning_time, duration, lecturer, Class);
        lesson_types[filename].push_back(lesson_type);
    }
    file.close();
}

void General_System::saveStudents(const string& filename, const map<string, Student>& students) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing: " + filename);
        }

        // Write header
        file << "ID,Name,Password\n";

        for (const auto& [id, student] : students) {
            file << id << "," << student.getName() << "," << student.getPassword() << "\n";
        }

        file.close();
    }
    catch (const exception& e) {
        cerr << "Error saving students: " << e.what() << endl;
    }
}

void General_System::saveTeachers(const string& filename, const map<string, Teacher>& teachers) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing: " + filename);
        }

        // Write header
        file << "ID,Name\n";

        for (const auto& [id, teacher] : teachers) {
            file << id << "," << teacher.getName() << "\n";
        }

        file.close();
    }
    catch (const exception& e) {
        cerr << "Error saving teachers: " << e.what() << endl;
    }
}

void General_System::saveCourses(const string& filename, const map<string, Course>& courses) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing: " + filename);
        }

        // Write header
        file << "ID,Name,Lecturer,Credits\n";

        for (const auto& [id, course] : courses) {
            file << id << "," << course.getCourseName() << "," << course.getLecturerName() << "," << course.getCreditPoints() << "\n";
        }

        file.close();
    }
    catch (const exception& e) {
        cerr << "Error saving courses: " << e.what() << endl;
    }
}

void General_System::saveLessonTypes(const string& filename, const map<string, vector<Lesson_type>>& lesson_types) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file for writing: " + filename);
        }

        // Write header
        file << "GroupNumber,Day,BeginningTime,Duration,Lecturer,Class\n";

        for (const auto& [filename, lessons] : lesson_types) {
            for (const auto& lesson : lessons) {
                file << lesson.getGroup_number() << "," << lesson.getDay() << ","
                    << lesson.getBeginning_time() << "," << lesson.getDuration() << ","
                    << lesson.getLecturer() << "," << lesson.getClass() << "\n";
            }
        }

        file.close();
    }
    catch (const exception& e) {
        cerr << "Error saving lesson types: " << e.what() << endl;
    }
}


//----------------------------------------------------------------------------------------------
template<typename T>
void General_System::printMap(const map<string, T>& map)
{
    int i = 1; // Counter to show the index
    for (const pair<const string, T>& pair : map) {
        cout << i << ": " << "key-" << pair.first << " ; value-" << pair.second << endl;
        i++;
    }
}

void General_System::PrintCourses(map<string, Course>& courses)
{
    auto it = courses.begin();
    int count = 0;
    int choice = 0;
    int C_size = courses.size();
    while (choice != 2)
    {
        if (C_size < 10)
        {
            // Iterate and print elements up to the chunkSize or until the end is reached
            for (; it != courses.end() && count < C_size; ++it, ++count) {
                cout << it->first << ": " << it->second << endl << endl;
            }
            C_size = 0;
            if (it == courses.end()) {
                cout << "No more courses." << endl << endl;
            }
        }
        else
        {
            // Iterate and print elements up to the chunkSize or until the end is reached
            for (; it != courses.end() && count < 10; ++it, ++count) {
                cout << it->first << ": " << it->second << endl << endl;
            }
            C_size = C_size - 10;
        }
        cout << "choose your option: " << endl << "1.More" << endl << "2.exit" << endl;
        cin >> choice;
        count = 0;
    }
}

void General_System::PrintCourseId(map<string, Course>& courses, string& course_id)
{
    int c_size = course_id.size();
    bool exists = false;
    if (c_size < 11)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        for (auto it = courses.begin(); it != courses.end(); ++it) {
            if (it->first == course_id.substr(6, c_size)) {
                exists = true;
            }
        }
        if (exists)
        {
            cout << courses[course_id.substr(6, c_size)] << endl << endl;
        }
        else
            cout << "This course doesn't exsits... " << endl << endl;

    }    
}


template<class T>
bool General_System::Valid_id(string id, map<string, T>& map, int len) {
    // Check if the course already exists
    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it->first.substr(0, len) == id) {
            cout << "This course already exists, try again: ";
            //cnt++;
            return false;
        }
    }
    // Check if the course_id is exactly 5 characters long
    if (id.length() != len) {
        cout << "You didn't enter a 5-digit number, try again: ";
        return false;
    }
    // Check if each character of the course_id is a digit
    for (unsigned int i = 0; i < id.length(); ++i) {
        if (!isdigit(id[i])) {
            cout << "You didn't enter a 5-digit number, try again: ";
            return false;
        }
    }
    return true;
}


