#include "Schedule.h"

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


/* Schedule::Schedule(){ */
/* 	sem_idx = 0; */
/* } */
float Schedule::parse_grade_input(string input) {
		if (letter_grade_to_gpa.find(input) != letter_grade_to_gpa.end())
			return letter_grade_to_gpa[input];
		else
			throw "Invalid letter grade!";
}
void Schedule::calculate_sem_gpa(){
		float total_units = 0;
		float running_gpa_points = 0;
		for (Course & c : m_sem_list[sem_idx].taking ) {
			total_units += c.units;
			running_gpa_points += c.grade * c.units;
		}
		m_sem_list[sem_idx].sem_gpa = running_gpa_points / total_units;
	}
void Schedule::recalculate_overall_gpa(){
	float total_units = 0;
	float running_gpa_points = 0;
	for (Semester & s : m_sem_list){
		if ( s.sem_units != 0 ) {
			for (Course & c : s.taking ) {
				total_units += c.units;
				running_gpa_points += c.grade * c.units;
			}
		}
	}
	gpa = running_gpa_points / total_units;
}
float Schedule::getGpa() {
	return gpa;
}
void Schedule::enter_final_grades(){
	throw "not implemented!";
}

void Schedule::add_sem(Semester s, int idx){
	m_sem_list[idx] = s;
}

void Schedule::finish_sem(){
	enter_final_grades();
	calculate_sem_gpa();
	recalculate_overall_gpa();
	cout << "your GPA this semester was: "  << m_sem_list[sem_idx].sem_gpa << endl;
	cout << "your overall GPA is now: "  << gpa << endl;
	cout << "I'm proud of you :)" << endl;
	cout << "On to the next!" << endl;
	m_sem_list[sem_idx].complete = true;
	sem_idx++;

}
