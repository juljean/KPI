import math
import random


class TwoLayerPerceptron231:
    def __init__(self, x, yr, dd, y_act=lambda x: 1 / (1 + math.exp(-x))):
        """
        Initialization of parameters in class
        :param x: list of float values, input signal
        :param yr: float, expected output value
        :param dd: float, allowed error
        :param y_act: activation function
        """
        self.x = x
        self.yr = yr
        self.dd = dd
        self.w = [[random.random() * 0.01 for __ in range(3)] for _ in range(3)]
        self.w.append([random.random() * 0.01 for _ in range(4)])
        self.y_act = y_act

    def learn(self):
        """
        Learning mode
        :return: list of float numbers, normalized weights
        """

        # x0 is always 1
        x0, x1, x2 = 1, self.x[0], self.x[1]

        y1, y2, y3 = [self.y_act(x0 * self.w[i][0] + x1 * self.w[i][1] + x2 * self.w[i][2])
                      for i in range(3)]
        xs = self.w[3][0] * x0 + self.w[3][1] * y1 + self.w[3][2] * y2 + self.w[3][3] * y3

        y_predicted = self.y_act(xs)
        # current error for calculated y
        dn = abs((self.yr - y_predicted) / self.yr)
        print("y: ", y_predicted, "dn:", dn)

        if dn > self.dd:
            # weights normalization
            q13 = y_predicted * (1 - y_predicted) * (self.yr - y_predicted)

            b1 = [q13 * x0, q13 * y1, q13 * y2, q13 * y3]
            for i in range(4):
                self.w[3][i] = self.w[3][i] + b1[i]
            y_n = [y1, y2, y3]
            x_n = [x0, x1, x2]
            for i in range(3):
                q1 = y_n[i]*(1-y_n[i])*(q13*self.w[3][i+1])
                for j in range(3):
                    self.w[i][j] = self.w[i][j] + x_n[j] * q1
            return self.learn()
        return self.w

    def recognition(self, x):
        """
        Recognition mode
        :param x: list of float values, input signal
        :return: predicted y
        """
        # x0 is always 1
        x0, x1, x2 = 1, x[0], x[1]
        y1, y2, y3 = [self.y_act(x0 * self.w[i][0] + x1 * self.w[i][1] + x2 * self.w[i][2])
                      for i in range(3)]
        xs = self.w[3][0] * x0 + self.w[3][1] * y1 + self.w[3][2] * y2 + self.w[3][3] * y3

        y_predicted = self.y_act(xs)
        return y_predicted


perceptron = TwoLayerPerceptron231([0.3, 0.1], 0.4, 0.1)
print(perceptron.learn())