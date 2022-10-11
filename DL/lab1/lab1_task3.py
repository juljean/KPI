import math
import random


class TwoLayerPerceptron231:
    def __init__(self, dd, y_act=lambda x: 1 / (1 + math.exp(-x))):
        """
        Initialization of parameters in class
        :param dd: float, allowed error
        :param y_act: activation function
        """
        self.dd = dd
        self.w = [[random.random() * 0.01 for __ in range(3)] for _ in range(3)]
        self.w.append([random.random() * 0.01 for _ in range(4)])
        self.y_act = y_act

    def learn(self, x, yr):
        """
        Learning mode
        :param x: list of float values, input signal
        :param yr: float, expected output value
        :return: list of float numbers, normalized weights
        """

        # x0 is always 1
        x0, x1, x2 = 1, x[0], x[1]

        # First and Second layer learning
        y1, y2, y3 = [self.y_act(x0 * self.w[i][0] + x1 * self.w[i][1] + x2 * self.w[i][2])
                      for i in range(3)]
        xs = self.w[3][0] * x0 + self.w[3][1] * y1 + self.w[3][2] * y2 + self.w[3][3] * y3

        y_predicted = self.y_act(xs)
        # Calculation of current error for y
        dn = abs((yr - y_predicted) / yr)
        print("y: ", y_predicted, "dn:", dn)

        if dn > self.dd:
            # Weights normalization
            q13 = y_predicted * (1 - y_predicted) * (yr - y_predicted)

            b1 = [q13 * x0, q13 * y1, q13 * y2, q13 * y3]
            for i in range(4):
                self.w[3][i] = self.w[3][i] + b1[i]
            y_n = [y1, y2, y3]
            x_n = [x0, x1, x2]
            for i in range(3):
                q1 = y_n[i]*(1-y_n[i])*(q13*self.w[3][i+1])
                for j in range(3):
                    self.w[i][j] = self.w[i][j] + x_n[j] * q1
            return self.learn(x, yr)
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


perceptron = TwoLayerPerceptron231(0.01)

for iteration in range(10000):
    print(iteration)
    num = random.randrange(1, 10, 1) * 0.1
    div = random.randrange(1, 10, 1) * 0.1
    perceptron.learn([num*div, num*(1-div)], num)


print(perceptron.recognition([0.1, 0.1]))
print(perceptron.recognition([0.2, 0.1]))
print(perceptron.recognition([0.35, 0.12]))
print(perceptron.recognition([0.7, 0.2]))
print(perceptron.recognition([0.2, 0.1]))