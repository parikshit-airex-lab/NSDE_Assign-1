#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <filesystem>
#include <string>
#include <functional>
#include <limits>
#include <iomanip>
#include "utils.h"
using namespace std;

// Define the function equivalent to derivative

real f1 (real m, real a, real k, real f_0, real w, real t, real x, real v){
    return v;
}

real f2 (real m, real a, real k, real f_0, real w, real t, real x, real v){
    return (1/m)*(-a*abs(v)*v - k*x + f_0*sin(w*t));
}

// Function to read the parameters from an input file
bool is_readable_file(const string& filename,real&m,real&a, real&k, real&f_0, real&w, vector<real>&steps){
    ifstream input_file(filename);
    if(!input_file.is_open()){
        cout<<"Opening error for input_file"<<endl;
        return false;
    }
    string line;
    while(getline(input_file, line)){
        stringstream ss(line);
        string str;
        ss >> str;
        if(str == "m="){
            ss >> m;
            // cout<<"m = "<<m<<endl;
        }
        if(str == "a="){
            ss >> a;
            // cout<<"a = "<<a<<endl;
        }
        if(str == "k="){
            ss >> k;
            // cout<<"k = "<<k<<endl;
        }
        if(str == "f_0="){
            ss >> f_0;
            // cout<<"f_0 = "<<f_0<<endl;
        }
        if(str == "w="){
            ss >> w;
            cout<<"w = "<<w<<endl;   
        }
        if(str == "step_size="){
                real step_size;
                while(ss >> step_size){
                    steps.push_back(step_size);
                }
            }   
    }
    input_file.close();
    return true;
}

// create results folder .i.e. directory
void create_results_directory(){
    if(! filesystem:: exists("resultsq3")){
        filesystem:: create_directory("resultsq3");
        cout<<"Results directory created"<<endl;
    }
}

// generate filename for output file
string generatefilename(const string& name, string step){
        ostringstream oss;
        oss << "resultsq3/output_"<<name<<"_"<<step<<".txt";
        return oss.str();
}

// find maximum values of quantities like displacement and velocity in a vector<vector<real>>
vector<pair<real,real>> find_max(vector<vector<real>> & ans, real step_size, vector<pair<real,real>>& max_values)
{
    real max_x = numeric_limits<real>::lowest();
    real max_v = numeric_limits<real>::lowest();
    real time_x = 0;
    real time_v = 0;
    for(int i=0;i<ans[0].size();i++){
        if(ans[0][i] > max_x){
            max_x = ans[0][i];
            time_x = i*step_size;
        }
        if(ans[1][i] > max_v){
            max_v = ans[1][i];
            time_v = i*step_size;
        }
    }
    max_values.push_back(make_pair(time_x,max_x));
    max_values.push_back(make_pair(time_v,max_v));
    return max_values;
}

// find minimum values of quantities like displacement and velocity in a vector<vector<real>>
vector<pair<real,real>> find_min(vector<vector<real>> & ans, real step_size, vector<pair<real,real>> & min_values)
{
    real min_x = numeric_limits<real>::max();
    real min_v = numeric_limits<real>::max();
    real time_x = 0;
    real time_v = 0;
    for(int i=0;i<ans[0].size();i++){
        if(ans[0][i] < min_x){
            min_x = ans[0][i];
            time_x = i*step_size;
        }
        if(ans[1][i] < min_v){
            min_v = ans[1][i];
            time_v = i*step_size;
        }
    }
    min_values.push_back(make_pair(time_x,min_x));
    min_values.push_back(make_pair(time_v,min_v));
    return min_values;
}

bool check_convergence(vector<vector<real>>& ans_1,vector<vector<real>>& ans_2,vector<vector<real>> & ans_3,vector<vector<real>> & ans_4,vector<vector<real>> & ans_5, vector<real> & steps, ofstream & output_file_RK4_convergence){
    for(int i=0;i<4;i++){
        if(i == 0){
        // for t = 5 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[0][5/steps[i]] - ans_2[0][5/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[1][5/steps[i]] - ans_2[1][5/steps[i+1]])<<endl;
        // for t = 10 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[0][10/steps[i]] - ans_2[0][10/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[1][10/steps[i]] - ans_2[1][10/steps[i+1]])<<endl;
        // for t = 15 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[0][15/steps[i]] - ans_2[0][15/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_1[1][15/steps[i]] - ans_2[1][15/steps[i+1]])<<endl;
        }
        if(i == 1){
        // for t = 5 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[0][5/steps[i]] - ans_3[0][5/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[1][5/steps[i]] - ans_3[1][5/steps[i+1]])<<endl;
        // for t = 10 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[0][10/steps[i]] - ans_3[0][10/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[1][10/steps[i]] - ans_3[1][10/steps[i+1]])<<endl;
        // for t = 15 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[0][15/steps[i]] - ans_3[0][15/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_2[1][15/steps[i]] - ans_3[1][15/steps[i+1]])<<endl;
        }
        if(i == 2){
        // for t = 5 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[0][5/steps[i]] - ans_4[0][5/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[1][5/steps[i]] - ans_4[1][5/steps[i+1]])<<endl;
        // for t = 10 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[0][10/steps[i]] - ans_4[0][10/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[1][10/steps[i]] - ans_4[1][10/steps[i+1]])<<endl;
        // for t = 15 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[0][15/steps[i]] - ans_4[0][15/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_3[1][15/steps[i]] - ans_4[1][15/steps[i+1]])<<endl;
        }
        if(i == 3){
        // for t = 5 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[0][5/steps[i]] - ans_5[0][5/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 5 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[1][5/steps[i]] - ans_5[1][5/steps[i+1]])<<endl;
        // for t = 10 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[0][10/steps[i]] - ans_5[0][10/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 10 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[1][10/steps[i]] - ans_5[1][10/steps[i+1]])<<endl;
        // for t = 15 sec
        output_file_RK4_convergence<<"difference between displacements at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[0][15/steps[i]] - ans_5[0][15/steps[i+1]])<<endl;
        output_file_RK4_convergence<<"difference between velocities at the time = 15 sec for step sizes "<<steps[i]<<" and "<<steps[i+1]<<" is "<<abs(ans_4[1][15/steps[i]] - ans_5[1][15/steps[i+1]])<<endl;
        }
    }
    return true;
}
    
int main(){
    vector<vector<real>>ans;
    vector<real>steps;
    real m;
    real a;
    real k;
    real f_0;
    real w;
    real step_size;
    real x_initial = 1;
    real v_initial = 0;
    real interval_length = 15;

    // read the parameters from the input file
    if(!is_readable_file("inputq3.txt",m,a,k,f_0,w,steps)){
        return 1;
    }
    if(steps.size() == 0){
        cout<<"No step sizes provided in the input file"<<endl;
        return 1;
    }
    // create "results" directory if it doesnot exist
    create_results_directory();
    // Generate filename for RK4 method
    string filename_RK4_1 = generatefilename("RK4",to_string(steps[0]));
    string filename_RK4_2 = generatefilename("RK4",to_string(steps[1]));
    string filename_RK4_3 = generatefilename("RK4",to_string(steps[2]));
    string filename_RK4_4 = generatefilename("RK4",to_string(steps[3]));
    string filename_RK4_5 = generatefilename("RK4",to_string(steps[4]));
    string filename_RK4_max_min = generatefilename("RK4","max_min"); 
    string filename_RK4_convergence = generatefilename("RK4","convergence");
    // open the output file for RK4 method
    ofstream output_file_RK4_1(filename_RK4_1);
    if(!output_file_RK4_1.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_1<<endl;
        return 1;
    }
    ofstream output_file_RK4_2(filename_RK4_2);
    if(!output_file_RK4_2.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_2<<endl;
        return 1;
    }
    ofstream output_file_RK4_3(filename_RK4_3);
    if(!output_file_RK4_3.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_3<<endl;
        return 1;
    }
    ofstream output_file_RK4_4(filename_RK4_4);
    if(!output_file_RK4_4.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_4<<endl;
        return 1;
    }
    ofstream output_file_RK4_5(filename_RK4_5);
    if(!output_file_RK4_5.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_5<<endl;
        return 1;
    }
    ofstream output_file_RK4_max_min(filename_RK4_max_min);
    if(!output_file_RK4_max_min.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_max_min<<endl;
        return 1;
    }
    ofstream output_file_RK4_convergence(filename_RK4_convergence);
    if(!output_file_RK4_convergence.is_open()){
        cerr<<"Error in opening output file "<<filename_RK4_convergence<<endl;
        return 1;
    }
    // define the vectors to store the results
    vector<vector<real>>ans_1;
    vector<vector<real>>ans_2;
    vector<vector<real>>ans_3;
    vector<vector<real>>ans_4;
    vector<vector<real>>ans_5;
    // call RK4 method
    for(const auto & step_size : steps){
        if (step_size == steps[0]){
        ans_1 = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
        // write the output to the file
        output_file_RK4_1<<setw(15)<< "Time (in sec)" <<setw(15)<< "Displacement" <<setw(15)<< "Velocity"<<endl;
            for(int i=0;i<ans_1[0].size();i++){
            output_file_RK4_1<<setw(15)<<i*step_size<<setw(15)<<ans_1[0][i]<<setw(15)<<ans_1[1][i]<<endl;
            }   
            cout<<"Results saved to output file "<<filename_RK4_1<<endl;
        }
        if (step_size == steps[1]){
        ans_2 = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
        // write the output to the file
        output_file_RK4_2<<setw(15)<< "Time (in sec)" <<setw(15)<< "Displacement" <<setw(15)<< "Velocity"<<endl;
            for(int i=0;i<ans_2[0].size();i++){
            output_file_RK4_2<<setw(15)<<i*step_size<<setw(15)<<ans_2[0][i]<<setw(15)<<ans_2[1][i]<<endl;
            }   
            cout<<"Results saved to output file "<<filename_RK4_2<<endl;
        }
        if (step_size == steps[2]){
        ans_3 = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
        // write the output to the file
        output_file_RK4_3<<setw(15)<< "Time (in sec)" <<setw(15)<< "Displacement" <<setw(15)<< "Velocity"<<endl;
            for(int i=0;i<ans_3[0].size();i++){
            output_file_RK4_3<<setw(15)<<i*step_size<<setw(15)<<ans_3[0][i]<<setw(15)<<ans_3[1][i]<<endl;
            }   
            cout<<"Results saved to output file "<<filename_RK4_3<<endl;
        }
        if (step_size == steps[3]){
        ans_4 = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
        // write the output to the file
        output_file_RK4_4<<setw(15)<< "Time (in sec)" <<setw(15)<< "Displacement" <<setw(15)<< "Velocity"<<endl;
            for(int i=0;i<ans_4[0].size();i++){
            output_file_RK4_4<<setw(15)<<i*step_size<<setw(15)<<ans_4[0][i]<<setw(15)<<ans_4[1][i]<<endl;
            }   
            cout<<"Results saved to output file "<<filename_RK4_4<<endl;
        }
        if (step_size == steps[4]){
        ans_5 = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
        // write the output to the file
        output_file_RK4_5<<setw(15)<< "Time (in sec)" <<setw(15)<< "Displacement" <<setw(15)<< "Velocity"<<endl;
            for(int i=0;i<ans_5[0].size();i++){
            output_file_RK4_5<<setw(15)<<i*step_size<<setw(15)<<ans_5[0][i]<<setw(15)<<ans_5[1][i]<<endl;
            }   
            cout<<"Results saved to output file "<<filename_RK4_5<<endl;
        }
    }
    cout<<"Convergence of RK4 method is as follows:"<<endl;
    // write the output of differences in displacements and velocities to the file
    if(check_convergence(ans_1,ans_2,ans_3,ans_4,ans_5,steps,output_file_RK4_convergence)){
        cout<<"Convergence results written to "<<filename_RK4_convergence<<endl;
        cout<<"Convergence independent of results"<<endl;
    }
    // find max and min values of displacement and velocity   
    step_size = steps[4];
    ans = RK4({m,a,k,f_0,w},f1,f2,step_size,interval_length,x_initial,v_initial);
    // create the vector to store max and min values
    vector<pair<real,real>>max_values;
    vector<pair<real,real>>min_values;
    // find max and min values
    max_values = find_max(ans,step_size,max_values);
    min_values = find_min(ans,step_size,min_values);
    // write the max and min values to the file
    output_file_RK4_max_min<<"maximum and minimum values of displacement and velocity are as follows:"<<endl;
    output_file_RK4_max_min<<"maximum value of displacement is x = "<<max_values[0].second<<" at time t = "<<max_values[0].first<<endl;
    output_file_RK4_max_min<<"minimum value of displacement is x = "<<min_values[0].second<<" at time t = "<<min_values[0].first<<endl;
    output_file_RK4_max_min<<"maximum value of velocity is v = "<<max_values[1].second<<" at time t = "<<max_values[1].first<<endl;
    output_file_RK4_max_min<<"minimum value of velocity is v = "<<min_values[1].second<<" at time t = "<<min_values[1].first<<endl;
    cout<<"Max and min values written to "<<filename_RK4_max_min<<endl;
    // close the output file
    if (output_file_RK4_1.is_open()) output_file_RK4_1.close();
    if (output_file_RK4_2.is_open()) output_file_RK4_2.close();
    if (output_file_RK4_3.is_open()) output_file_RK4_3.close();
    if (output_file_RK4_4.is_open()) output_file_RK4_4.close();
    if (output_file_RK4_5.is_open()) output_file_RK4_5.close();
    if (output_file_RK4_max_min.is_open()) output_file_RK4_max_min.close();
    if (output_file_RK4_convergence.is_open()) output_file_RK4_convergence.close();
    return 0;
}