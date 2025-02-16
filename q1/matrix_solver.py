import numpy as np
from scipy.linalg import solve
import sympy as sp

# Define symbols
c1, c2, c3, c4 = sp.symbols('c1 c2 c3 c4')
dx1, dx2, dx3 = sp.symbols('dx1 dx2 dx3')
p, q, r = sp.symbols('p q r')

# Express the dx1, dx2, dx3 in terms of p, q, r
dx1_subs = p
dx2_subs = q - p
dx3_subs = r - q
# Define the coefficient matrix
A = sp.Matrix([
    [1, 1, 1, 1],
    [0, dx1, dx1+dx2, dx1+dx2+dx3],
    [0, dx1**2, (dx1+dx2)**2, (dx1+dx2+dx3)**2],
    [0, dx1**3, (dx1+dx2)**3, (dx1+dx2+dx3)**3]
])
# Define the right-hand side vector
b = sp.Matrix([0, 0, 2, 0])
# Solve the linear system
solution = sp.linsolve((A, b))
# Substitute dx1, dx2, dx3 in terms of p, q, r
solution_pqr = {var: sol.subs({dx1: dx1_subs, dx2: dx2_subs, dx3: dx3_subs}).simplify()
                for var, sol in zip([c1, c2, c3, c4], next(iter(solution)))}
# Print the solution in terms of p, q, r
for var, sol in solution_pqr.items():
    print(f"{var} = {sol}")
# Save the solution to a file
output_file_path_pqr = "matrix_solution_output_pqr.txt"
with open(output_file_path_pqr, "w") as file:
    for var, sol in solution_pqr.items():
        file.write(f"{var} = {sol}\n")
#  Display the solution neatly
output = []
for sol in solution:
    output.append(f"c1 = {sol[0].simplify()}")
    output.append(f"c2 = {sol[1].simplify()}")
    output.append(f"c3 = {sol[2].simplify()}")
    output.append(f"c4 = {sol[3].simplify()}")
# Print the solution
for line in output:
    print(line)
# Save the solution to a file
output_file_path = "matrix_solution_output.txt"
with open(output_file_path, "w") as file:
    for line in output:
        file.write(line + "\n")

