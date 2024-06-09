#ifndef _STUDENT_USER_H_
#define _STUDENT_USER_H_
#include <iostream>
#include <string>
#include "General_system.h"
#include "Schedule.h"

using namespace std;

class Student_user : public General_System {
private:

public:
	Student_user();
	//Student_user(const Lesson_type& other);
	~Student_user();
	void printScheduleById(int scheduleId, map<int, vector<Schedule>>& scheduleTypeMa);
	map<int, vector<Schedule>> readCSV(const string& filename); // Declare the readCSV function
	void writeCSV(const map<int, vector<Schedule>>& scheduleTypeMap, const string& filename); // Declare the writeCSV function
	void deleteAllSchedules(map<int, vector<Schedule>>& scheduleTypeMap);
	void checkForOverlapsInLessons(const map<string, vector<Lesson_type>>& lesson_types);
	map<int, vector<Schedule>> getReadySchedule(const string& choice);
	void AddSchedule();
	void Search(string search_text);
	void Printall(map<int, vector<Schedule>>& scheduleTypeMap);
	void PrintSchedule(string search_text, map<int, vector<Schedule>>& scheduleTypeMa);
	void Add_less_sch(string& search_text, map<string, vector<Lesson_type>>& lesson_typess, map<int, vector<Schedule>>& scheduleTypeMa);
	void AddFun(int schedule_num, string& course_id, string& group_num, string& key,
		string& val, map<string, vector<Lesson_type>>& lesson_typess, map<int, vector<Schedule>>& scheduleTypeMa);
	void RemoveSchedule(string& TXT, map<int, vector<Schedule>>& scheduleTypeMa);
	void RemoveLesson(string& TXT, map<int, vector<Schedule>>& scheduleTypeMa);
};
#endif
