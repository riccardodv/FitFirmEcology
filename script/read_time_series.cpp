//read_time_series.cpp
//Definition of the function that reads data from file and creates a matrix with the time-series
#include <iostream>
#include <fstream>

using namespace std;

double ** read_time_series(string str, int * number_of_rows, int * number_of_columns){

//read the number of columns and rows in the file
    FILE *fp;
    fp = fopen(str.c_str(),"r");
    
    int columns = 0, rows = 0, i;
    while((i=fgetc(fp))!=EOF)
    {
        if(i=='\t'){
            columns++;
        } else if(i == '\n')
            rows++;
    }
   
    columns = columns/rows + 1;
    //cout << "columns = " << columns << ", rows = " << rows << endl;
    * number_of_rows = rows;
    * number_of_columns = columns;
    //put data in a matrix
    double ** mvs;
    mvs=new double*[rows];
    for (int i=0; i<rows; i++)
        mvs[i] = new double[columns];

    ifstream all_data_f;
    all_data_f.open(str);
    
    if (all_data_f.is_open())
    {
        for (int i=0; i<rows; i++)
        {
            for (int t=0; t<columns; t++)
            {
                all_data_f>>mvs[i][t];
            }
        }
    }
    else
        cout<<"The file was not opend correctly.";
    
    return mvs;

}