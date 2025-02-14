#ifndef UTILS_H
#define UTILS_H

#include<functional>
#include<vector>
#include<string>
using namespace std;

// Define a type alias for precision
using real = double;

// Function declarations
vector<vector<real>> RK4(vector<real>b,real (*f1ptr)(real,real,real,real,real,real,real,real), real (*f2ptr)(real,real,real,real,real,real,real,real), real step_size, real interval_length, real x_initial,real v_initial);
#endif