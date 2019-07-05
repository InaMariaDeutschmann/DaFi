#ifndef tracker_Hpp
#define tracker_Hpp

#include <string> // operator + for string concatenation std::stoi std::stod
#include <vector> // vector

class Tracker{
    public:
        // Constructor
        Tracker();

        // Add info
        void tracker_colnames( std::vector< std::string > v );
        void add_colsum( int i, double d );
        void add_plus1_Tracker_fullfillded_rowsum();
        void add_plus1_Tracker_not_fullfillded_rowsum();
        void add_plus1_Tracker_fullfillded_presence();
        void add_plus1_Tracker_not_fullfillded_presence();
        void add_plus1_Tracker_fullfillded_both();
        void add_plus1_Tracker_num_rows();
    
        // Get output string
        std::string get_report( double threshold_min_rowsum, double threshold_min_presence, double rowsum_kept, double rowsum_filtered );
        void get_report_colsums( std::string filename_output_colsums );

	private:
        std::vector< std::string > Tracker_colnames;
        std::vector< double > Tracker_colsum;

        int Tracker_fullfillded_rowsum;
        int Tracker_not_fullfillded_rowsum;
        int Tracker_fullfillded_presence;
        int Tracker_not_fullfillded_presence;
        int Tracker_fullfillded_both;
        int Tracker_num_rows;
};

#endif
