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
#define N_SEMESTERS 8
#include <unordered_map>
#include <iostream>
#include <string>
#include "Schedule.h"
#include "csv.cpp"
using namespace std;





int main(int argc, char* argv[])
{

	Schedule s;

	unordered_map<string, Course> catalog = init_course_list("cs.csv");
	unordered_map<course_prefix, vector<req>> reqs = init_requirements(catalog);
	s.reqs = reqs;
	s.majors = {cs};
	s.catalog = catalog;
	while (true){
		string selection = "";
		cout << "[Add] a Semester, view [Summary], [Finish] the current semester, or [Exit]" << endl;
		cout << "Make A selection:";
		cin >> selection; // lowercase this maybe
	if (selection == "Add")
		s.add_sem();
	else if (selection == "Summary")
		s.summary();
	else if (selection == "Finish")
		s.finish_sem();
	else if (selection == "Exit")
		break;
	else
		cout << "\"" << selection << "\" is not a valid command :( this is case sensitive because I (Elam) suck " << endl;
	}
    return 0;
}
