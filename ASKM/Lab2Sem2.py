import numpy as np
from scipy import optimize
import matplotlib.pyplot as plt

x_given = np.array([0, 1, 2, 3, 4, 5])
y_given = np.array([6.2, 11.6, 22.4, 35.4, 54.8, 75.2])


def exp_func(x, a, b, c):
    return a * np.exp(b * x) + c


def plotting_results(x, y):
    ax = plt.axes()
    ax.scatter(x_given, y_given, label='Raw data')
    ax.plot(x, y, 'k', label='Fitted curve')
    ax.set_title(r'Fitting a given-function with an exponential function')
    ax.set_ylabel('y-Values')
    ax.set_ylim(0, 100)
    ax.set_xlabel('x-Values')
    ax.legend()
    plt.show()


def main():
    # Fit the function a * np.exp(b * t) + c to x and y
    popt, _ = optimize.curve_fit(exp_func, x_given, y_given)
    a = popt[0]
    b = popt[1]
    c = popt[2]
    # print the optimized parameters
    print(f'Optimized Parameters: a = {a}, b = {b}, c = {c}')

    # Create the fitted curve
    x_fitted = np.linspace(np.min(x_given), np.max(x_given), 100)
    y_fitted = exp_func(x_fitted, a, b, c)
    # Create the fitted x-values
    y_fitted_error_calculation = exp_func(x_given, a, b, c)
    # Calculate the maximum absolute error and relative error
    max_abs_error = np.max(np.abs(y_fitted_error_calculation - y_given))
    print(f'Absolute Error:{max_abs_error}')
    # calculate the error of approximation
    relative_error = np.max(np.abs(y_fitted_error_calculation - y_given) / np.abs(y_given))
    print(f'Relative Error:{relative_error}')

    plotting_results(x_fitted, y_fitted)


main()
