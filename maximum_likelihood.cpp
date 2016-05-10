//maximum_likelihood.cpp
//In this part we want to create a function, a log-likelihood in our case, and we want to find the parameters which maximise it.
#include <iostream>
#include <fstream>
#include <cmath>
#include "common.h"

using namespace std;

double sx2(int t, int s, double ** time_series, int * clustering, int * number_of_rows/*, int * number_of_columns*/){ //maybe number of columns not necessary to be passed to function
    
    double sum=0;
    for (int i=0; i< *number_of_rows; i++) {
        if (s==clustering[i]) {
            sum=sum+time_series[i][t]*time_series[i][t];
        }
    }
    return sum;
}

double sx1(int t, int s, double ** time_series, int * clustering, int * number_of_rows){
    
    double sum=0;
    for (int i=0; i< *number_of_rows; i++) {
        if (s==clustering[i]) {
            sum=sum+time_series[i][t];
        }
    }
    return sum;
}

double nst(int t, int s, double ** time_series, int * clustering, int * number_of_rows){
    
    double sum=0;
    for (int i=0; i< *number_of_rows; i++) {
        if (s==clustering[i] && time_series[i][t]!=0.) {
            sum++;
        }
    }
    return sum;
}

struct likelihood{
    
    int * n_o_r;
    int * n_o_c;
    int * n_o_s;
    double ** t_s;
    int * cl;
    likelihood(int * number_of_rows, int * number_of_columns, int * number_of_sectors, double ** time_series, int * clustering) : n_o_r(number_of_rows), n_o_c(number_of_columns), n_o_s(number_of_sectors), t_s(time_series), cl(clustering) {}
    Doub operator()(VecDoub z){
        double sum=0;
        //for (int t=0; t< *n_o_c; t++) {
            //for (int s=0; s< *n_o_s; s++) {
                for (int s=0; s< 100; s++) {
                /*sum+=log((pow(z[s+200],2)+nst(t,s,t_s,cl,n_o_r)*pow(z[s+100],2))/(pow(z[s+200],2*(1-nst(t,s,t_s,cl,n_o_r)))))+(sx2(t,s,t_s,cl,n_o_r)+nst(t,s,t_s,cl,n_o_r)*pow(z[s],2)-2*sx1(t,s,t_s,cl,n_o_r)*z[s])/(pow(z[s+200],2))-(pow(z[s]*nst(t,s,t_s,cl,n_o_r)-sx1(t,s,t_s,cl,n_o_r),2)*pow(z[s+100],2))/(pow(z[s+200],2)*(pow(z[s+200],2)+nst(t,s,t_s,cl,n_o_r)*pow(z[s+100],2)));*/
                sum=sum+pow(z[s]-s*s,2);
            }
        //}
        
        return sum;
        //return (z[0]-1)*(z[0]-1)+(z[1]+2)*(z[1]+2)+(z[2]-3-(*n_o_s))*(z[2]-3-(*n_o_s))+4;
    }
};

VecDoub min(int * number_of_rows, int * number_of_columns, int * number_of_sectors, double **time_series, int * clustering){
    
        cout<<"blabla"<<*number_of_rows<<endl;
    
    likelihood f(number_of_rows, number_of_columns, number_of_sectors, time_series, clustering);
    
        cout<<"---------"<<endl<<*number_of_rows<<endl<<*number_of_columns<<endl<<*number_of_sectors<<endl<<time_series[1][16]<<endl<<"---------"<<endl;
    
    VecDoub pmin(100);
    
    for (int i =0; i<100; i++) {
        pmin[i]=1;
    }
    
    Powell<likelihood> powell(f);
    pmin=powell.minimize(pmin);
    
    //Doub ftol=pow(10,-16);
    //Amoeba am(ftol);
    /*VecDoub initial_points(3*(*number_of_sectors));
    
    
    for (int i =0; i<16; i++) {
        initial_points[i]=1;
    }*/
    //for (int i =0; i<3*(*number_of_sectors); i++) {
    //    initial_points[i]=1;
    //}
    //VecDoub initial_points(3);
    //initial_points[0]=32;
    //initial_points[1]=54;
    //initial_points[2]=65;

    //Doub del = 1;
    //pmin=am.minimize(initial_points,del,f);
    
        cout<<"zeze"<<endl<<pmin[0]<<endl;
    
    
    //for (int i =0; i<3*(*number_of_sectors); i++) {
    //    cout<<pmin[i]<<endl;
    //cout<<pmin[0]<<endl<<pmin[1]<<endl<<pmin[2]<<endl;
    for (int i=0; i<100; i++) {
        cout<<pmin[i]<<endl;
    }
    //}
    return pmin;
    
}


/*
int number_of_rows(int * n_o_r){
    return n_o_r
}

int number_of_columns(int * n_o_c){
    return n_o_c
}*/