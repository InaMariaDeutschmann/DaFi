DaFi - Dataset Filter Program
Version 1.0
2019-07-05
Ina Maria Deutschmann

Our dataset of millions of genes is very big. DaFi will read in the data line by line. It expects the genes in the rows and the samples in the column. While doing so, it will determine the presence and only outputs the lines if the presence is not below/above the min/max threshold, which is 0%/100% by default but can be changed with --threshold_min_presence/--threshold_max_presence. On the way the program tracks the number of reads per sample, per gene, and of the dataset. Thus, it is also possible to filter the gene table based on the sum. The threshold is 0/inf but can be changed with --threshold_min_rowsum/--threshold_max_rowsum.

# GENERAL USAGE NOTES
- DaFi is a program to filter datasets based on the sum of values in each row, and also based on the presence, i.e. how many values are above 0. It expects a table with the first row being the row names, and the first column being the column names. Further, it expects positive values and no missing values.

# DEPENDENCIES
The program requires the 
- gcc = GNU Compiler Collection (GCC)
- boost = boost C++ Libraries

# COMPILATION
The makefile contains the code to generate all required commands to compile the program. Go within the terminal into the folder `DaFi` and type
```
make
```

# Usage
```
[PATH to DaFi folder]/build/DaFi --input_file [PATH/FILENAME] [OPTIONS]
```

# Get help and option overview with
```
./build/DaFi -h
```
or
```
./build/DaFi --help
```

# CONTACT
Ina Maria Deutschmann
ina.m.deutschmann@gmail.com
5th of July 2019