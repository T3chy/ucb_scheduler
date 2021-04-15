/* #include "Schedule.h" */


// init all cs classes, this could probably be hashmapped or smth too
// read course catalog from a csv file


/* int init_course_list(const char * filename) { */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // std::stringstream


#define MAXW 128


int main (int argc, char **argv) {

	std::string prefix;
    int course_number = 0;
    std::string modifier;
    float units = 0 ;
    std::string name;
    std::vector<std::string> prereqs;

    char comma;

    std::fstream f (argv[1]);
    if (!f.is_open()) {
        std::cerr << "error: file open failed " << argv[1] << ".\n";
        return 1;
    }
        // Helper vars
    std::string line, colname;
    std::string val;
        std::vector<std::pair<std::string, std::vector<std::string>>> result;

        if(f.good())
    {
        // Extract the first line in the file
        std::getline(f, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<std::string> {}});
        }
    }

    // Read data, line by line
    while(std::getline(f, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
	std::vector<std::string> row = {};
        while(ss >> val){
            // Add the current integer to the 'colIdx' column's values vector

            result.at(colIdx).second.push_back(val);
		row.push_back(val);
		std::cout << colIdx << val << std::endl;

            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    f.close();
}
    /* for (;;) {          /1* loop continually *1/ */
    /*     f << prefix << comma << course_number << comma << units << comma << name << comma; */
	/* std::cout << prefix << comma << course_number << comma << units << comma << name << comma << std::endl; */
    /*     if (f.fail() || f.eof()) */
    /*         break; */
    /*     f.ignore (MAXW, '\n'); */
    /* } */
    /* f.close(); */
/* } */
