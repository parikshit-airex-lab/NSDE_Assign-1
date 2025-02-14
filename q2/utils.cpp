#include<iostream>
#include<vector>
#include "utils.h"
using namespace std;


// Explicit Euler method
vector<real> exp_Euler(real (*funptr)(real,real), real step_size,  int interval_length, real y_initial)
{
    real y_0 = y_initial;
    int N = interval_length/step_size;
    vector<real>y(N+1);
    y[0] = y_0;
    real y_1;
    for(int p=0;p<N;p++){
        y_1 = y_0 + funptr(p*step_size, y_0)*step_size;
        y[p+1] = y_1;
        y_0 = y_1;
    }
    return y;
}

// Adams-Bashforth 2nd order method
vector<real> AB2(real (*funptr)(real,real), real step_size, int interval_length, real y_initial)
{
    real y_0 = y_initial;
    int N = interval_length/step_size;
    vector<real> y(N+1);
    y[0] = y_0;
    real y_1;
    real y_2;
    real k1 = funptr(0, y_0);
    real k2 = funptr(step_size, y_0 + k1*step_size);
    y_1 = y_0 + (k1 + k2)*step_size/2;
    y[1] = y_1; 
    for(int l=1; l<N; l++){
         y_2 = y_1 + (3*funptr((l)*step_size, y_1) - funptr((l-1)*step_size, y_0))*step_size/2;
         y[l+1] = y_2;
         y_0 = y_1;
         y_1 = y_2;
    }
    return y;
}

// Runge-Kutta 2nd order method
vector<real> RK2(real (*funptr)(real,real), real step_size, int interval_length, real y_initial)
{
    real y_0 = y_initial;
    real k1;
    real k2;
    real y_1;
    int N = interval_length/step_size;
    vector<real>y(N+1);
    y[0] = y_0;
    for(int i=0;i<N;i++){
        k1 = funptr(i*step_size, y_0);
        k2 = funptr((i+1)*step_size, y_0 + k1*step_size);
        y_1 = y_0 + (k1 + k2)*step_size/2;
        y[i+1] = y_1;
        y_0 = y_1;
    }
    return y;
}
    