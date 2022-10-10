import math
import random


class Neuron:
    def __init__(self, x, yr, dd, y_act=lambda x: 1 / (1 + math.exp(-x))):
        """
        Initialization of parameters in class
        :param x: list of float numbers, input signals
        :param yr: float, expected output value
        :param dd: float, allowed error
        :param y_act: activation function
        """
        self.x = x
        # Number of signals
        self.x_num = len(x)
        self.w = [random.random() * 0.01 for i in range(self.x_num)]
        self.dd = dd
        self.yr = yr
        self.y_act = y_act

    def learn(self):
        """
        Learning mode
        :return: list of float numbers, normalized weights
        """
        xs = 0
        for ind in range(self.x_num):
            xs += self.x[ind] * self.w[ind]
        y = self.y_act(xs)
        # current error for calculated y
        dn = abs((self.yr - y) / self.yr)
        print("y: ", y, "dn:", dn)
        if dn > self.dd:
            # weights normalization
            q = y * (1 - y) * (self.yr - y)
            dw = [self.x[ind] * q for ind in range(self.x_num)]
            self.w = [self.w[ind] + dw[ind] for ind in range(self.x_num)]
            return self.learn()
        return self.w

    def recognition(self, x):
        """
        Recognition mode
        :param x: list of float numbers, input signals
        :return: float, predicted y
        """
        xs = 0
        for n in range(self.x_num):
            xs += eval(f"x" + str(n)) * eval(f"self.w" + str(n))
        y = self.y_act(xs)
        return y


neur = Neuron([1, 3, 5, 7], 0.3, 0.1)
print("Optimized weights:", *(neur.learn()))

