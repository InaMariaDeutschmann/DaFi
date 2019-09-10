#include "tracker.hpp"

#include <iostream>
#include <fstream> // read in and out files

Tracker::Tracker(){    
    Tracker_fulfilled_rowsum = 0;
    Tracker_not_fulfilled_rowsum = 0;
    Tracker_fulfilled_presence = 0;
    Tracker_not_fulfilled_presence = 0;
    Tracker_fulfilled_both = 0;
    Tracker_num_rows = 0;
    Tracker_rowsum_kept = 0;
    Tracker_rowsum_filtered = 0;
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
void Tracker::add_plus1_Tracker_fulfilled_rowsum(){
    Tracker_fulfilled_rowsum += 1;
};
void Tracker::add_plus1_Tracker_not_fulfilled_rowsum(){
    Tracker_not_fulfilled_rowsum += 1;
};
void Tracker::add_plus1_Tracker_fulfilled_presence(){
    Tracker_fulfilled_presence += 1;
};
void Tracker::add_plus1_Tracker_not_fulfilled_presence(){
    Tracker_not_fulfilled_presence += 1;
};
void Tracker::add_plus1_Tracker_fulfilled_both(){
    Tracker_fulfilled_both += 1;
};
void Tracker::add_plus1_Tracker_num_rows(){
    Tracker_num_rows += 1;
};
void Tracker::add_rowsum_kept( double d ){
    Tracker_rowsum_kept += d;
};
void Tracker::add_rowsum_filtered( double d ){
    Tracker_rowsum_filtered += d;
};

// Get output string
std::string Tracker::get_report(){
    std::string outputline = "";
    
    outputline += "\nTrackers:\n";
    outputline += std::to_string( Tracker_num_rows );
    outputline += " rows in total.\n\t";
    outputline += "\nOnly RowSum Filter: ";
    outputline += "\n\tRows Kept: ";
    outputline += std::to_string( Tracker_fulfilled_rowsum );
    outputline += "\n\tRows Filtered: ";
    outputline += std::to_string( Tracker_not_fulfilled_rowsum );
    outputline += "\nOnly Presence Filter: ";
    outputline += "\n\tRows Kept: ";
    outputline += std::to_string( Tracker_fulfilled_presence );
    outputline += "\n\tRows Filtered: ";
    outputline += std::to_string( Tracker_not_fulfilled_presence );
    outputline += "\nBoth: ";
    outputline += "\n\tRows Kept: ";
    outputline += std::to_string( Tracker_fulfilled_both );
    outputline += "\n\tRows Filtered: ";
    outputline += std::to_string( Tracker_num_rows - Tracker_fulfilled_both );
    outputline += "\n\nSum:\n\tTotal: ";
    outputline += std::to_string( Tracker_colsum[0] );
    outputline += "\n\tKept: ";
    outputline += std::to_string( Tracker_rowsum_kept );
    outputline += "\n\tFiltered: ";
    outputline += std::to_string( Tracker_rowsum_filtered );
    outputline += "\n\nSum in percentage:\n\tTotal: 100%";
    outputline += "\n\tKept: ";
    outputline += std::to_string( Tracker_rowsum_kept / Tracker_colsum[0] * 100 );
    outputline += "%\n\tFiltered: ";
    outputline += std::to_string( Tracker_rowsum_filtered / Tracker_colsum[0] * 100 );
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
