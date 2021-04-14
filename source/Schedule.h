/** @file main.cpp
 * da main program
 */
// The previous block is needed in every file for which you want to generate documentation

/* #include <fmt/format.h> */

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
#include<vector>

using namespace std;

enum course_prefix {cs, philo};
class Course {
	public:
		bool nocourse;
		float grade; // in gpa points version
		course_prefix prefix;
		int course_number;
		string modifier;
		float units;
		string m_notes;
		vector<Course> prereqs;
		bool isUpperDivision(){return (course_number >= 100);}
		Course(){nocourse = true;}
Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n);
		Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n, vector<Course> prq);
		bool operator ==(const Course compare_to){
			return (prefix == compare_to.prefix && course_number == compare_to.course_number && modifier== compare_to.modifier);
		}
		string toString();
};

class Semester {
	public:
	float sem_units;
	bool complete;
	float sem_gpa;
	vector<Course> taking ; // impossible to take more than 5 courses per sem at berk unless you bend the rules
	Semester(){
		sem_units = 0;
		complete = false;
		sem_gpa = 0;
	}
	Semester(vector<Course> t){
		sem_units = 0;
		complete = false;
		sem_gpa = 0;
		taking = t;
	}
	string toString(){
		string tmp = "";
		for (int i=0; i < taking.size(); i++)
			tmp += taking[i].toString() + "\n";

		return tmp;
	}
	int add_course(Course c){ // TODO check previous semesters / warn if retaking and previously passed
		for (int i=0; i < taking.size(); i++)
			if (taking[i] == c)
				return -1;
		taking.push_back(c);
		return 0;
	}




};

class Schedule { // for some reason default constructor ( or something else? ) sets sem_idx to 1 fix that

	private:
		int sem_idx;
		float gpa;
		void enter_final_grades();
		vector<Semester> m_sem_list;
		static float parse_grade_input(string input);
		void calculate_sem_gpa();
		void recalculate_overall_gpa();
	public:
		bool can_take(Course c);
		bool can_take(Course c, int sem_ifx);
		float getGpa();
		void add_sem(Semester s);
		void add_sem(); // current idx
		void add_sem(Semester s, int idx); // future sem
		void finish_sem();
};
#endif
