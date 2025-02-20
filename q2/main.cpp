#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<sstream>
#include<filesystem>
#include "utils.h"
using namespace std;
// Define the function equivalent to derivative
real given_function(real t , real y){
    return y*(t*t - 1.1);
}
// Function to read the parameters from an input file
bool is_readable_file(const string& filename, vector<real>&steps, vector<string>& methods){
    ifstream input_file(filename);
    if(!input_file.is_open()){
        cout<<"Opening error for input_file"<<endl;
        return false;
    }
    string line;
    while(getline(input_file, line)){
        stringstream ss(line);
        string method;
        ss >> method;
        if(method == "Explicit_Euler_method"){
            methods.push_back(method);
            string str;
            ss >> str;
            if(str == "step_size"){
                real step_size;
                while(ss >> step_size){
                    steps.push_back(step_size);
                }
            }    
        }
        if(method == "Second_order_Adam_Bashforth_method"){
            methods.push_back(method);
            // ss.clear();
        }
        if (method == "Runge_Kutta_2nd_order_method") {
            methods.push_back(method);
        }
    }
    input_file.close();
    return true;
}

//  create results folder .i.e. directory
void create_results_directory(){
    if(! filesystem:: exists("results")){
        filesystem:: create_directory("results");
        cout<<"Results directory created"<<endl;
    }
}
// Create result folder and save the each method output to different txt files
string generatefilename(const string& name){
        ostringstream oss;
        oss << "results/output_"<<name<<".txt";
        return oss.str();
}
int main(){
    vector<string>methods;
    vector<real>steps;
    real step_size;
    real y_initial = 1;
    int interval_length = 2;
   
    if(!is_readable_file("input.txt",steps,methods)){
        return 1;
    }
    // create "results" directory if it doesnot exist
    create_results_directory();
     // Generate filenames for each method
     string filename;
     string filename_AB;
     string filename_RK;
     for (const auto& method : methods) {
         if (method == "Explicit_Euler_method") {
             filename = generatefilename(method);
         } else if (method == "Second_order_Adam_Bashforth_method") {
             filename_AB = generatefilename(method);
         }
         else if (method == "Runge_Kutta_2nd_order_method") {
             filename_RK = generatefilename(method);
         }
     } 
    // open the output file for Explicit Euler method
    ofstream output_file(filename);
    if(!output_file.is_open()){
        cerr<<"Error in opening output file "<<filename<<endl;
        return 1;
    }
    // open the output file for Adam-Bashforth method
    ofstream output_file_AB(filename_AB);
    if(!output_file_AB.is_open()){
        cerr<<"Error in opening output file "<<filename_AB<<endl;
        return 1;
    }
    // open the output file for Runge-Kutta 2nd order method
    ofstream output_file_RK(filename_RK);
    if(!output_file_RK.is_open()){
        cerr<<"Error in opening output file "<<filename_RK<<endl;
        return 1;
    }
    //   loop over the step_size for each method
    for (const auto& method : methods){
      for(int i=0;i<steps.size();i++){
        step_size = steps[i];
        if(method == "Explicit_Euler_method"){
            vector<real> y_euler_final;
            y_euler_final = exp_Euler(given_function, step_size,interval_length,y_initial);
            for(int k=0;k<y_euler_final.size();k++){
                output_file << "Numerical solution by "<< method<<"for the step_size "<<step_size<<" for the grid point "<< k*step_size <<" is: " <<y_euler_final[k]<<endl;
            }
            //  create a new line for each step_size
            output_file << endl;
            cout<< "Results saved to output file "<<endl;
        }
        if(method == "Second_order_Adam_Bashforth_method"){
            vector<real> y_AB2_final;
            y_AB2_final = AB2(given_function, step_size,interval_length,y_initial);
            for(int j=0;j<y_AB2_final.size();j++){
                output_file_AB << "Numerical solution by "<< method<<"for the step_size "<<step_size<<" for the grid point "<< j*step_size <<" is: " <<y_AB2_final[j]<<endl;
            }
            //  create a new line for each step_size
            output_file_AB << endl;
            cout<< "Results saved to output file AB "<<endl;
        }
        if(method == "Runge_Kutta_2nd_order_method"){
            vector<real> y_RK2_final;
            y_RK2_final = RK2(given_function, step_size,interval_length,y_initial);
            for(int j=0;j<y_RK2_final.size();j++){
                output_file_RK << "Numerical solution by "<< method<<"for the step_size "<<step_size<<" for the grid point "<< j*step_size <<" is: " <<y_RK2_final[j]<<endl;
            }
            //  create a new line for each step_size
            output_file_RK << endl;
            cout<< "Results saved to output file RK "<<endl;
        }
      }
    } 
    // Close files
    if (output_file.is_open()) output_file.close();
    if (output_file_AB.is_open()) output_file_AB.close();
    if (output_file_RK.is_open()) output_file_RK.close();
    return 0;
}