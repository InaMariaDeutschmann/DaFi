#ifndef log_Hpp
#define log_Hpp

#include <string> // operator + for string concatenation std::stoi std::stod

class Log{
    public:
        // Constructor
        Log();

        // Set info
        void set_filename_input( std::string s );
        void set_filename_output_filtered_data( std::string s );
        void set_filename_output_rowsums_presence( std::string s );
        void set_filename_output_colsums( std::string s );
        void set_filename_output_logfile( std::string s );
        void set_sep( std::string s );
        void set_threshold_min_rowsum( std::string s );
        void set_threshold_max_rowsum( std::string s );
        void set_threshold_min_presence( std::string s );
        void set_threshold_max_presence( std::string s );
        void set_indicator_output_rowsums_presence();
        void set_indicator_output_colsums();
        void set_indicator_output_file_filter();

        // Get info
        int get_indicator_output_rowsums_presence();
        int get_indicator_output_colsums();
        int get_indicator_output_file_filter();
        double get_threshold_min_rowsum();
        double get_threshold_max_rowsum();
        double get_threshold_min_presence();
        double get_threshold_max_presence();
        std::string get_filename_input();
        std::string get_filename_output_filtered_data();
        std::string get_filename_output_rowsums_presence();
        std::string get_filename_output_colsums();
        std::string get_filename_output_logfile();
        std::string get_sep();
    
        // Check input files
        std::string check_input_files();

        // Get output string
        std::string get_bash_command( int argc, char **argv );
        std::string get_settings();

	private:
        // Parameters
        int indicator_output_rowsums_presence;        // Indicator to create extra output
        int indicator_output_colsums;                 // Indicator to create extra output
        int indicator_output_file_filter;             // Indicator to create filtered file output
        double threshold_min_rowsum;                  // Threshold for min rowsum
        double threshold_max_rowsum;                  // Threshold for max rowsum
        double threshold_min_presence;                // Threshold for min presence within row
        double threshold_max_presence;                // Threshold for max presence within row

        // Filenames
        std::string filename_input;                   // Filename/path of input
        std::string filename_output_filtered_data;    // Filename/path of output
        std::string filename_output_rowsums_presence; // Filename of extra output
        std::string filename_output_colsums;          // Filename of extra output
        std::string filename_output_logfile;          // Filename of logfile
        // Separators of input files
        std::string sep;                              // Separator for input file
 };

#endif
