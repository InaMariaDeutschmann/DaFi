#include "output_help_message.hpp"

#include <iostream>

// Get help message
void get_help_message( std::string s ){
    std::cout <<  "\n##############################################################################################################################################################\n" << std::endl;
    std::cout <<  "Usage: " << s << " --input_file [path/filename] <option(s)>\n" << std::endl;
    std::cout <<  "Options:" << std::endl;
    // Help
    // used alphabetical letters: dfhmotv
    // available alphabetical letters: abcegijklnpqrsuwxyz
    std::cout <<  "\t-h,--help.....................................Returns this help message\n" << std::endl;
    std::cout <<  "\t-v,--version..................................Returns version of the program.\n" << std::endl;
    std::cout <<  "\t-d,--defaults.................................Returns default values of the program.\n" << std::endl;
    // Required options
    std::cout <<  "\nRequired options:" << std::endl;
    std::cout <<  "\t-f,--input_file [filename]....................Name of the input file (first line are the column names, first row rownames).\n" << std::endl;
    // Thresholds input
    std::cout <<  "\nSettings:" << std::endl;
    std::cout <<  "\t--threshold_min_rowsum [num]......................Default: 0. \"num\" is threshold to filter by row sum.\n" << std::endl;
    std::cout <<  "\t--threshold_max_rowsum [num]......................Default: inf. \"num\" is threshold to filter by row sum.\n" << std::endl;
    std::cout <<  "\t--threshold_min_presence [num]....................Default: 0. \"num\" is threshold to filter by presence (in percent).\n" << std::endl;
    std::cout <<  "\t--threshold_max_presence [num]....................Default: 100. \"num\" is threshold to filter by presence (in percent).\n" << std::endl;
    // Inputfile separators
    std::cout <<  "\t--separator_file \"[sep]\"......................Default: tab, other possibilities, but not limited to: \";\" or \" \"\n" << std::endl;
    // Outputfiles
    std::cout <<  "\nOutput:" << std::endl;
    std::cout <<  "\t-o,--output_file_filtered [filename]..........Default: \"filtered_data.txt\"; name of the output network file.\n" << std::endl;
    std::cout <<  "\t--no_output_file_filtered.....................Default: output filtered data file. With this flag results in not printing the filtered file.\n" << std::endl;
    std::cout <<  "\t--output_file_rowsums_presence [filename].....Create output with rowsums and presence for each row.\n" << std::endl;
    std::cout <<  "\t--output_file_colsums [filename]..............Create output with colsums for each column.\n" << std::endl;
    std::cout <<  "\n##############################################################################################################################################################\n" << std::endl;
};

// Get default values
void get_defaults(){
    std::cout <<  "\n########################################################################\n" << std::endl;
    std::cout <<  "\nDefault settings" << std::endl;
    std::cout <<  "\t- threshold_min_rowsum = 0." << std::endl;
    std::cout <<  "\t- threshold_max_rowsum = inf." << std::endl;
    std::cout <<  "\t- threshold_min_presence = 0%." << std::endl;
    std::cout <<  "\t- threshold_max_presence = 100%." << std::endl;
    std::cout <<  "\t- Inputfile separator is by default tabs." << std::endl;
    std::cout <<  "\t- Output: by default the only output is the filtered file." << std::endl;
    std::cout <<  "\n########################################################################\n" << std::endl;
};
