# DaFi - Dataset Filter Program

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3269808.svg)](https://doi.org/10.5281/zenodo.3269808) <div itemscope itemtype="https://schema.org/Person"><a itemprop="sameAs" content="https://orcid.org/0000-0002-3512-261X" href="https://orcid.org/0000-0002-3512-261X" target="orcid.widget" rel="noopener noreferrer" style="vertical-align:top;"><img src="https://orcid.org/sites/default/files/images/orcid_16x16.png" style="width:1em;margin-right:.5em;" alt="ORCID iD icon"></a></div>


DaFi will read in the data line by line. It expects the observations in the rows and the samples in the columns. While doing so, it will determine the presence and only outputs the lines if the presence is not below/above the min/max threshold, which is 0%/100% by default but can be changed with --threshold_min_presence/--threshold_max_presence. On the way the program tracks the number of reads per sample, per gene, and of the dataset. Thus, it is also possible to filter the gene table based on the sum. The threshold is 0/inf but can be changed with --threshold_min_rowsum/--threshold_max_rowsum.

## GENERAL USAGE NOTES
DaFi is a C++ program that can filter datasets based on the sum of values in each row and/or the presence, i.e. how many values are above 0. It expects a table with the first row being the row names, and the first column being the column names. Further, it expects positive values and no missing values. The makefile contains the code to generate all required commands to compile the program. Go within the terminal into the folder `DaFi` and type
```
make
```
The command to use the program is:
```
[PATH to DaFi folder]/build/DaFi --input_file [PATH/FILENAME] [OPTIONS]
```

## DEPENDENCIES
The program requires the 
- gcc = GNU Compiler Collection (GCC)
- boost = boost C++ Libraries

## Get help with
```
./build/DaFi -h
```
or
```
./build/DaFi --help
```

## Options
- `--help` Returns this help message
- `-v,--version` Returns version of the program
- `-d,--defaults` Returns default values of the program

### Required option, input file
- `-f,--input_file [filename]` Name of the input file (first line are the column names, first row rownames)

### Thresholds input
- `--threshold_min_rowsum [num]` Default: 0. Minimal allowed row sum that gets not filtered out
- `--threshold_max_rowsum [num]` Default: inf. Maximal allowed row sum that gets not filtered out
- `--threshold_min_presence [num]` Default: 0. Minimal allowed presence that gets not filtered out
- `--threshold_max_presence [num]` Default: 100. Maximal allowed presence that gets not filtered out

### Inputfile separators
- `--separator_file \"[sep]\"` Default: tab, other possibilities, but not limited to: \";\" or \" \"

### Outputfiles
- `-o,--output_file_filtered [filename]` Default: \"filtered_data.txt\"; name of the output network file
- `--no_output_file_filtered` Default: output filtered data file. With this flag results will not be printed
- `--output_file_rowsums_presence [filename]` Create output with rowsums and presence for each row
- `--output_file_colsums [filename]` Create output with colsums for each column

## Please cite as
Deutschmann, Ina Maria (2019). DaFi - Dataset Filter Program. https://doi.org/10.5281/zenodo.3269808

## Version
Version 1.0,
5th of July 2019

## CONTACT
Ina Maria Deutschmann,
ina.m.deutschmann@gmail.com
