#include "utils.h"
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;

// Runge-Kutta 4th order method
vector<vector<real>> RK4(vector<real>b, real (*f1ptr)(real,real,real,real,real,real,real,real), real (*f2ptr)(real,real,real,real,real,real,real,real), real step_size, real interval_length, real x_initial,real v_initial)
{
    vector<real>values(5);
    for (int i=0;i<5;i++){
        values[i] = b[i];
    }
    real x_0 = x_initial;
    real v_0 = v_initial;
    int N = interval_length/step_size;
    vector<vector<real>>ans(2,vector<real>(N+1));
    ans[0][0] = x_0;
    ans[1][0] = v_0;
    real x_1;
    real v_1;
    real k1_x;
    real k2_x;
    real k3_x;
    real k4_x;
    real k1_v;
    real k2_v;
    real k3_v;
    real k4_v;
    real h = step_size;
    for(int i=0;i<N;i++)
    {
        k1_x = f1ptr(values[0],values[1],values[2],values[3],values[4],i*h,x_0,v_0);
        k1_v = f2ptr(values[0],values[1],values[2],values[3],values[4],i*h,x_0,v_0);
        k2_x = f1ptr(values[0],values[1],values[2],values[3],values[4],i*h + h/2, x_0 + k1_x*h/2, v_0 + k1_v*h/2);
        k2_v = f2ptr(values[0],values[1],values[2],values[3],values[4],i*h + h/2, x_0 + k1_x*h/2, v_0 + k1_v*h/2);
        k3_x = f1ptr(values[0],values[1],values[2],values[3],values[4],i*h + h/2, x_0 + k2_x*h/2, v_0 + k2_v*h/2);
        k3_v = f2ptr(values[0],values[1],values[2],values[3],values[4],i*h + h/2, x_0 + k2_x*h/2, v_0 + k2_v*h/2);
        k4_x = f1ptr(values[0],values[1],values[2],values[3],values[4],i*h + h, x_0 + k3_x*h, v_0 + k3_v*h);
        k4_v = f2ptr(values[0],values[1],values[2],values[3],values[4],i*h + h, x_0 + k3_x*h, v_0 + k3_v*h);
        x_1 = x_0 + (k1_x + 2*k2_x + 2*k3_x + k4_x)*h/6;
        v_1 = v_0 + (k1_v + 2*k2_v + 2*k3_v + k4_v)*h/6;
        ans[0][i+1] = x_1;
        ans[1][i+1] = v_1;
        x_0 = x_1;
        v_0 = v_1;
    }
    return ans;
}