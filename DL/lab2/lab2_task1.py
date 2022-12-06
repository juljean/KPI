import numpy as np


class PNN:
    def __init__(self, train_x, train_y, epsilon=1, number_of_classes=2):
        """
        Initialization of class
        :param train_x: np.array, input signals of training set
        :param train_y: np.array, output signals of training set
        :param epsilon: int, deviation for radial-basis function in the pattern layer
        :param number_of_classes: int, number of possible outputs
        """
        self.train_x = train_x
        self.train_y = train_y
        self.epsilon = epsilon
        self.number_of_classes = number_of_classes
        # Weights based on the number of samples for particular output class
        self.weighted_value = self.get_weights(train_y)
        # Median of the range
        self.q2 = np.median(self.train_x, axis=0)
        # Label encoding for output signals
        self.label_encoding = {0: "A", 1: "B"}
        # Normalized train input
        self.normalized_train_x = self.input_layer(train_x)

    def input_layer(self, x):
        """
        Normalizing data range by subtracting the median and dividing by the interquartile range
        :param x: np.array, range
        :return: np.array, normalized range
        """
        q1, q3 = np.percentile(x, q=[75, 25])
        return (x - self.q2) / (q3 - q1)

    def pattern_layer(self, x):
        """
        Patternizing the data using inverse distance
        :param x: np.array, normalized values for prediction
        :return: list
        """
        result = []
        for i in range(len(x)):
            # Euclidean distance
            euclidian_distance = np.sum(pow(self.normalized_train_x - x[i], 2), axis=-1)
            # Inverse distance estimation
            result.append(np.exp(-euclidian_distance * pow(self.epsilon, 2)))
        return result

    @staticmethod
    def get_hidden_neuron(*args):
        """
        Get each hidden neuron stores the actual target category of each training event
        :param args: int
        :return: np.ndarray
        """
        # Define dimensions of result matrix
        number_of_examples = sum(args)
        res = np.zeros((number_of_examples, len(args)), dtype='float64')  # Result template
        shift = 0  # Running offset
        for i in range(len(args)):
            res[shift:shift + args[i], i] = 1 / args[i]  # Scaled by number of same class
            shift += args[i]  # Moving offset
        return res

    def get_weights(self, train_y):
        """
        Get the number of samples for each class
        :param train_y: np.ndarray, output signals for train set
        :return: np.ndarray
        """
        class_example_number = np.zeros(self.number_of_classes, dtype='int')
        for i in range(self.number_of_classes):
            # Number training examples every class has
            class_example_number[i] = np.count_nonzero(train_y == i)
        return self.get_hidden_neuron(*class_example_number)

    def summation_layer(self, pattern_output):
        """
        The values for the class that the pattern neurons represent are added together
        :param pattern_output: np.ndarray
        :return: np.ndarray
        """
        return np.dot(pattern_output, self.weighted_value)  # compute weighed sum

    def decision_layer(self, addition_output):
        """
        The output layer compares the weighted votes accumulated in the pattern layer for each target category and
        utilizes the largest vote to predict the target category.
        :param addition_output:
        :return:
        """
        return np.argmax(addition_output, axis=-1)

    def predict(self, x):
        """
        Predicting the output signals for the new entries
        :param x: np.ndarray, input signals
        :return: np.ndarray
        """
        normalized_x = self.input_layer(x)
        pattern_output = self.pattern_layer(normalized_x)
        addition_output = self.summation_layer(pattern_output)
        return self.decision_layer(addition_output)

    def classification_result(self, data_x, data_y):
        """
        Results with the label-deencoding
        :param data_x: np.ndarray, input signals
        :param data_y: np.ndarray, predicted answers
        """
        class_name = self.label_encoding[data_y[0]]
        print(f"Result for entry {data_x} is `{class_name}`")
        print()


def main():
    """
    Performing the training and prediction of the model
    :return:
    """
    train_x = np.array([[1, 1], [1, 2], [2, 1], [10, 10]])
    train_y = np.array([0, 0, 0, 1])  # 0 == A, 1 == B
    model = PNN(train_x=train_x, train_y=train_y)  # Create PNN model
    model.classification_result([1, 0], model.predict(np.array([1, 0])))
    model.classification_result([3, 4], model.predict(np.array([3, 4])))
    model.classification_result([12, 10], model.predict(np.array([12, 10])))


main()
