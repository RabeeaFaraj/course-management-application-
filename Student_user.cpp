#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include "Teachers.h" 
#include "Course.h"
#include "Lesson_type.h"
#include "General_system.h"
#include "Student_user.h"
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


Student_user::Student_user(void) : General_System()// Default constructor
{

}

Student_user::~Student_user()//Destructor
{

}



map<int, vector<Schedule>> Student_user::readCSV(const string& filename) {

    map<int, vector<Schedule>> scheduleTypeMap;

    try {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for reading");
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            int key;

            getline(ss, item, ',');
            key = stoi(item);

            string scheduleData;
            getline(ss, scheduleData);
            Schedule schedule = Schedule::fromCSVString(scheduleData);

            scheduleTypeMap[key].push_back(schedule);
        }

        // Ensure file stream state is checked before closing
        if (file.bad()) {
            throw runtime_error("Error occurred while reading the file");
        }

        file.close();

    }
    catch (const exception& e) {
        cerr << "An error occurred while reading the file: " << e.what() << endl;
    }

    return scheduleTypeMap;
}

void Student_user::writeCSV(const map<int, vector<Schedule>>& scheduleTypeMap, const string& filename) {
    try {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open file for writing");
        }

        for (const auto& pair : scheduleTypeMap) {
            int key = pair.first;
            const vector<Schedule>& schedules = pair.second;

            for (const auto& schedule : schedules) {
                file << key << "," << schedule.toCSVString() << "\n";
            }
        }

        file.flush(); // Ensure all data is written to the file
        if (file.fail()) {
            throw runtime_error("Error occurred while flushing the file buffer");
        }

        file.close();
        if (file.fail()) {
            throw runtime_error("Error occurred while closing the file after writing");
        }
    }
    catch (const exception& e) {
        cerr << "An error occurred while writing the file: " << e.what() << endl;
    }
}

void Student_user::printScheduleById(int scheduleId, map<int, vector<Schedule>>& scheduleTypeMa)
{
    const string days[DAYS] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    const string hours[HOURS] = { "08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00" };

    // Find the schedule by ID
    auto it = scheduleTypeMa.find(scheduleId);
    if (it == scheduleTypeMa.end())
    {
        cout << "Schedule with ID " << scheduleId << " not found." << endl;
        return;
    }

    vector<Schedule> schedule = it->second;

    // Prepare a 2D vector to store the schedule
    vector<vector<string>> scheduleTable(HOURS, vector<string>(DAYS, ""));

    // Populate the schedule table
    for (const auto& lesson : schedule) {
        int dayIndex = -1;
        for (int d = 0; d < DAYS; ++d) {
            if (lesson.getDay() == days[d]) {
                dayIndex = d;
                break;
            }
        }
        if (dayIndex == -1) continue; // Skip if the day is not found

        int hourIndex = -1;
        for (int h = 0; h < HOURS; ++h) {
            if (lesson.getBeginning_time() == hours[h]) {
                hourIndex = h;
                break;
            }
        }
        if (hourIndex == -1) continue; // Skip if the hour is not found

        int duration = stoi(lesson.getDuration());
        for (int d = 0; d < duration && hourIndex + d < HOURS; ++d) {
            scheduleTable[hourIndex + d][dayIndex] = lesson.getCourseID() + "(" + lesson.getLesson() + ")";
        }
    }
    // Print the header with more spaces between days
    cout << setw(10) << " " << days[0];
    for (int d = 1; d < DAYS; ++d) {
        cout << setw(12) << " " << days[d];
    }
    cout << endl;

    // Print the schedule table
    for (int h = 0; h < HOURS; ++h) {
        cout << hours[h];
        for (int d = 0; d < DAYS; ++d)
        {
            if (d <= 2)
                cout << setw(17) << scheduleTable[h][d] << "|";
            else if (d > 2 && d <= 4)
                cout << setw(21) << scheduleTable[h][d] << "|";
            else
                cout << setw(15) << scheduleTable[h][d] << "|";

        }
        cout << endl;
    }
}

void Student_user::deleteAllSchedules(map<int, vector<Schedule>>& scheduleTypeMap)
{
    if (scheduleTypeMap.empty())
    {
        cout << "Your schedule is empty." << endl << endl;
    }
    else
    {
        scheduleTypeMap.clear();
        schedule_key = 0;
    }
}

void Student_user::checkForOverlapsInLessons(const map<string, vector<Lesson_type>>& lesson_types) {
    map<string, vector<Lesson_type>> lessonMap;

    const string days[DAYS] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    const string hours[HOURS] = { "08:00", "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00" };

    // Populate the lessonMap with actual lessons
    for (const auto& subject : lesson_types) {
        string course_id = subject.first;
        for (const auto& lesson : subject.second) {
            string day = lesson.getDay();
            string time = lesson.getBeginning_time();
            bool validDay = false, validTime = false;

            for (int i = 0; i < DAYS; ++i) {
                if (days[i] == day) {
                    validDay = true;
                    break;
                }
            }

            for (int i = 0; i < HOURS; ++i) {
                if (hours[i] == time) {
                    validTime = true;
                    break;
                }
            }

            if (validDay && validTime) {
                string dayTime = day + " " + time;
                lessonMap[dayTime].push_back(lesson);
            }
        }
    }

    // Check for overlaps
    for (const auto& entry : lessonMap) {
        if (entry.second.size() > 1) {
            cout << "Overlap found for " << entry.first << ":\n";
            map<string, bool> printed;  // To avoid duplicate prints
            for (const auto& lesson : entry.second) {
                stringstream ss;
                ss << lesson.getDay() << lesson.getBeginning_time() << lesson.getClass() << lesson.getGroup_number();
                string uniqueKey = ss.str();

                if (printed.find(uniqueKey) == printed.end()) {
                    cout << "Class num: " << lesson.getClass() << "  Group number: " << lesson.getGroup_number()
                        << ", Lecturer: " << lesson.getLecturer() << endl;
                    printed[uniqueKey] = true;
                }
            }
        }
    }
}

map<int, vector<Schedule>> Student_user::getReadySchedule(const string& choice)
{
    int c_size = choice.size();
    int s_size = choice.size() - 16;
    string year = choice.substr(13 + s_size, 1);
    string sem = choice.substr(15 + s_size, c_size);
    cout << year << endl;
    cout << sem << endl;
    map<int, vector<Schedule>> scheduleTypeMap;

    try {
        ifstream file("year" + year + "sem" + sem + ".csv");
        if (!file.is_open()) {
            throw runtime_error("Could not open file for reading");
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            int key;

            key = schedule_key;

            string scheduleData;
            getline(ss, scheduleData);
            Schedule schedule = Schedule::fromCSVString(scheduleData);

            scheduleTypeMap[key].push_back(schedule);
        }

        // Ensure file stream state is checked before closing
        if (file.bad()) {
            throw runtime_error("Error occurred while reading the file");
        }

        file.close();

    }
    catch (const exception& e) {
        cerr << "An error occurred while reading the file: " << e.what() << endl;
    }

    return scheduleTypeMap;
}

void Student_user::AddSchedule()
{
    schedule_key++;
    schedule_typeMap[schedule_key];
}

void Student_user::Search(string search_text)
{
    int c_size = search_text.size();
    string course_id = search_text.substr(7, c_size);
    int cnt = 0;
    string lab_key = course_id + "_labs.csv";
    string lec_key = course_id + "_lectures.csv";
    string tut_key = course_id + "_tutorials.csv";
    if (c_size < 12)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        //printing the speciefic lessons after remove
        cout << "labs:" << endl;
        for (auto it = lesson_typeMap[lab_key].begin(); it != lesson_typeMap[lab_key].end(); ++it)
        {
            cout << *it << endl;
            cnt++;
        }
        cout << "lectures:" << endl;
        for (auto it = lesson_typeMap[lec_key].begin(); it != lesson_typeMap[lec_key].end(); ++it)
        {
            cout << *it << endl;
            cnt++;
        }
        cout << "tutorials:" << endl;
        for (auto it = lesson_typeMap[tut_key].begin(); it != lesson_typeMap[tut_key].end(); ++it)
        {
            cout << *it << endl;
            cnt++;
        }
        cout << endl;
        if (cnt == 0)
            cout << "there are no such a course" << endl << endl;
    }  
}

void Student_user::Printall(map<int, vector<Schedule>>& scheduleTypeMap)
{
    if (scheduleTypeMap.empty())
    {
        cout << "Your schedule is empty." << endl;
    }
    else
    {
        for (const auto& entry : scheduleTypeMap)
        {
            cout << "Schedule number: " << entry.first << endl;
            for (auto it = entry.second.begin(); it != entry.second.end(); ++it)
            {
                cout << *it << endl;
            }
        }
    }
    cout << endl;
}

void Student_user::PrintSchedule(string search_text, map<int, vector<Schedule>>& scheduleTypeMa)
{
    int c_size = search_text.size();
    if (c_size < 7)
    {
        cout << "you didn't enter right data..." << endl << endl;
    }
    else
    {
        for (unsigned int i = 0; i < search_text.substr(6, c_size).length(); ++i) {
            if (!isdigit(search_text.substr(6, c_size)[i])) {
                cout << "You didn't enter a digit number..." << endl << endl;
                break;
            }
            else
            {
                int scheduleId = stoi(search_text.substr(6, c_size));
                printScheduleById(scheduleId, scheduleTypeMa);
            }
        }
    }   
}

void Student_user::Add_less_sch(string& search_text, map<string, vector<Lesson_type>>& lesson_typess,
    map<int, vector<Schedule>>& scheduleTypeMa)
{
    int all_size = search_text.size();
    int num_size = search_text.size() - 13;
    bool ya_digit = true;
    // Check if the substring contains only digits
    if (search_text.length() > 4)
    {
        for (unsigned int i = 0; i < search_text.substr(4, all_size).length(); ++i) {
            if (!isdigit(search_text.substr(4, all_size)[i]) && !(search_text.substr(4, all_size)[i] == ' ')) {
                ya_digit = false;
                break;
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < search_text.substr(0, 3).length(); ++i) {
            if (!isdigit(search_text.substr(0, 3)[i])) {
                ya_digit = false;
                break;
            }
        }
    } 
    //add 1 10001 10
    if (!ya_digit) {
        cout << "You didn't enter a digit number..." << endl << endl;
    }
    else {
        if (search_text.size() < 14)
            cout << "you didn't enter the right data..." << endl;
        else
        {
            int schedule_num = stoi(search_text.substr(4, num_size));
            if (schedule_key < schedule_num) {
                cout << "you dont have " << schedule_num << " schedule" << endl << endl;
            }
            else {
                string course_id = search_text.substr(5 + num_size, 5);
                string group_num = search_text.substr(11 + num_size, all_size);
                string lab_key = course_id + "_labs.csv";
                string lec_key = course_id + "_lectures.csv";
                string tut_key = course_id + "_tutorials.csv";
                string lab_val = "lab";
                string lec_val = "lecture";
                string tut_val = "tutorial";
                AddFun(schedule_num, course_id, group_num, lab_key, lab_val, lesson_typess, scheduleTypeMa);
                AddFun(schedule_num, course_id, group_num, lec_key, lec_val, lesson_typess, scheduleTypeMa);
                AddFun(schedule_num, course_id, group_num, tut_key, tut_val, lesson_typess, scheduleTypeMa);
                cout << endl;
            }
        }        
    }
}

void Student_user::AddFun(int schedule_num, string& course_id, string& group_num, string& key,
    string& val, map<string, vector<Lesson_type>>& lesson_typess, map<int, vector<Schedule>>& scheduleTypeMa)
{
    bool exists = false;
    auto it_L = lesson_typess[key].begin();
    while (it_L != lesson_typess[key].end() && exists == false) {
        if (it_L->getGroup_number() == group_num) {
            for (auto it = scheduleTypeMa[schedule_num].begin();
                it != scheduleTypeMa[schedule_num].end(); ++it) {
                if ((it->getCourseID() == course_id) && (it->getGroup_number() == group_num)) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                cout << "This course already exists..." << endl;
            }
            else {
                Schedule schedule(course_id, val, it_L->getGroup_number(), it_L->getDay(), it_L->getBeginning_time(),
                    it_L->getDuration(), it_L->getLecturer(), it_L->getClass());
                scheduleTypeMa[schedule_num].push_back(schedule);
                ++it_L;
            }
        }
        else {
            ++it_L;
        }
    }
}

void Student_user::RemoveSchedule(string& TXT, map<int, vector<Schedule>>& scheduleTypeMa)
{
    int all_size = TXT.size();
    int num_size = TXT.size() - 13;
    bool ya_digit = true;
    // Check if the substring contains only digits
    if (all_size < 11)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        for (unsigned int i = 0; i < TXT.substr(11, num_size).length(); ++i) {
            if (!isdigit(TXT.substr(11, num_size)[i])) {
                ya_digit = false;
                break;
            }
        }
        if (!ya_digit) {
            cout << "You didn't enter a digit number..." << endl << endl;
        }
        else {
            if (scheduleTypeMa.empty())
            {
                cout << "Your schedule is empty." << endl;
            }
            else
            {
                if (schedule_key < stoi(TXT.substr(11, all_size)) || schedule_key <= 0)
                {
                    cout << "you dont have " << stoi(TXT.substr(11, all_size)) << " schedule" << endl;
                }
                else
                {
                    scheduleTypeMa.erase(stoi(TXT.substr(11, all_size)));
                    map<int, vector<Schedule>> tempMap;
                    int newKey = 1;
                    for (const auto& entry : scheduleTypeMa)
                    {
                        tempMap[newKey++] = entry.second;
                    }

                    // Replace old map with newly ordered map
                    scheduleTypeMa.swap(tempMap);
                }
            }
        }
    }    
}

void Student_user::RemoveLesson(string& TXT, map<int, vector<Schedule>>& scheduleTypeMa)
{
    int c_size = TXT.size();
    int s_size = TXT.size() - 12;
    bool ya_digit = true;
    if (c_size < 13)
        cout << "you didn't enter right data..." << endl << endl;
    else
    {
        // Check if the substring contains only digits
        for (unsigned int i = 0; i < TXT.substr(3, s_size).length(); ++i) {
            if (!isdigit(TXT.substr(3, s_size)[i])) {
                ya_digit = false;
                break;
            }
        }
        if (!ya_digit) {
            cout << "You didn't enter a digit number..." << endl << endl;
        }
        else {
            int sch_num = stoi(TXT.substr(3, s_size));
            string course_id = TXT.substr(4 + s_size, 5);
            string group_num = TXT.substr(10 + s_size, c_size);
            if (scheduleTypeMa.empty())
            {
                cout << "Your schedule is empty." << endl;
            }
            else
            {
                if (schedule_key < sch_num || schedule_key <= 0)
                {
                    cout << "you dont have " << sch_num << " schedule" << endl;
                }
                else
                {
                    auto it_lab = scheduleTypeMa[sch_num].begin();
                    while (it_lab != scheduleTypeMa[sch_num].end()) {
                        if (it_lab->getGroup_number() == group_num && it_lab->getCourseID() == course_id) {
                            it_lab = scheduleTypeMa[sch_num].erase(it_lab);
                        }
                        else
                        {
                            ++it_lab;
                        }
                    }
                }
            }
        }
    }
}
