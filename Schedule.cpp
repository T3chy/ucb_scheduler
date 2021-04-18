#include "Schedule.h"

unordered_map<string, float> letter_grade_to_gpa = {\
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


float Schedule::parse_grade_input(string input) {
		if (letter_grade_to_gpa.find(input) != letter_grade_to_gpa.end())
			return letter_grade_to_gpa[input];
		else
			throw "Invalid letter grade!";
}
void Schedule::calculate_sem_gpa(int idx){
		float total_units = 0;
		float running_gpa_points = 0;
		for (Course & c : m_sem_list[idx].taking ) {
			total_units += c.units;
			running_gpa_points += c.grade * c.units;
		}
		m_sem_list[idx].sem_gpa = running_gpa_points / total_units;
	}
void Schedule::recalculate_overall_gpa(){
	float total_units = 0;
	float running_gpa_points = 0;
	cout << "sem list length " << m_sem_list.size() << endl;
	for (Semester & s : m_sem_list){
		cout << "looping recalcualtion" << endl;
		if ( s.taking.size() != 0 ) {
			for (Course & c : s.taking ) {
				total_units += c.units;
				running_gpa_points += c.grade * c.units;
			}
		}
	}
	cout << "running gpa points " << running_gpa_points << endl;
	cout << "total units" << total_units << endl;
	gpa = running_gpa_points / total_units;
}
float Schedule::getGpa() {
	return gpa;
}
void Schedule::enter_final_grades(int idx){
	for (int i=0; i < m_sem_list[idx].taking.size(); i++ ) {
		string grade = "";
		cout << "Please enter your grade for " << m_sem_list[idx].taking[i].toString() <<  ":";
		cin >> grade;
		grade[0] = toupper(grade[0]); // in case they enter a lowercase letter grade like a cringe normie
		if (letter_grade_to_gpa.find(grade) != letter_grade_to_gpa.end())
			m_sem_list[idx].taking[i].grade = letter_grade_to_gpa[grade];
		else {
			cout << "\"" << grade << "\" is not a valid grade :( please try again " << endl;
			i--;
		}
	}
}

vector<Course> Schedule::enter_sem_courses(int idx) {
	cout << "Choosing classes for semester " << idx << endl;
	vector<Course> courses = {};
	while (true) {
		string selection = "";
		cout << "enter the course ID of the course you'd like to add (e.g cs61a):";
		cin >> selection;
		if (catalog[selection].units != 0) { // null check
			if (can_take(catalog[selection], idx)) { // TODO write try catch here lol
				courses.push_back(catalog[selection]);
				cout << "added! " << endl;
			} else {
				cout << "looks like you don't have the prereqs for that one :(" << endl;
			}
		} else {
			cout << "looks like that's not a valid course ID :(" << endl;
		}
		cout << "Enter another one? [Y/n] ";
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
		throw "you've tried to reassign a semester that doesn't exist! Please use the no-argument method to add a new semester";
	else {
		m_sem_list[idx].taking = enter_sem_courses(idx);
		m_sem_list[idx].sem_units = 0;
		for (Course c : m_sem_list[idx].taking )
			m_sem_list[idx].sem_units += c.units;
	}
}
void Schedule::add_sem(){
	m_sem_list.push_back(Semester(enter_sem_courses(m_sem_list.size())));
}

void Schedule::finish_sem(){
	finish_sem(sem_idx);

}
void Schedule::finish_sem(int idx){
	enter_final_grades(idx);
	calculate_sem_gpa(idx);
	recalculate_overall_gpa();
	cout << "your GPA this semester was: "  << m_sem_list[sem_idx].sem_gpa << endl;
	cout << "your overall GPA is now: "  << gpa << endl;
	cout << "I'm proud of you :)" << endl;
	cout << "On to the next!" << endl;
	m_sem_list[sem_idx].complete = true;
	sem_idx++;

}
bool Schedule::can_take (Course c){
	return can_take(c, sem_idx);
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
float Schedule::get_upper_div_credits(course_prefix tmp) {
	float upper_div_units = 0;
	for (int i=0; i < m_sem_list.size(); i++ )
		for (Course c : m_sem_list[i].taking )
			if (c.prefix == tmp && c.isUpperDivision())
				upper_div_units += c.units;
	return upper_div_units;
}
Course::Course(course_prefix p, int c_n, char const * mod, float u, char const * m_n, vector<Course> prq = {}) {
	prefix = p;
	course_number = c_n;
	modifier = mod;
	units = u;
	m_notes = m_n;
	nocourse = false;
	prereqs = prq;
};
bool Schedule::req_fulfilled(req r){
	vector<Course> taken = {};
	int credits = 0;
	if (r.requirement_type != any || r.requirement_type == any_upper_div ) {
		for (int i=0; i < m_sem_list.size(); i++)
			for (int j=0; j < m_sem_list[j].taking.size(); j++)
				for (int k=0; k < r.courses.size(); k++)
					if (m_sem_list[i].taking[j] == r.courses[k])
						taken.push_back(r.courses[k]);
	} else {
		if (r.requirement_type == any || r.requirement_type == any_upper_div) {
			for (int i=0; i < m_sem_list.size(); i++)
				for (int j=0; j < m_sem_list[j].taking.size(); j++)
					if (( r.requirement_type == any || m_sem_list[i].taking[j].isUpperDivision()) && m_sem_list[i].taking[j].prefix == r.prefix) // ugly lmfao
						credits += m_sem_list[j].taking[j].units;
			return (credits >= r.n);
		}
	}
	switch(r.requirement_type){
		case(both):
			return (r.courses == taken);
		case(either):
			return (r.courses.size() >= r.n);
		default:
			return false;
	}
}
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
