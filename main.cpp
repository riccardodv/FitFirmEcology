#include <iostream>
#include "common.h"
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

double ** read_time_series(string, int * number_of_rows, int * number_of_columns);
int * first_clustering(string, int * number_of_rows, int * number_of_columns);
double sx1(int t, int s, double ** time_series, int * clustering, int * number_of_rows);
double sx2(int t, int s, double ** time_series, int * clustering, int * number_of_rows);
double nst(int t, int s, double ** time_series, int * clustering, int * number_of_rows);
VecDoub min(int * number_of_rows, int * number_of_columns, int * number_of_sectors, double **time_series, int * clustering);

struct likelihood;

int main() {
    
    int n_o_r,n_o_c;
    int n_o_s=100;
    int * number_of_rows=&n_o_r;
    int * number_of_columns=&n_o_c;
    int * number_of_sectors=&n_o_s;
    string name_file_timeseries, name_file_initclustering;
    cout<<"Insert below the name of the file you would like to read the time-series from:"<<endl;
    cin>>name_file_timeseries;
    double ** time_series = read_time_series(name_file_timeseries,number_of_rows,number_of_columns);
    
    
    cout<<"Insert below the name of the file containing the first clustering (according to SIC for example):"<<endl;
    cin>>name_file_initclustering;
    int * clustering = first_clustering(name_file_initclustering,number_of_rows,number_of_columns);
    cout << "*columns = " << *number_of_columns << ", rows = " << *number_of_rows << endl;
    
    //get VecDoub-array given by my function minimize
    VecDoub minima;
    minima=min(number_of_rows,number_of_columns,number_of_sectors,time_series,clustering);
    
    cout<<"hello";
    
}
