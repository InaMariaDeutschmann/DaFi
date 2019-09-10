// #############################################################################
// DaFi.cpp
//
// Filter datasets based on the sum of values in each row,
//     and also based on the presence,
//     i.e. how many values are above 0.
//
// Compiling: make
// Usage:
// [PATH to AbFi folder]/build/AbFi --input_file [PATH/FILENAME] [optional OPTIONS]
//
// Input: File with numerical values
//
// Output: Filtered file
//
// Ina Maria Deutschmann
// 16. June 2019
// #############################################################################

// #############################################################################
// Dependencies
#include <iostream>
#include <fstream>                    // read in and out files
#include <getopt.h>                   // parsing options
#include <boost/version.hpp>          // boost version
#include <time.h>                     // time_t, time, ctime
#include <math.h>                     // floor
#include <chrono>                     // steady_clock

#include "output_help_message.hpp"
#include "output_version_message.hpp"
#include "log.hpp"
#include "error_handling.hpp"
#include "dafi.hpp"
// #############################################################################

// #############################################################################
int main(int argc, char *argv[]) {
    // Start time of program
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    //Starttime
    time_t starttime;
    struct tm * timeinfo;
    char buffer [80];
    time (&starttime);
    timeinfo = localtime (&starttime);

    strftime (buffer, 80, "%Y-%m-%d_%Hh%Mmin%Ssec", timeinfo);

    // Constructors
    Log log = Log();
    log.set_filename_output_logfile( (std::string)buffer );
    Error_handling ERR = Error_handling();

    // Parsing Options
    int opt = 0;
    int longIndex = 0;
    static const char *optString = "hvdf:m:o:t:";

    static const struct option longOpts[] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { "defaults", no_argument, NULL, 'd' },
        // Required options
        { "input_file", required_argument, NULL, 'f' },  // expected to have first row as colnames and first column as rownames
        // Thresholds input
        { "threshold_min_rowsum", required_argument, NULL, 0 },
        { "threshold_max_rowsum", required_argument, NULL, 0 },
        { "threshold_min_presence", required_argument, NULL, 0 },
        { "threshold_max_presence", required_argument, NULL, 0 },
        // Inputfile Separator
        { "separator_file", required_argument, NULL, 0 },
        // Outputfiles
        { "output_file_filtered", required_argument, NULL, 'o' },
        { "no_output_file_filtered", no_argument, NULL, 0 },
        { "output_file_rowsums_presence", required_argument, NULL, 0 },
        { "output_file_colsums", required_argument, NULL, 0 },
        { NULL, no_argument, NULL, 0 } // <- needed?
    };

    opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    while ( opt != -1 )
    {
        switch ( opt )
        {
            // { "help", no_argument, NULL , 'h' },
            case 'h':
                get_help_message( argv[ 0 ]);
                std::cout << std::endl;
                return 1;
                break;

            // { "version", no_argument, NULL, 'v' },
            case 'v':
                std::cout << get_version_message( argv[0] ) << std::endl;
                return 1;
                break;

            //{ "defaults", no_argument, NULL, 'v' },
            case 'd':
                get_defaults();
                std::cout << std::endl;
                return 1;
                break;

            // { "input_file", required_argument, NULL, 'f' },
            case 'f':
                log.set_filename_input( optarg );
                ERR.set_error_input_missing();
                break;

            // Outputfiles
            // { "output_file_filtered", required_argument, NULL, 'o' },
            case 'o':
                log.set_filename_output_filtered_data( optarg );
                break;

            // long option without a short arg
            case 0:
            {
                // { "separator_file", required_argument, NULL, 0 },
                if( strcmp( "separator_file", longOpts[longIndex].name ) == 0 )
                {
                    log.set_sep( optarg );
                }
                // Thresholds input
                else if( std::string( longOpts[longIndex].name).substr( 0 , 1 ) == "t" )
                {
                    // { "threshold_min_rowsum", required_argument, NULL, 0 },
                    if( strcmp( "threshold_min_rowsum", longOpts[longIndex].name ) == 0 )
                    {
                        log.set_threshold_min_rowsum( optarg );
                    }
                    // { "threshold_min_rowsum", required_argument, NULL, 0 },
                    if( strcmp( "threshold_max_rowsum", longOpts[longIndex].name ) == 0 )
                    {
                        log.set_threshold_max_rowsum( optarg );
                    }
                    //{ "threshold_min_presence", required_argument, NULL, 0 },
                    else if( strcmp( "threshold_min_presence", longOpts[longIndex].name ) == 0 )
                    {
                        log.set_threshold_min_presence( optarg );
                    }
                    //{ "threshold_min_presence", required_argument, NULL, 0 },
                    else if( strcmp( "threshold_max_presence", longOpts[longIndex].name ) == 0 )
                    {
                        log.set_threshold_max_presence( optarg );
                    }
                }
                // Extra output
                else if( std::string( longOpts[longIndex].name).substr( 0 , 1 ) == "o" )
                {
                    // { "output_file_rowsums_presence", no_argument, NULL, 0 },
                    if( strcmp( "output_file_rowsums_presence", longOpts[longIndex].name ) == 0 ){
                        log.set_indicator_output_rowsums_presence();
                        log.set_filename_output_rowsums_presence( optarg );
                    }
                    // { "output_file_colsums", no_argument, NULL, 0 },
                    else if( strcmp( "output_file_colsums", longOpts[longIndex].name ) == 0 ){
                        log.set_indicator_output_colsums();
                        log.set_filename_output_colsums( optarg );
                    }
                }
                // { "no_output_file_filtered", no_argument, NULL, 0 },
                else if( strcmp( "no_output_file_filtered", longOpts[longIndex].name ) == 0 ){
                    log.set_indicator_output_file_filter();
                }
                //else{ // getopt_long sets next option right QuitNow, we shouldnt worry }
            }
                break;

            case '?':
                ERR.set_error_unexpected_option( longOpts[longIndex].name );
                break;

                // Error handling code here would be good, but obvious errors should be already catched before.
        }
        opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    }

    // ToLog: welcome message and version
    std::ofstream toLog( log.get_filename_output_logfile() );
    toLog << get_version_message( argv[0] ) << std::endl;
    std::string outputline = "Versions:";
    outputline += "\nGNU GCC/G++: ";
    outputline += std::to_string( __GNUC__ );
    outputline += ".";
    outputline += std::to_string( __GNUC_MINOR__ );
    outputline += ".";
    outputline += std::to_string( __GNUC_PATCHLEVEL__ );
    outputline += "\nboost: ";
    outputline += std::to_string( BOOST_VERSION / 100000 );     // major version
    outputline += ".";
    outputline += std::to_string( BOOST_VERSION / 100 % 1000 ); // minor version
    outputline += ".";
    outputline += std::to_string( BOOST_VERSION % 100 );        // patch level
    outputline += "\n";
    toLog << outputline;
    toLog << log.get_bash_command( argc, argv ) << std::endl;

    // Error Report
    ERR.set_error_input_files( log.check_input_files() );
    if( ERR.did_error_occur() )
    {
        toLog << ERR.get_error_report() << std::endl;
        std::cout << ERR.get_error_report();
        get_help_message( argv[ 0 ]);
        std::cout << std::endl;
        return 1;
    }

    // ToLog: settings
    toLog << log.get_settings() << std::endl;

    // Constructor for indirect edge detection
    DaFi my_DaFi = DaFi(log.get_sep(), log.get_indicator_output_rowsums_presence(), log.get_filename_output_rowsums_presence(), log.get_threshold_min_presence(), log.get_threshold_max_presence(), log.get_threshold_min_rowsum(), log.get_threshold_max_rowsum());
    
    /// Dataset filtering
    // Read in rows from file and output if they above threshold filters
    std::ifstream IN( log.get_filename_input() );
    std::ofstream OUT( log.get_filename_output_filtered_data() );
    // Output extra file
    if( log.get_indicator_output_rowsums_presence() )
    {
        std::ofstream OUT( log.get_filename_output_rowsums_presence() );
        OUT << "ID\trowsum\tpresence" << std::endl;
        OUT.close();
    }
    if( IN.good() )
    {
        std::string l;
        // Read in header (1st line)
        if( getline( IN, l ).good() )
        {
            toLog << "\nReading in " << log.get_filename_input() << " for filtering." << std::endl;
            my_DaFi.set_num_samples( l ); // first line is colnames, is used to determine the number of columns in file
            OUT << l << std::endl;
            
            if( log.get_indicator_output_file_filter() == 1 )
            {
                while( getline( IN, l).good() )
                {
                    std::string outputline = my_DaFi.filter( l ); // Here happenes the filtering!!!
                    if( outputline != "" )
                    {
                        OUT << outputline << std::endl;
                    }
                }
            }
            else
            {
                while( getline( IN, l).good() )
                {
                    std::string outputline = my_DaFi.filter( l ); // Here happenes the filtering!!!
                }
            }
        }
    }
    // Close network files
    IN.close();
    OUT.close();

    // ToLog: Trackers
    toLog << my_DaFi.get_tracker_report( log.get_indicator_output_colsums(), log.get_filename_output_colsums() );

    // End time of program
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

    // ToLog: Time the program needed to compute
    toLog << "Computing time:" << std::endl;
    // End time
    time_t endtime;
    struct tm * timeinfo2;
    char buffer2 [80];
    time (&endtime);
    timeinfo2 = localtime (&endtime);

    strftime (buffer2, 80, "%Y-%m-%d_%Hh%Mmin%Ssec", timeinfo2);

    toLog << "Start: " << buffer << std::endl;
    toLog << "End:   " << buffer2 << std::endl;

    // Difference
    double sec2 = difftime(endtime,starttime);
    double hour = std::floor( sec2/(1440) );
    double min = std::floor((sec2-hour*1440)/60);
    double sec = sec2 - hour*1440 - min*60;

    toLog << "\nin sec:          " << sec2 << std::endl;
    toLog << "in hour:min:sec: " << hour << ":" << min << ":" << sec << std::endl;
    // Close Log file
    toLog.close();

    return 0;
};
