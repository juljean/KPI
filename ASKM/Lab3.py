import numpy as np
import pandas as pd
from tabulate import tabulate
import matplotlib.pyplot as plt
from scipy.integrate import odeint

# Given values for Variant 8
dif_eq = lambda x, y_, y__: (-1 - pow(y_, 2)) / (1 + pow(x, 2))
F = lambda x, y, y_: y_
a = 0
b = 0.5
y0 = 1
y0_ = 1


def rk4_1(x, y, y_, h=0.05):
    k0 = h * F(x, y, y_)
    k0_ = h * dif_eq(x, y, y_)
    k1 = h * F(x + h / 2, y + k0 / 2, y_ + k0_ / 2)
    k1_ = h * dif_eq(x + h / 2, y + k0 / 2, y_ + k0_ / 2)
    k2 = h * F(x + h / 2, y + k0 / 2, y_ + k0_ / 2)
    k2_ = h * dif_eq(x + h / 2, y + k0 / 2, y_ + k0_ / 2)
    k3 = h * F(x + h, y + k2, y_ + k2_)
    k3_ = h * dif_eq(x + h, y + k2, y_ + k2_)
    y = y + (k0 + 2 * k1 + 2 * k2 + k3) / 6
    y_ = y_ + (k0_ + 2 * k1_ + 2 * k2_ + k3_) / 6
    return y, y_


def rk4_2(x, y, y_, h=0.05):
    k0 = h * F(x, y, y_)
    k0_ = h * dif_eq(x, y, y_)
    k1 = h * F(x + h / 4, y + k0 / 4, y_ + k0_ / 4)
    k1_ = h * dif_eq(x + h / 4, y + k0 / 4, y_ + k0_ / 4)
    k2 = h * F(x + h / 2, y + k1 / 2, y_ + k1_ / 2)
    k2_ = h * dif_eq(x + h / 2, y + k1 / 2, y_ + k1_ / 2)
    k3 = h * F(x + 2 * h / 3, y + k0 - 2 * k1 + 2 * k2, y_ + k0_ - 2 * k1_ + 2 * k2_)
    k3_ = h * dif_eq(x + 2 * h / 3, y + k0 - 2 * k1 + 2 * k2, y_ + k0_ - 2 * k1_ + 2 * k2_)
    y = y + (k0 + 2 * k1 + 2 * k2 + k3) / 6
    y_ = y_ + (k0_ + 2 * k1_ + 2 * k2_ + k3_) / 6
    return y, y_


def rk3(x, y, y_, h=0.05):
    k0 = h * F(x, y, y_)
    l0 = h * dif_eq(x, y, y_)
    k1 = h * F(x + h / 2, y + k0 / 2, y_ + l0 / 2)
    l1 = h * dif_eq(x + h / 2, y + k0 / 2, y_ + l0 / 2)
    k2 = h * F(x + h, y - k0 + 2 * k1, y_ - l0 + 2 * l1)
    l2 = h * dif_eq(x + h, y - k0 + 2 * k1, y_ - l0 + 2 * l1)
    y = y + (k0 + 4 * k1 + k2) / 6
    y_ = y_ + (l0 + 4 * l1 + l2) / 6

    return y, y_


def rk2_1(x, y, y_, h=0.05):
    k0 = h * F(x, y, y_)
    l0 = h * dif_eq(x, y, y_)
    k1 = h * F(x + h, y + k0, y_ + l0 / 2)
    l1 = h * dif_eq(x + h, y + k0, y_ + l0 / 2)
    y = y + (k0 + k1) / 2
    dy = y_ + (l0 + l1) / 2
    return y, dy


def rk2_2(x, y, y_, h=0.05):
    k0 = h * F(x, y, y_)
    l0 = h * dif_eq(x, y, y_)
    k1 = h * F(x + h / 2, y + k0 / 2, y_ + l0 / 2)
    l1 = h * dif_eq(x + h / 2, y + k0 / 2, y_ + l0 / 2)
    y = y + (k0 + k1) / 2
    dy = y_ + (l0 + l1) / 2
    return y, dy


def calculation(h=0.05):
    x_points = np.arange(a, b + h, h)
    # Starting values for function in a range
    y_points_2_1, y_points_2_2, y_points_3, y_points_4_1, y_points_4_2 = [y0], [y0], [y0], [y0], [y0]
    dy_points_2_1, dy_points_2_2, dy_points_3, dy_points_4_1, dy_points_4_2 = [y0_], [y0_], [y0_], [y0_], [y0_]
    # Calculation with the ready tools
    function_de = lambda ys, x: (F(x, ys[0], ys[1]), dif_eq(x, ys[0], ys[1]))
    y_answers = odeint(function_de, [y0, y0_], x_points)[:, 0]

    for i in range(0, len(x_points) - 1):
        value_2_1 = rk2_1(x_points[i], y_points_2_1[i], dy_points_2_1[i], h)
        y_points_2_1.append(value_2_1[0]), dy_points_2_1.append(value_2_1[1])

        value_2_2 = rk2_2(x_points[i], y_points_2_2[i], dy_points_2_2[i], h)
        y_points_2_2.append(value_2_2[0]), dy_points_2_2.append(value_2_2[1])

        value_3 = rk3(x_points[i], y_points_3[i], dy_points_3[i], h)
        y_points_3.append(value_3[0]), dy_points_3.append(value_3[1])

        value_4_1 = rk4_1(x_points[i], y_points_4_1[i], dy_points_4_1[i], h)
        y_points_4_1.append(value_4_1[0]), dy_points_4_1.append(value_4_1[1])

        value_4_2 = rk4_2(x_points[i], y_points_4_2[i], dy_points_4_2[i], h)
        y_points_4_2.append(value_4_2[0]), dy_points_4_2.append(value_4_2[1])

    df_results = pd.DataFrame({'x': x_points,
                              'y2_1': y_points_2_1,
                              'error2_1': map(lambda x: abs(y_points_2_1[x] - y_answers[x]), range(len(y_answers))),
                              'y2_2': y_points_2_2,
                              'error2_2': map(lambda x: abs(y_points_2_2[x] - y_answers[x]), range(len(y_answers))),
                              'y3': y_points_3,
                              'error3': map(lambda x: abs(y_points_3[x] - y_answers[x]), range(len(y_answers))),
                              'y4_1': y_points_4_1,
                              'error4_1': map(lambda x: abs(y_points_4_1[x] - y_answers[x]), range(len(y_answers))),
                              'y4_2': y_points_4_2,
                              'error4_2': map(lambda x: abs(y_points_4_2[x] - y_answers[x]), range(len(y_answers)))})

    print('Runge-Kutta Results and Errors:')
    print(tabulate(df_results, headers='keys', tablefmt='fancy_grid', showindex=True))

    return df_results


def plot_results(data):
    fig, ax = plt.subplots(figsize=(5, 4))
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Precision of Results")
    ax.plot(data['x'], data['y2_1'], label='second order 1st')
    ax.plot(data['x'], data['y2_2'], label='second order 2nd')
    ax.plot(data['x'], data['y3'], label='third order')
    ax.plot(data['x'], data['y4_1'], label='fourth order 1st')
    ax.plot(data['x'], data['y4_2'], label='fourth order 2nd')
    ax.legend()
    plt.show()


results = calculation()
plot_results(results)
