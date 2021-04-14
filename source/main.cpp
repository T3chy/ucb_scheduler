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
	cout << s.getGpa() << endl;
	cout << cs61a.isUpperDivision() << endl;
	cout << cs162.isUpperDivision() << endl;
	cout << s1.toString().c_str();

	s.add_sem(s1);
    return 0;
}
