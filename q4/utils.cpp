#include<iostream>
#include<vector>
#include<cmath>
#include<functional>
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

// Newton-Raphson method - Nonlinear solver
real Nonlinear_solver(real (*funptr)(real,real),real(*funptr1)(real,real),real tol, int max_iter, real x_next, real y_next, real y_current, real step_size)
{
    int iter = 0;
    while(iter < max_iter){
  real F = y_next - y_current - step_size*(funptr(x_next, y_next));
  real F_prime = 1 - step_size*(funptr1(x_next, y_next));
  real y_next_new = y_next - F/F_prime;
  if(abs(y_next_new - y_next) < tol){
      return y_next_new;
  }
  y_next = y_next_new;
  iter++;
    }
    if(iter == max_iter){
        cout<<"Max iterations reached"<<endl;
    }
    return y_next;        
}

// Implicit Euler method
vector<real> imp_Euler(real (*funptr)(real, real),real(*funptr1)(real,real), real step_size, int interval_length, real y_initial, real tol, int max_iter)
{
    real y_0 = y_initial;
    int N = interval_length/step_size;
    vector<real>y(N+1);
    y[0] = y_0;
    real y_1;
    for(int p=0;p<N;p++){
        y_1 = y_0 + funptr(p*step_size, y_0)*step_size;
        y_1 = Nonlinear_solver(funptr, funptr1, tol, max_iter, (p+1)*step_size, y_1, y_0, step_size);
        y[p+1] = y_1;
        y_0 = y_1;
    }
    return y;
}