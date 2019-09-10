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
        void add_plus1_Tracker_fulfilled_rowsum();
        void add_plus1_Tracker_not_fulfilled_rowsum();
        void add_plus1_Tracker_fulfilled_presence();
        void add_plus1_Tracker_not_fulfilled_presence();
        void add_plus1_Tracker_fulfilled_both();
        void add_plus1_Tracker_num_rows();
        void add_rowsum_kept( double d );
        void add_rowsum_filtered( double d );
    
        // Get output string
        std::string get_report();
        void get_report_colsums( std::string filename_output_colsums );

	private:
        std::vector< std::string > Tracker_colnames;
        std::vector< double > Tracker_colsum;

        int Tracker_fulfilled_rowsum;
        int Tracker_not_fulfilled_rowsum;
        int Tracker_fulfilled_presence;
        int Tracker_not_fulfilled_presence;
        int Tracker_fulfilled_both;
        int Tracker_num_rows;
        double Tracker_rowsum_kept = 0;
        double Tracker_rowsum_filtered = 0;
};

#endif
