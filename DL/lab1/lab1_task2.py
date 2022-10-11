import math
import random


class TwoLayerPerceptron111:
    def __init__(self, dd, y_act=lambda x: 1 / (1 + math.exp(-x))):
        """
        Initialization of parameters in class
        :param dd: float, allowed error
        :param y_act: activation function
        """
        self.dd = dd
        self.w1 = random.random()
        self.w2 = random.random()
        self.y_act = y_act

    def learn(self, x, yr):
        """
        Learning mode
        :param x: int, input signal
        :param yr: float, expected output value
        :return: list of float numbers, normalized weights
        """

        # First and Second layer learning
        x2 = self.w1 * x
        y2 = self.y_act(x2)
        x3 = self.w2 * y2
        y3 = self.y_act(x3)

        # Calculation of current error for y
        dn = abs((yr - y3) / yr)
        print("y: ", y3, "dn:", dn)
        if dn > self.dd:
            # Weights normalization
            q3 = y3 * (1 - y3) * (yr - y3)
            q2 = y2 * (1 - y2) * (q3 * self.w2)
            self.w1 += x * q2
            self.w2 += y2 * q3
            return self.learn(x, yr)
        return [self.w1, self.w2]

    def recognition(self, x):
        """
        Recognition mode
        :param x: int, input signal
        :return: float, predicted y
        """
        x2 = self.w1 * x
        y2 = self.y_act(x2)
        x3 = self.w2 * y2
        y3 = self.y_act(x3)
        return y3


perceptron = TwoLayerPerceptron111(0.1)
print(*perceptron.learn(3, 0.7))
