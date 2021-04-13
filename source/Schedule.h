/** @file main.cpp
 * da main program
 */
// The previous block is needed in every file for which you want to generate documentation

#include <fmt/format.h>

// This should be in the headers

/**
 * @brief main loop, text-based interaction
 * @return nada
 */
#ifndef Schedule_H
#define Schedule_H
#define N_SEMESTERS 8
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

enum course_prefix {cs, philo};
struct Course {
	course_prefix prefix;
	int course_number;
	bool div;
	float units;
	float grade; // in gpa points version
	string m_notes;
	Course * prereqs[5]; //damn you, ISO C++!!
	string toString(){
	string tmp = "";

	   switch(prefix) {
	      case cs:
		 tmp = "cs";
	      case philo:
		 tmp = "philo";
	      default:
		 throw "Invalid course prefix";
	   }

		return tmp + to_string(course_number);
	}
};
struct Semester {
	float sem_units;
	bool complete;
	float sem_gpa;
	Course taking[5]; // impossible to take more than 5 courses per sem at berk unless you bend the rules
};

unordered_map<string, int> letter_grade_to_gpa = {\
	{"A+",	4},\
	{"A",4},\
	{"A-",	3.7},\
	{"B+",	3.3},\
	{"B",3},\
	{"B-",	2.7},\
	{"C+",	2.3},\
	{"C",2},\
	{"C-",	1.7},\
	{"D+",	1.3},\
	{"D",1},\
	{"D-",	0.7},\
	{"F",0},\
};

class Schedule {

	private:
		int sem_idx;
		float gpa;
		void enter_final_grades();
		Semester m_sem_list[N_SEMESTERS];
		static float parse_grade_input(string input);
		void calculate_sem_gpa();
		void recalculate_overall_gpa();
	public:
		Schedule();
		float getGpa();
		void add_sem(Semester s, int idx);
		void finish_sem();
};
#endif
