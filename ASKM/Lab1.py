import numpy as np
import re
import sys

float_val = re.compile(r"[-+]?(?:\d*\.\d+|\d+)")
int_val = re.compile(r"\d+")


def int_input(input_text):
    """
    Validating the string for conversion to integer
    :param input_text: str, user-inputed text to be validated
    :return: int, text of user converted to integer
    """
    if re.fullmatch(int_val, input_text):
        return int(input_text)
    else:
        new = input("Wrong format. Print integer number: ")
        return int_input(new)


def float_input(input_text):
    """
    Validating the string for conversion to float
    :param input_text: str, user-inputed text to be validated
    :return: float, text of user converted to float
    """
    if re.fullmatch(float_val, input_text):
        return float(input_text)
    else:
        new = input("Wrong format. Print float number: ")
        return float_input(new)


# Example augmented matrix for var 8
example_a = np.array([[2.12, 0.42, 1.34, 0, 11.172],
                      [0.42, 3.95, 1.87, 0, 0.115],
                      [1.34, 1.87, 2.98, 0, 9.009],
                      [0.88, 0.43, 0.46, 0, 11.172]], dtype=float)
# Example augmented matrix, that has solution
working_a = np.array([[1, 1, 1, 9],
                      [2, -3, 4, 13],
                      [3, 4, 5, 40]], dtype=float)

# Length of the future solution vector for example matrix
n_example = len(example_a[0]) - 1
# Length of the future solution vector for working matrix
n_working = len(working_a[0]) - 1


def gauss_methode(a, n):
    """
    Gauss methode for computation the solution for simultaneous equations
    :param a: np.array(float), 2-d matrix with system coefficients
    :param n: int, number of unknowns
    :return:
    """
    solution_check_mx = a[0:n, 0:n].copy()
    solution_check_v = a[0:n, -1].copy()
    # Solution vector base for example matrix
    v = np.zeros(n)
    has_solution = True
    # Elimination phase
    for i in range(n):
        # Not possible to find the lambda in this case
        if a[i][i] == 0.0:
            has_solution = False
            break

        for j in range(i + 1, n):
            lamd = a[j][i] / a[i][i]

            for k in range(n + 1):
                # Accuracy level is agreed here
                a[j][k] = round(a[j][k] - lamd * a[i][k], 6)
        # In case of (0, 0, ...; b), where b is augmented part and !0 claims that simultaneous eq don't have solution
        if np.count_nonzero(a[i]) == 1 and a[i][-1] != 0:
            has_solution = False
            break

    # Back Substitution
    if has_solution:
        v[n - 1] = a[n - 1][n] / a[n - 1][n - 1]

        for i in range(n - 2, -1, -1):
            v[i] = a[i][n]

            for j in range(i + 1, n):
                v[i] = v[i] - a[i][j] * v[j]

            v[i] = v[i] / a[i][i]
        print("Error =", np.max((abs(np.linalg.solve(solution_check_mx, solution_check_v) - v))))
        return f"Solution for these simultaneous equations are: ", v
    else:
        return "No solution for this simultaneous equations. Or system has endless number of solutions."


def custom_matrix():
    """
    Creation of custom matrix by user
    """
    size = int_input(input("Enter size of the linear system: "))
    mx_a = np.zeros((size, size + 1))
    for i in range(size):
        for j in range(size + 1):
            mx_a[i][j] = float_input(input("Enter a[{}][{}]: ".format(i, j)))

    print(gauss_methode(mx_a, size))
    print(mx_a)


is_exit = False
while not is_exit:
    print("Choose the option:")
    choice = input("Calculate the 1 - Example Matrix; 2 - Working Matrix; 3 - Custom matrix; 4 - Exit the program:")
    if choice == "1":
        print(gauss_methode(example_a, n_example))
        print(example_a)
    elif choice == "2":
        print(gauss_methode(working_a, n_working))
        print(working_a)
    elif choice == "3":
        custom_matrix()
    elif choice == "4":
        sys.exit()
    else:
        print("Incorrect input")
