# Numerical Methods Assignment-1   

## Description  
This assignment covers numerical solutions for ODEs using Explicit and Implicit Euler's Method, Family of Runge-Kutta Methods, and Adams-Bashforth second order methods. The goal is to compare their accuracy and stability and to learn their implementations.  

## Prerequisites 
- knowedge of numerical methods used for solving ODE.
- Python 
- c++
- NumPy and Matplotlib.
- scipy.
- sympy.

## File Structure  
# DS289_A1_Parikshit_Mahajan

## File Structure  

- The main directory, **DS289_A1_Parikshit_Mahajan**, contains four subdirectories, each corresponding to a question (**q1, q2, q3, q4**).  

### **Subdirectory: q1**  
- Contains code using the **SymPy** library to solve a linear system of equations for Question 1.  
- Includes two output files storing the results.  

### **Subdirectories: q2, q3, and q4**  
Each of these subdirectories follows a similar structure:  
- 📂 **results/** → Stores output files containing numerical results.  
- 📂 **figures/** → Stores generated plots.  
- 📜 **Python notebook** → Used for result analysis and visualization.  
- ⚙️ **Makefile** → Automates compilation and execution.  
- 📄 **utils.h** → Header file containing function declarations for numerical methods.  
- 🖋️ **utils.cpp** → Implements the functions declared in "utils.h".  
- 📄 **input.txt** → Contains input data required for computations.  
- 🚀 **main.cpp** → The main program that executes all subparts of the question. It reads input, performs computations, and writes results to files.  

This structured organization ensures clear separation of code, data, and results for better maintainability and execution. 

## Methods Used  
- Explicit Euler Method  
- Implicit Euler Method
- Runge-Kutta (4th order)
- Runge-Kutta (2nd order)  
- Adams-Bashforth (2nd order)  

## Acknowledgment  
I acknowledge the use of ChatGPT and GitHub Copilot for code snippet support.  

## References  
- Numerical Methods for Engineers, Chapra & Canale.
- Lecture notes on ODE part.
- Numerical Analysis by Richard L. Burdern ,J.Douglas Faires.
