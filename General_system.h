#ifndef _GENERAL_SYSTEM_H_
#define _GENERAL_SYSTEM_H_
#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include "Teachers.h" 
#include "Course.h"
#include "Lesson_type.h"
#include "Schedule.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>


using namespace std;


class General_System {
protected:
	map<string, vector<Lesson_type>> lesson_typeMap;
	map<string, Student> studentsMap;
	map<string, Teacher> teachersMap;
	map<string, Course> coursesMap;
	map<int, vector<Schedule>> schedule_typeMap;
	static int schedule_key;
	General_System* student_user;
	General_System* admin_user;

public:
	General_System();
	General_System(const General_System& other);
	virtual ~General_System();
	void Generator(void);
	void loadStudents(const string& filename, map<string, Student>& students); //loading the data of students.csv file to map
	void loadTeachers(const string& filename, map<string, Teacher>& teachers); //loading the data of Teachers.csv file to map
	void loadCourses(const string& filename, map<string, Course>& courses); //loading the data of Courses.csv file to map
	void loadlesson_type(const string& filename, map<string, vector<Lesson_type>>& lesson_types); //loading the data of xxxxx_labs/lectures/tutorials.csv files to map that the value is vector
	void saveStudents(const string& filename, const map<string, Student>& students);
	void saveTeachers(const string& filename, const map<string, Teacher>& teachers);
	void saveCourses(const string& filename, const map<string, Course>& courses);
	void saveLessonTypes(const string& filename, const map<string, vector<Lesson_type>>& lesson_types);
	template <class T>
	void printMap(const map<string, T>& map); //print the map that the value is template of classes
	void PrintCourses(map<string, Course>& courses);
	void PrintCourseId(map<string, Course>& courses, string& course_id);
	template<class T>
	bool Valid_id(string id, map<string, T>& map, int len);
	void funSchedule(string id);
	virtual void Search(string search_text) {};
};
#endif
