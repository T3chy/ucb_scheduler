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
#define N_SEMESTERS 8
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;


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


enum course_prefix {cs, philo};
string course_prefix_to_string(course_prefix prefix) {
   switch(prefix) {
      case cs:
         return "cs";
      case philo:
         return "philo";
      default:
         return "Invalid course prefix";
   }
}
struct Course {
		course_prefix prefix;
		int course_number;
		bool div;
		float units;
		float grade; // in gpa points version
		string m_notes;
		Course * prereqs[];
		string toString(){
			return course_prefix_to_string(prefix) + to_string(course_number);
		}
};
struct Semester {
	float sem_units;
	bool complete;
	float sem_gpa;
	Course taking[5]; // impossible to take more than 5 courses per sem at berk unless you bend the rules
};
class Schedule {
	private:
		int sem_idx;
		float gpa;
		Semester m_sem_list[N_SEMESTERS];
	void enter_final_grades(){
		string tmp = "";
		for ( Course & c : m_sem_list[sem_idx].taking ) {
			if ( c.course_number != 0 ) {
				tmp = "";
				cout << "Enter your grade for: " << c.toString();
				cin >> tmp;
				c.grade = parse_grade_input(tmp);
			}
		}
	}

	static float parse_grade_input(string input) {
		if (letter_grade_to_gpa.find(input) != letter_grade_to_gpa.end())
			return letter_grade_to_gpa[input];
		else
			throw "Invalid letter grade!";
	}
	void calculate_sem_gpa(){
		float total_units = 0;
		float running_gpa_points = 0;
		for (Course & c : m_sem_list[sem_idx].taking ) {
			total_units += c.units;
			running_gpa_points += c.grade * c.units;
		}
		m_sem_list[sem_idx].sem_gpa = running_gpa_points / total_units;
	}
	void recalculate_overall_gpa(){
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
	public:
		float getGpa() {
			return gpa;
		}
		void add_sem(Semester s, int idx){
			m_sem_list[idx] = s;
		}

		void finish_sem(){
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
};

int main(int argc, char* argv[])
{
    if (argc)
    {
        fmt::print("hello world from {}!", argv[0]);
    }
    return 0;
}
