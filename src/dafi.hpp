#ifndef dafi_Hpp
#define dafi_Hpp

#include "tracker.hpp"

#include <string>
#include <vector>                     // vector
#include <unordered_map>              // unordered_maps
#include <boost/algorithm/string.hpp> // split


class DaFi{
    public:
        // Constructor
        DaFi( std::string set_sep, int set_indicator_output_rowsums_presence, std::string set_filename_output_rowsums_presence, double set_threshold_min_presence, double set_threshold_max_presence, double set_threshold_min_rowsum, double set_threshold_max_rowsum() );
    
        // set_num_samples( l )
        void set_num_samples( std::string line );

        // Dataset Filtering
        std::string filter( std::string line );
    
        // Get
        std::string get_tracker_report( int indicator_print_colsum, std::string filename_output_colsums );

	private:
        // Tracking
        int error_occurred;
        std::string error_message;
        std::string log_message;
        std::string triplet_info_message;
        int indicator_triplet_edge;
        double rowsum_filtered;
        double rowsum_kept;

        // Filename
        std::string filename_output_rowsums_presence;
        std::string sep;

        // Settings
        int num_samples;
        double threshold_min_presence;
        double threshold_max_presence;
        double threshold_min_rowsum;
        double threshold_max_rowsum;

        // Extra output indicator
        int indicator_output_rowsums_presence;

        // Other Datastructures
        Tracker my_tracker;
};

#endif
