def antiderivative(x):
    """
    Antiderivative function for Variant 8
    :param x: float, function variable
    :return: function value for assigned variable
    """
    return (2*(x+2)**(3/2)*(15*x**2-24*x+32))/105


def func(x):
    """
    Derivative function of the given function
    :param x: float, function variable
    :return: function value for assigned variable
    """
    return pow(x, 2)*pow(x+2, 0.5)


def coordinate_sequences(a, n, h):
    """
    Function returns arrays with coordinate sequences X, Y for the established h-step
    :param a: float, the beginning of interval for function interpolation
    :param n: number of interpolation knots
    :param h: constant step
    :return: arrays, X, Y coordinate sequences
    """
    x_values = [round(a + h * i, 2) for i in range(n + 1)]
    y_values = [antiderivative(x) for x in x_values]
    return x_values, y_values


def lagrange_rule(y, n, h):
    """
    Function calculating derivatives for the interpolation knots, using Lagrange Rule
    :param y: array of float; sequence of interpolation knots
    :param n: number of interpolation knots
    :param h: constant step
    :return: array of calculated derivatives at points
    """
    result = [(1 / (2 * h)) * (-3 * y[0] + 4 * y[1] - y[2])]
    for i in range(1, n):
        result.append((1 / (2 * h)) * (y[i + 1] - y[i - 1]))
    result.append((1 / (2 * h)) * (y[n - 2] - 4 * y[n - 1] + 3 * y[n]))
    return result


def simpson_rule(y, h):
    """
    Function to calculate integral sum by Simpson Rule
    :param y: array of float; sequence of interpolation knots
    :param h: constant step
    :return: float, integral sum, calculated by Simpson Formula
    """
    # first value + last value + doubled even values + quadrupled odd values
    return h/3 * sum(y[0:-1:2] + 4*y[1::2] + y[2::2])


def absolute_error_calculation(x1, x2):
    return [sum(abs(x1[i] - x2[i])for i in range(len(x1)))][0]


def main():
    # Start-point of interpolation interval
    a = 1
    # End-point of interpolation interval
    b = 4
    # Number of interpolation knots
    n = 50
    # Constant step between interpolation knots
    h = 0.06

    interval = [a, b]
    x, y = coordinate_sequences(interval[0], n, h)

    # Local Derivatives calculated by Lagrange Rule
    lagrange_rule_result = lagrange_rule(y, n, h)
    # Local Derivatives found directly from formula
    derivative_formula_result = [func(el) for el in x]

    print(f"Result found directly from by Lagrange Rule: {lagrange_rule_result}")
    print(f"Result found directly from f formula: {derivative_formula_result}")
    print(f"Absolute error between results equals to: {absolute_error_calculation(lagrange_rule_result, derivative_formula_result)}")

    # Integral Sum calculated by Simpson Rule
    simpson_result = simpson_rule(derivative_formula_result, h)
    # Integral Sum calculated by Newton-Leibniz Formula
    newton_leibniz_result = antiderivative(b) - antiderivative(a)

    print(f"Integral Sum calculated by Simpson Rule: {simpson_result}")
    print(f"Integral Sum calculated by Newton-Leibniz Formula: {newton_leibniz_result}")
    print(f"Absolute error between results equals to: {abs(simpson_result - newton_leibniz_result)}")


main()
