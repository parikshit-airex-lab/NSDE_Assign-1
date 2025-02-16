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
real Nonlinear_solver(real (*funptr)(real,real),real(*funptr1)(real,real),real tol, int max_iter, real x_next, real y_next, real y_current, real step_size);
vector<real> imp_Euler(real (*funptr)(real, real),real(*funptr1)(real,real), real step_size, int interval_length, real y_initial, real tol, int max_iter);
#endif