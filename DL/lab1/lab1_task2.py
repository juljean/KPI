import math
import random


class TwoLayerPerceptron:
    def __init__(self, x, yr, dd, y_act=lambda x: 1 / (1 + math.exp(-x))):
        """
        Initialization of parameters in class
        :param x: int, input signal
        :param yr: float, expected output value
        :param dd: float, allowed error
        :param y_act: activation function
        """
        self.x = x
        self.yr = yr
        self.dd = dd
        self.w1 = random.random()
        self.w2 = random.random()
        self.y_act = y_act

    def learn(self):
        """
        Learning mode
        :return: list with weights values
        """
        x2 = self.w1 * self.x
        y2 = self.y_act(x2)
        x3 = self.w2 * y2
        y3 = self.y_act(x3)

        # current error for calculated y
        dn = abs((self.yr - y3) / self.yr)
        print("y: ", y3, "dn:", dn)
        if dn > self.dd:
            # weights normalization
            q3 = y3 * (1 - y3) * (self.yr - y3)
            q2 = y2 * (1 - y2) * (q3 * self.w2)
            self.w1 += self.x * q2
            self.w2 += y2 * q3
            return self.learn()
        return [self.w1, self.w2]

    def recognition(self):
        """
        Recognition mode
        :return: float, predicted y
        """
        x2 = self.w1 * self.x
        y2 = self.y_act(x2)
        x3 = self.w2 * y2
        y3 = self.y_act(x3)
        return y3


perceptron = TwoLayerPerceptron(3, 0.4, 0.1)
print(*perceptron.learn())
