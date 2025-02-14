#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<functional>
#include<vector>
using namespace std;

// Define a type alias for precision
using real = double;

// Function declarations 
vector<real> exp_Euler(real (*funptr)(real, real), real step_size, int interval_length, real y_initial);
vector<real> AB2(real (*funptr)(real, real), real step_size, int interval_length, real y_initial);
vector<real> RK2(real (*funptr)(real, real), real step_size, int interval_length, real y_initial);
#endif