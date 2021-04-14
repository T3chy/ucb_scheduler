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
#include "cs.h"
using namespace std;





int main(int argc, char* argv[])
{

	Schedule s;
	cout << csa["cs61a"].isUpperDivision() << endl;
	Semester s1 = Semester({csa["cs61a"]});
	cout << s1.add_course(csa["cs61a"]) << endl;
	s.add_sem(s1);
	s.finish_sem();


    return 0;
}
