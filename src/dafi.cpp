#include "dafi.hpp"

#include <iostream>
#include <fstream> // read in and out files
#include <cmath>   // nan("")

DaFi::DaFi( std::string set_sep, int set_indicator_output_rowsums_presence, std::string set_filename_output_rowsums_presence, double set_threshold_min_presence, double set_threshold_max_presence, double set_threshold_min_rowsum, double set_threshold_max_rowsum ){
    // Tracking
    error_occurred = 0;
    error_message = "";
    log_message = "";
    triplet_info_message = "";
    indicator_triplet_edge = 0;

    // Filename
    filename_output_rowsums_presence = set_filename_output_rowsums_presence;
    sep = set_sep;

    // Settings
    threshold_min_presence = set_threshold_min_presence;
    threshold_max_presence = set_threshold_max_presence;
    threshold_min_rowsum = set_threshold_min_rowsum;
    threshold_max_rowsum = set_threshold_max_rowsum;

    // Extra output indicator
    indicator_output_rowsums_presence = set_indicator_output_rowsums_presence;

    // Constructors
    my_tracker = Tracker();
};

// set_num_samples( l )
void DaFi::set_num_samples( std::string line ){
    // remove "newline" sign if there is one at the end of the line
    size_t found = line.find( '\n' );
    if( found != std::string::npos ){ line = line.substr(0, line.size()-1); }
    found = line.find( '\r' );
    if( found != std::string::npos ){ line = line.substr(0, line.size()-1); }
    
    // Split line by separator
    std::vector< std::string > v;
    split( v, line, boost::is_any_of( sep ) ); // Split by sep, vector positions starts with 0, but [0]=rowname
    
    // Track colnames
    my_tracker.tracker_colnames( v );
    
    // Set colnumber
    num_samples = v.size() - 1;
};


// Dataset Filtering
std::string DaFi::filter( std::string line ){
    // Outputline
    std::string outputline = "";
    
    // remove "newline" sign if there is one at the end of the line
    size_t found = line.find( '\n' );
    if( found != std::string::npos ){ line = line.substr(0, line.size()-1); }
    found = line.find( '\r' );
    if( found != std::string::npos ){ line = line.substr(0, line.size()-1); }
    
    // Split line by separator
    std::vector< std::string > v;
    split( v, line, boost::is_any_of( sep ) ); // Split by sep, vector positions starts with 0, but [0]=rowname
    
    // Convert to doubles and determine row sum and presence
    double rowsum = 0;
    double presence = 0;
    double min_presence_allowed = num_samples * threshold_min_presence / 100;
    double max_presence_allowed = num_samples * threshold_max_presence / 100;
    for( int i = 1; i <= num_samples; i++)
    {
        double d = std::stod( v[i] );
        if( d > 0 )
        {
            rowsum += d;
            presence += 1;
            
            // Track column sum
            my_tracker.add_colsum(i,d);
        }
    }
    // Filter
    int bool_rowsum = 0;
    int bool_presence = 0;
    if( rowsum >= threshold_min_rowsum && rowsum <= threshold_max_rowsum )
    {
        my_tracker.add_plus1_Tracker_fulfilled_rowsum();
        bool_rowsum = 1;
    }
    else
    {
        my_tracker.add_plus1_Tracker_not_fulfilled_rowsum();
    }
    if( presence >= min_presence_allowed && presence <= max_presence_allowed )
    {
        my_tracker.add_plus1_Tracker_fulfilled_presence();
        bool_presence = 1;
    }
    else
    {
        my_tracker.add_plus1_Tracker_not_fulfilled_presence();
    }
    
    if( bool_rowsum && bool_presence )
    {
        my_tracker.add_plus1_Tracker_fulfilled_both();
        outputline = line;
        my_tracker.add_rowsum_kept( rowsum );
    }
    else
    {
        my_tracker.add_rowsum_filtered( rowsum );
    }
    my_tracker.add_plus1_Tracker_num_rows();
    
    // Output extra file
    if( indicator_output_rowsums_presence )
    {
        std::ofstream OUT( filename_output_rowsums_presence, std::ios::out|std::ios::app );
        OUT << v[0] << "\t" << rowsum << "\t" << presence << std::endl;
        OUT.close();
    }
    return outputline;
    
};

// Get
std::string DaFi::get_tracker_report( int indicator_print_colsum, std::string filename_output_colsums ){
    if( indicator_print_colsum )
    {
        my_tracker.get_report_colsums( filename_output_colsums );
    }
    return my_tracker.get_report();
};
