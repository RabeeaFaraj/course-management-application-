#ifndef _ADMIN_USER_H_
#define _ADMIN_USER_H_
#include <iostream>
#include <string>
#include "General_system.h"
#include "Schedule.h"

using namespace std;

class Admin_user : public General_System {
private:

public:
	Admin_user();
	~Admin_user();
	void AddCourse(map<string, Course>& courses, string course_id, string course_name, string head_lecturer, string points);
	void RmCourseId(map<string, Course>& courses, string& course_id);
	void AddStudent(map<string, Student>& students, string student_id, string student_name, string password);
	void AddLecturer(map<string, Teacher>& teachers, string lectuer_id, string lecturer_name);
	void RmStudentId(map<string, Student>& students, string& student_id);
	void RmLecturerId(map<string, Teacher>& teachers, string& lecturer_id);
	void Search(string search_text);
	void AddLesson(map<string, vector<Lesson_type>>& lessons, string lesson_key, string group_number, string day, string beginning_time, string duration, string lecturer, string Class);
	void RmLesson(map<string, vector<Lesson_type>>& lessons, string id_gnum);
	void AddLessonFun();

};
#endif
