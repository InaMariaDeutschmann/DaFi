#include "tracker.hpp"

#include <iostream>
#include <fstream> // read in and out files

Tracker::Tracker(){    
    Tracker_fullfillded_rowsum = 0;
    Tracker_not_fullfillded_rowsum = 0;
    Tracker_fullfillded_presence = 0;
    Tracker_not_fullfillded_presence = 0;
    Tracker_fullfillded_both = 0;
    Tracker_num_rows = 0;
};

// Add info
void Tracker::tracker_colnames( std::vector< std::string > v ){
    Tracker_colnames = v;
    Tracker_colnames[ 0 ] = "Total_sum";
    std::vector< double > new_Tracker_colsum ( v.size(), 0 ); // v.size() = number of columns, array contains only zeros
    Tracker_colsum = new_Tracker_colsum;
};
void Tracker::add_colsum( int i, double d ){
    Tracker_colsum[ i ] += d;
    Tracker_colsum[ 0 ] += d;
};
void Tracker::add_plus1_Tracker_fullfillded_rowsum(){
    Tracker_fullfillded_rowsum += 1;
};
void Tracker::add_plus1_Tracker_not_fullfillded_rowsum(){
    Tracker_not_fullfillded_rowsum += 1;
};
void Tracker::add_plus1_Tracker_fullfillded_presence(){
    Tracker_fullfillded_presence += 1;
};
void Tracker::add_plus1_Tracker_not_fullfillded_presence(){
    Tracker_not_fullfillded_presence += 1;
};
void Tracker::add_plus1_Tracker_fullfillded_both(){
    Tracker_fullfillded_both += 1;
};
void Tracker::add_plus1_Tracker_num_rows(){
    Tracker_num_rows += 1;
};

// Get output string
std::string Tracker::get_report( double threshold_min_rowsum, double threshold_min_presence, double rowsum_kept, double rowsum_filtered ){
    std::string outputline = "";
    
    outputline += "\nTrackers:\n";
    outputline += std::to_string( Tracker_num_rows );
    outputline += " rows in total.\n\t";
    outputline += std::to_string( Tracker_fullfillded_rowsum );
    outputline += " rows have sum >= ";
    outputline += std::to_string( threshold_min_rowsum );
    outputline += "\n\t";
    outputline += std::to_string( Tracker_not_fullfillded_rowsum );
    outputline += " rows have sum < ";
    outputline += std::to_string( threshold_min_rowsum );
    outputline += "\n\t";
    outputline += std::to_string( Tracker_fullfillded_presence );
    outputline += " rows have presence >= ";
    outputline += std::to_string( threshold_min_presence );
    outputline += "\n\t";
    outputline += std::to_string( Tracker_not_fullfillded_presence );
    outputline += " rows have presence < ";
    outputline += std::to_string( threshold_min_presence );
    outputline += "\n\t";
    outputline += std::to_string( Tracker_fullfillded_both );
    outputline += " rows have sum >= ";
    outputline += std::to_string( threshold_min_rowsum );
    outputline += " and presence >= ";
    outputline += std::to_string( threshold_min_presence );
    outputline += "\n\nRowsum:\n\tTotal: ";
    outputline += std::to_string( Tracker_colsum[0] );
    outputline += "\n\tKept: ";
    outputline += std::to_string(rowsum_kept);
    outputline += "\n\tFiltered: ";
    outputline += std::to_string(rowsum_filtered);
    outputline += "\n\nRowsum in percentage:\n\tTotal: 100%";
    outputline += "\n\tKept: ";
    outputline += std::to_string( rowsum_kept / Tracker_colsum[0] * 100 );
    outputline += "%\n\tFiltered: ";
    outputline += std::to_string( rowsum_filtered / Tracker_colsum[0] * 100 );
    outputline += "%\nDone!\n\n";
    
    return outputline;
};

void Tracker::get_report_colsums( std::string filename_output_colsums ){
    std::ofstream OUT( filename_output_colsums );
    OUT << "Col_name\tCol_sum" << std::endl;
    for( int i = 1; i < Tracker_colsum.size(); i++ )
    {
        OUT << Tracker_colnames[i] << "\t" << Tracker_colsum[i] << std::endl;
    }
    OUT.close();
};
