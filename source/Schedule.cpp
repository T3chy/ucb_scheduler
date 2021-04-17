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
	m_sem_list[sem_idx].sem_gpa = 4.1;
}

vector<Course> Schedule::enter_sem_courses(int idx) {
	cout << "Choosing classes for semester " << idx << endl;
	vector<Course> courses = {};
	while (true) {
		string selection = "";
		cout << "enter the course ID of the course you'd like to add (e.g cs61a):";
		cin >> selection;
		if (can_take(catalog[selection], idx)) { // TODO write try catch here lol
			courses.push_back(catalog[selection]);
			cout << "added! " << endl;
		} else {
			cout << "looks like you don't have the prereqs for that one :(" << endl;
		}
		cout << "Enter another one? [Y/n]" << endl;
		string tmp = "";
		cin >> tmp;
		if (tmp == "N" || tmp == "n")
			break;
	}
	cout << "This semester's courses are: " << endl;
	for (Course c : courses)
		cout << c.toString() << endl;
	return courses;


}
void Schedule::add_sem(int idx){
	if (idx > m_sem_list.size() - 1)
		throw "you've tried to reassign a semester that doesn't exist! Please use the single-argument constructor to add a new semester";
	else

		m_sem_list[idx] = enter_sem_courses(idx);
}
void Schedule::add_sem(){
	m_sem_list.push_back(enter_sem_courses(m_sem_list.size()));
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
bool Schedule::can_take (Course c){
	vector<Course> taken = {};
	for (int i=0; i < c.prereqs.size(); i ++)
		for (int j=0; j < sem_idx -1; j++ )
			for ( int k=0; k < m_sem_list[j].taking.size(); k++)
				if ( c.prereqs[i] == m_sem_list[j].taking[k] )
					taken.push_back(c.prereqs[i]);
	return taken.size() == c.prereqs.size();
}
bool Schedule::can_take (Course c, int sem_idx){
	vector<Course> taken = {};
	for (int i=0; i < c.prereqs.size(); i ++)
		for (int j=0; j <= sem_idx -1; j++ )
			for ( int k=0; k < m_sem_list[j].taking.size(); k++)
				if ( c.prereqs[i] == m_sem_list[j].taking[k] )
					taken.push_back(c.prereqs[i]);
	return taken.size() == c.prereqs.size();
}
Course::Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n) {

	prefix = p;
	course_number = c_n;
	modifier = mod;
	units = u;
	nocourse = false;
	m_notes = m_n;
};
Course::Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n, vector<Course> prq) {
	prefix = p;
	course_number = c_n;
	modifier = mod;
	units = u;
	m_notes = m_n;
	nocourse = false;
	prereqs = prq;
};
string Course::toString(){
   string tmp = "";
   switch(prefix) {
      case cs:
	 tmp = "cs";
	 break;
      case philo:
	 tmp = "philo";
	 break;
      default:
	 throw "Invalid course prefix";
   }
	return tmp + to_string(course_number) + modifier + ", " + to_string(units) + " units ";
}
