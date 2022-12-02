def func(x):
    """
    Function for Variant 8
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
    y_values = [func(x) for x in x_values]
    return x_values, y_values


def derivative(x):
    """
    Derivative function of the given function
    :param x: float, function variable
    :return: function value for assigned variable
    """
    return (x*(5*x + 8))/(2*pow(x+2, 0.5))


def integral(x):
    """
    Integral function of the given function
    :param x: float, function variable
    :return: function value for assigned variable
    """
    return (2*(x+2)**(3/2)*(15*x**2-24*x+32))/105


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


def simpson_rule(x, h):
    """
    Function to calculate integral sum by Simpson Rule
    :param x: array of float; sequence of interpolation knots
    :param h: constant step
    :return: float, integral sum, calculated by Simpson Formula
    """
    # first value + last value + doubled even values + quadrupled odd values
    return h/3 * sum(x[0:-1:2] + 4*x[1::2] + x[2::2])


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
    # Integral Sum calculated by Simpson Rule
    print(simpson_rule(y, h))
    # Integral Sum calculated by Newton-Leibniz Formula
    print(integral(b) - integral(a))

    # Local Derivatives calculated by Lagrange Rule
    print(lagrange_rule(y, n, h))
    # Local Derivatives found directly from formula
    print([derivative(el) for el in x])


main()
