//first_time_cluster_fixing.cpp
#include <iostream>
#include <fstream>

using namespace std;

int firts_two_bits(int a){
    int b=a%100;
    return (a-b)/100;
}

int * first_clustering(string str, int * number_of_rows, int * number_of_columns) {
    
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
    cout << "columns = " << columns << ", rows = " << rows << endl;
    if (*number_of_rows==rows){}
        else
            cout<<"There is a mismatch between the N timeseries and the sectors to which they belong";
    
    //put data in a matrix
    int ** clustering;
    clustering=new int*[rows];
    for (int i=0; i<rows; i++)
        clustering[i] = new int[columns];
    
    ifstream all_data_f;
    all_data_f.open(str);
    
    if (all_data_f.is_open())
    {
        for (int i=0; i<rows; i++)
        {
            for (int t=0; t<columns; t++)
            {
                all_data_f>>clustering[i][t];
            }
        }
    }
    else
        cout<<"The file was not opend correctly.";
    
    //select the first two digits of the code and put them in an array
    int * cl;
    cl=new int[rows];
    //int no_sector=0;
    
    for (int j=0; j<rows; j++) {
        if (clustering[j][1] != 0) {
            cl[j]=firts_two_bits(clustering[j][1]);
        } else {
            if (clustering[j][0]!=0) {
                cl[j]=firts_two_bits(clustering[j][0]);
            } else {
                cl[j]=0;
                //no_sector++; there are 10 firms with no classification
            }
        }
    }
    return cl;
}