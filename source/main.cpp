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
#include "Schedule.cpp"
using namespace std;





int main(int argc, char* argv[])
{
	Schedule s;
    if (argc)
    {
        fmt::print("hello world from {}!", argv[0]);
    }
    return 0;
}
