#include "log.hpp"
#include <vector>                     // vector
#include <boost/algorithm/string.hpp> // split
#include <fstream>                    // read in and out files

Log::Log(){
    // Parameters
    indicator_output_rowsums_presence = 0;                     // Indicator to create extra output
    indicator_output_colsums = 0;                              // Indicator to create extra output
    indicator_output_file_filter = 1;                          // Indicator to create filtered file output
    threshold_min_rowsum = 0;                                  // Threshold for min_rowsum
    threshold_max_rowsum = 1.0/0.0;                            // Threshold for max_rowsum (inf)
    threshold_min_presence = 0;                                // Threshold for min_presence within row
    threshold_max_presence = 100;                              // Threshold for max_presence within row (because all values will be 0-100%)
    
    // Filenames
    filename_input = "";                                       // Filename/path of input
    filename_output_filtered_data = "filtered_data.txt";       // Filename/path of output
    filename_output_rowsums_presence = "rowsums_presence.txt"; // Filename of extra output
    filename_output_colsums = "colsums.txt";                   // Filename of extra output
    filename_output_logfile = "log.txt";                       // filename/path of logfile
    
    // Separators of input files
    sep = "\t";                                                // Separator for input file
};

// Set info
void Log::set_filename_input( std::string s ){
    filename_input = s;
};
void Log::set_filename_output_filtered_data( std::string s ){
    filename_output_filtered_data = s;
};
void Log::set_filename_output_rowsums_presence( std::string s ){
    filename_output_rowsums_presence = s;
};
void Log::set_filename_output_colsums( std::string s ){
    filename_output_colsums = s;
};
void Log::set_filename_output_logfile( std::string s ){
    filename_output_logfile = "log_";
    filename_output_logfile += s;
    filename_output_logfile += ".txt";
};
void Log::set_sep( std::string s ){
    sep = s;
};
void Log::set_threshold_min_rowsum( std::string s ){
    threshold_min_rowsum = std::stod( s );
};
void Log::set_threshold_max_rowsum( std::string s ){
    threshold_max_rowsum = std::stod( s );
};
void Log::set_threshold_min_presence( std::string s ){
    threshold_min_presence = std::stod( s );
};
void Log::set_threshold_max_presence( std::string s ){
    threshold_max_presence = std::stod( s );
};
void Log::set_indicator_output_rowsums_presence(){
    indicator_output_rowsums_presence = 1;
};
void Log::set_indicator_output_colsums(){
    indicator_output_colsums = 1;
};
void Log::set_indicator_output_file_filter(){
    indicator_output_file_filter = 0;
};

// Get info
int Log::get_indicator_output_rowsums_presence(){
    return indicator_output_rowsums_presence;
};
int Log::get_indicator_output_colsums(){
    return indicator_output_colsums;
};
int Log::get_indicator_output_file_filter(){
    return indicator_output_file_filter;
};
double Log::get_threshold_min_rowsum(){
    return threshold_min_rowsum;
};
double Log::get_threshold_max_rowsum(){
    return threshold_max_rowsum;
};
double Log::get_threshold_max_presence(){
    return threshold_max_presence;
};
double Log::get_threshold_min_presence(){
    return threshold_min_presence;
};
std::string Log::get_filename_input(){
    return filename_input;
};
std::string Log::get_filename_output_filtered_data(){
    return filename_output_filtered_data;
};
std::string Log::get_filename_output_rowsums_presence(){
    return filename_output_rowsums_presence;
};
std::string Log::get_filename_output_colsums(){
    return filename_output_colsums;
};
std::string Log::get_filename_output_logfile(){
    return filename_output_logfile;
};
std::string Log::get_sep(){
    return sep;
};

// Check input files
std::string Log::check_input_files(){
    std::string error_message = "";

    std::ifstream IN( filename_input );
    if( !IN.good() )
    {
        error_message += "\n";
        error_message += filename_input;
        error_message += " could not be opened.\n";
    }
    else
    {
        std::string l;
        // Read in header (1st line)
        if( getline( IN, l ).good() )
        {
            // file contains something
        }
        else
        {
            error_message += filename_input;
            error_message += " is empty.\n";
        }
    }
    IN.close();
    return error_message;
};

// Get output string
std::string Log::get_bash_command( int argc, char **argv ){
    std::string outputline;
    outputline += "\nYour command was: \n";
    for( int i = 0; i < argc; i++ )
    {
        outputline += argv[ i ];
        outputline += " ";
    }
    return outputline;
};
std::string Log::get_settings(){
    std::string outputline = "\n\nSettings:\n";

    // Files
    outputline += "\nInput\n\tThe input filename: ";
    outputline += filename_input;
    outputline += "\n\nOutput\n\tThe output filename: ";
    outputline += filename_output_filtered_data;
    if( indicator_output_rowsums_presence )
    {
        outputline += "\n\tThe output filename for extra file with rowsums and presence: ";
        outputline += filename_output_rowsums_presence;
    }
    if( indicator_output_colsums )
    {
        outputline += "\n\tThe output filename for extra file with colsums: ";
        outputline += filename_output_colsums;
    }

    // Separator(s)
    outputline += "\nSeparator\n\tThe separator in the input file is assumed to be \"";
    if( sep == "\t" )
    {
        outputline += "tab\"\n";
    }
    else if( sep == " " )
    {
        outputline += "space\", \" \"\n";
    }
    else
    {
        outputline += sep;
        outputline += "\"";
    }

    // Settings
    outputline += "\nThreshold Setting(s)\n";
    outputline += "\n\tThreshold for minimum rowsum that gets not filtered out: ";
    outputline += std::to_string( threshold_min_rowsum );
    outputline += "\n\tThreshold for maximum rowsum that gets not filtered out: ";
    outputline += std::to_string( threshold_max_rowsum );
    outputline += "\n\tThreshold(in percentage) for minimum presence that gets not filtered out: ";
    outputline += std::to_string( threshold_min_presence );
    outputline += "\n\tThreshold(in percentage) for maximum presence that gets not filtered out: ";
    outputline += std::to_string( threshold_max_presence );
    outputline += "\n";

    return outputline;
};
