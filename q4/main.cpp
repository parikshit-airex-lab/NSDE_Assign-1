#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<sstream>
#include<filesystem>
#include<iomanip>
#include<string>
#include "utils.h"
using namespace std;

// Define the function equivalent to derivative
real given_function(real x , real y){
    return -1000*y + 1000*exp(-x) - exp(-x);
}
//  derivative of the given_function
real given_function_yprime(real x, real y){
    return -1000;
}
// Function to read the parameters from an input file
bool is_readable_file(const string& filename, vector<real>&steps, vector<string>& methods , vector<real>&IC){
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
        if(method == "method"){
            string method_name;
            while(ss >> method_name)
            methods.push_back(method_name);
        }
        if(method == "step_size"){
            real step;
            while(ss >> step)
            steps.push_back(step);
        }
        if(method == "IC"){
            real IC_value;
            while(ss >> IC_value)
            IC.push_back(IC_value);
        }
    }
    input_file.close();
    return true;
}

// create results folder .i.e. directory
void create_results_directory(){
    if(! filesystem:: exists("resultsq4")){
        filesystem:: create_directory("resultsq4");
        cout<<"Results directory created"<<endl;
    }
}

// Create result folder and save the each method output to different txt files
string generatefilename(const string& name, const string& step, const string& IC_name){
        ostringstream oss;
        oss << "resultsq4/output_"<<name<<"_step_"<<step<<"_IC_"<<IC_name<<".txt";
        return oss.str();
}

int main(){
    vector<string>methods;
    vector<real>steps;
    vector<real>IC;
    real step_size;
    real y_initial;
    real y_initial_1;
    real interval_length = 2;
    real tol = 1e-7;
    int max_iter = 1000;
    if(!is_readable_file("inputq4.txt",steps,methods,IC)){
        return 1;
    }
    cout<<"Input file read successfully"<<endl;
    y_initial = IC[0];
    y_initial_1 = IC[1];
    cout<<"Initial conditions are "<<y_initial<<" and "<<y_initial_1<<endl;
    cout<<"Step sizes are "<<steps[0]<<", "<<steps[1]<<" and "<<steps[2]<<endl;
    cout<<"Methods are "<<methods[0]<<" and "<<methods[1]<<endl;
    // create "results" directory if it doesnot exist
    create_results_directory();
    // Generate filename for each method
    string filename_1e = generatefilename("Explicit_Euler",to_string(steps[0]), to_string(IC[0]));
    string filename_2e = generatefilename("Explicit_Euler",to_string(steps[0]), to_string(IC[1]));
    string filename_3e = generatefilename("Explicit_Euler",to_string(steps[1]), to_string(IC[0]));
    string filename_4e = generatefilename("Explicit_Euler",to_string(steps[1]), to_string(IC[1]));
    string filename_5e = generatefilename("Explicit_Euler",to_string(steps[2]), to_string(IC[0]));
    string filename_6e = generatefilename("Explicit_Euler",to_string(steps[2]), to_string(IC[1]));
    string filename_1i = generatefilename("Implicit_Euler",to_string(steps[0]), to_string(IC[0]));
    string filename_2i = generatefilename("Implicit_Euler",to_string(steps[0]), to_string(IC[1]));
    string filename_3i = generatefilename("Implicit_Euler",to_string(steps[1]), to_string(IC[0]));
    string filename_4i = generatefilename("Implicit_Euler",to_string(steps[1]), to_string(IC[1]));
    string filename_5i = generatefilename("Implicit_Euler",to_string(steps[2]), to_string(IC[0]));
    string filename_6i = generatefilename("Implicit_Euler",to_string(steps[2]), to_string(IC[1]));
    // open the output file for Explicit Euler method
    ofstream output_file_1e(filename_1e);
    if(!output_file_1e.is_open()){
        cerr<<"Error in opening output file "<<filename_1e<<endl;
        return 1;
    }
    ofstream output_file_2e(filename_2e);
    if(!output_file_2e.is_open()){
        cerr<<"Error in opening output file "<<filename_2e<<endl;
        return 1;
    }
    ofstream output_file_3e(filename_3e);
    if(!output_file_3e.is_open()){
        cerr<<"Error in opening output file "<<filename_3e<<endl;
        return 1;
    }
    ofstream output_file_4e(filename_4e);
    if(!output_file_4e.is_open()){
        cerr<<"Error in opening output file "<<filename_4e<<endl;
        return 1;
    }
    ofstream output_file_5e(filename_5e);
    if(!output_file_5e.is_open()){
        cerr<<"Error in opening output file "<<filename_5e<<endl;
        return 1;
    }
    ofstream output_file_6e(filename_6e);
    if(!output_file_6e.is_open()){
        cerr<<"Error in opening output file "<<filename_6e<<endl;
        return 1;
    }
    // open the output file for Implicit Euler method
    ofstream output_file_1i(filename_1i);
    if(!output_file_1i.is_open()){
        cerr<<"Error in opening output file "<<filename_1i<<endl;
        return 1;
    }
    ofstream output_file_2i(filename_2i);
    if(!output_file_2i.is_open()){
        cerr<<"Error in opening output file "<<filename_2i<<endl;
        return 1;
    }
    ofstream output_file_3i(filename_3i);
    if(!output_file_3i.is_open()){
        cerr<<"Error in opening output file "<<filename_3i<<endl;
        return 1;
    }
    ofstream output_file_4i(filename_4i);
    if(!output_file_4i.is_open()){
        cerr<<"Error in opening output file "<<filename_4i<<endl;
        return 1;
    }
    ofstream output_file_5i(filename_5i);
    if(!output_file_5i.is_open()){
        cerr<<"Error in opening output file "<<filename_5i<<endl;
        return 1;
    }
    ofstream output_file_6i(filename_6i);
    if(!output_file_6i.is_open()){
        cerr<<"Error in opening output file "<<filename_6i<<endl;
        return 1;
    }
    // define the vectors to store the results
    vector<real>ans_1e;
    vector<real>ans_2e;
    vector<real>ans_3e;
    vector<real>ans_4e;
    vector<real>ans_5e;
    vector<real>ans_6e;
    vector<real>ans_1i;
    vector<real>ans_2i;
    vector<real>ans_3i;
    vector<real>ans_4i;
    vector<real>ans_5i;
    vector<real>ans_6i;
  cout<<"code reached here"<<endl;
    //   loop over the step_size for each method
    for(const auto & method : methods){
      for(int i=0;i<steps.size();i++){
        if(method == "Explicit_Euler_method"){
            if(steps[i] == steps[0]){
                ans_1e = exp_Euler(given_function, steps[i], interval_length, y_initial);
                ans_2e = exp_Euler(given_function, steps[i], interval_length, y_initial_1);
                output_file_1e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_2e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_1e.size();k++){
                    output_file_1e<<setw(15)<<k*steps[i]<<setw(15)<<ans_1e[k]<<endl;
                    output_file_2e<<setw(15)<<k*steps[i]<<setw(15)<<ans_2e[k]<<endl;
                }
                cout<<"Results saved to output file "<<filename_1e<<endl;
                cout<<"Results saved to output file "<<filename_2e<<endl;
            }
            if(steps[i] == steps[1]){
                ans_3e = exp_Euler(given_function, steps[i], interval_length, y_initial);
                ans_4e = exp_Euler(given_function, steps[i], interval_length, y_initial_1);
                output_file_3e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_4e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_3e.size();k++){
                    output_file_3e<<setw(15)<<k*steps[i]<<setw(15)<<ans_2e[k]<<endl;
                    output_file_4e<<setw(15)<<k*steps[i]<<setw(15)<<ans_2e[k]<<endl;
                }
                cout<<"Results saved to output file "<<filename_3e<<endl;
                cout<<"Results saved to output file "<<filename_4e<<endl;
            }
            if(steps[i] == steps[2]){
                ans_5e = exp_Euler(given_function, steps[i], interval_length, y_initial);
                ans_6e = exp_Euler(given_function, steps[i], interval_length, y_initial_1);
                output_file_5e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_6e<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_5e.size();k++){
                    output_file_5e<<setw(15)<<k*steps[i]<<setw(15)<<ans_3e[k]<<endl;
                    output_file_6e<<setw(15)<<k*steps[i]<<setw(15)<<ans_4e[k]<<endl;
                }
                cout<<"Results saved to output file "<<filename_5e<<endl;
                cout<<"Results saved to output file "<<filename_6e<<endl;
            }
        }
        if(method == "Implicit_Euler_method"){
            if(steps[i] == steps[0]){
                ans_1i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial, tol, max_iter);
                ans_2i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial_1, tol, max_iter);
                output_file_1i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_2i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_1i.size();k++){
                output_file_1i<<setw(15)<<k*steps[i]<<setw(15)<<ans_1i[k]<<endl;
                output_file_2i<<setw(15)<<k*steps[i]<<setw(15)<<ans_2i[k]<<endl;
                }   
                cout<<"Results saved to output file "<<filename_1i<<endl;
                cout<<"Results saved to output file "<<filename_2i<<endl;
            }
            if(steps[i] == steps[1]){
                ans_3i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial, tol, max_iter);
                ans_4i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial_1, tol, max_iter);
                output_file_3i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_4i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_3i.size();k++){
                output_file_3i<<setw(15)<<k*steps[i]<<setw(15)<<ans_3i[k]<<endl;
                output_file_4i<<setw(15)<<k*steps[i]<<setw(15)<<ans_4i[k]<<endl;
                }   
                cout<<"Results saved to output file "<<filename_3i<<endl;
                cout<<"Results saved to output file "<<filename_4i<<endl;
            }
            if(steps[i]==steps[2]){
                ans_5i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial, tol, max_iter);
                ans_6i = imp_Euler(given_function, given_function_yprime, steps[i], interval_length, y_initial_1, tol, max_iter);
                output_file_5i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                output_file_6i<<setw(15)<< "step_size" <<setw(15)<< "function value"<<endl;
                for(int k=0;k<ans_5i.size();k++){
                output_file_5i<<setw(15)<<k*steps[i]<<setw(15)<<ans_5i[k]<<endl;
                output_file_6i<<setw(15)<<k*steps[i]<<setw(15)<<ans_6i[k]<<endl;
                }   
                cout<<"Results saved to output file "<<filename_5i<<endl;
                cout<<"Results saved to output file "<<filename_6i<<endl;
            }
        }
      }
    }
    //close the output files
    if (output_file_1e.is_open()) output_file_1e.close();
    if (output_file_2e.is_open()) output_file_2e.close();
    if (output_file_3e.is_open()) output_file_3e.close();
    if (output_file_4e.is_open()) output_file_4e.close();
    if (output_file_5e.is_open()) output_file_5e.close();
    if (output_file_6e.is_open()) output_file_6e.close();
    if (output_file_1i.is_open()) output_file_1i.close();
    if (output_file_2i.is_open()) output_file_2i.close();
    if (output_file_3i.is_open()) output_file_3i.close();
    if (output_file_4i.is_open()) output_file_4i.close();
    if (output_file_5i.is_open()) output_file_5i.close();
    if (output_file_6i.is_open()) output_file_6i.close();
    return 0;

}