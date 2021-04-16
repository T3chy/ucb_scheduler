#include "Schedule.h"
#include "Schedule.cpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // std::stringstream
#include <unordered_map>
#include<string.h>
// TODO make it not require a blanked column idk why it does that

using namespace std;
course_prefix string_to_course_prefix(string s) {
	const char * tmp = s.c_str();
	if (strcmp(tmp, "cs")) {
		return cs;
	} else if (strcmp(tmp, "philo")) {
		return philo;
	} else{
		throw "invalid prefix!";
	}
	cout << "bruh 2 " << endl;
}
unordered_map<string, Course>  init_course_list(const char * filename){ // maybe just put this on the heap (how? dynamic size? sizeof(course) * num lines?) and return pointer
	unordered_map <string, Course> catalog = {};

	// File pointer
	fstream fin;

	// Open an existing file
	fin.open(filename, ios::in);

	// Read the Data from the file
	// as String Vector
	vector<string> row;
	string line, word, temp;

	while (fin >> temp) {

		row.clear();

		// read an entire row and
		// store it in a string variable 'line'
		getline(fin, line);

		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in the respetive tmp variable
		int colIdx = 0;
		std::string prefix;
		int course_number = 0;
		std::string modifier = "";
		float units = 0 ;
		std::string name = "";
		std::vector<string> prereqs;
		while (getline(s, word, ',')) {
			cout << word << endl;
			switch (colIdx++) {
				case (0):
					/* cout << "PREFIX " << word << endl; */
					prefix = word;
					break;
				case (1):
					/* cout << "course number " << word << endl; */
					course_number = stoi(word);
					break;
				case(2):
					/* cout << "modifier " << word << endl; */
					modifier = word;
					break;
				case(3):
					/* cout << "units " << word << endl; */
					units = stoi(word);
					break;
				case(4):
					/* cout << "name " << word << endl; */
					name =  word.c_str();
					break;
				default:
					prereqs.push_back(word);
					/* cout << "prereq " << word << endl; */
			}
		}
		// may need to re-init to accomodate for prerequisites that haven't be inited yet
		vector<Course> prqs = {};
		for (int i=0; i < prereqs.size(); i++)
			prqs.push_back(catalog[prereqs[i]]);

		cout << prefix + to_string(course_number) + modifier << endl;
		catalog[prefix + to_string(course_number) + modifier]  = Course(string_to_course_prefix(prefix), course_number, modifier.c_str(), units, name.c_str(), prqs);



	}
	return catalog;
}


int main(){
	unordered_map<string, Course> b = init_course_list("cs.csv");
	cout << b["cs61a"].isUpperDivision();
	return 0;
}
