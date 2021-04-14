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
struct Course {
		bool nocourse;
		float grade; // in gpa points version
		course_prefix prefix;
		int course_number;
		string modifier;
		float units;
		string m_notes;
		vector<Course> prereqs;
		bool isUpperDivision(){
			return (course_number >= 100);
		}
		Course(){
			nocourse = true;
		}

		Course(course_prefix p, int c_n, const char * mod, float u, const char * m_n) {
			prefix = p;
			course_number = c_n;
			modifier = mod;
			units = u;
			nocourse = false;
			m_notes = m_n;
		}
		Course(course_prefix p, int c_n, const char * mod, float u, const char * m_n, vector<Course> prq) {
			prefix = p;
			course_number = c_n;
			modifier = mod;
			units = u;
			m_notes = m_n;
			nocourse = false;
		}
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

			cout << tmp + to_string(course_number) + modifier;
			return tmp + to_string(course_number) + modifier;
		}
};
struct Semester {
	float sem_units;
	bool complete;
	float sem_gpa;
	Course taking[5]; // impossible to take more than 5 courses per sem at berk unless you bend the rules
	Semester(){
		sem_units = 0;
		complete = false;
		sem_gpa = 0;
		for (int i=0; i > 5; i++) //ugly
			taking[i] = Course();
	}


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
	/* Schedule(); */
		float getGpa();
		void add_sem(Semester s, int idx);
		void finish_sem();
};
#endif
