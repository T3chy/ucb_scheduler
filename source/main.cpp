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
#include "cs.cpp"
using namespace std;





int main(int argc, char* argv[])
{

	Schedule s;

	unordered_map<const char *, Course> c = init_cs();
	Semester s1 = Semester({c["cs61b"]});
	s.add_sem(s1);
	s.finish_sem();
	Semester s2 = Semester({c["cs61a"]});
	cout << s.can_take(c["cs162"]) << endl;
	s.add_sem(s2);


    return 0;
}
