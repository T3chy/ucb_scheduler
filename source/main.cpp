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
	s.catalog = catalog;
	s.add_sem();
	s.finish_sem();
	s.add_sem();
	s.finish_sem();


    return 0;
}
