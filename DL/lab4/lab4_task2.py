import matplotlib.pyplot as plt
from keras.utils import np_utils
from keras.models import load_model
import numpy as np
import random

# Load test data
data = np.load('test_data.npz')
X_test = data['X_test']
y_test = data['y_test']
# Load the model
model = load_model('my_model.h5')
# Change the type of array so that model can process it
X_test = X_test.astype('float32')
# Encoding process
Y_test = np_utils.to_categorical(y_test, 10)
labels = ['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
counter_labels = {item[0]: item[1:] for item in enumerate(labels)}
# Set up random indexes to test model
example_indexes = [random.randint(0, 1000) for _ in range(5)]

# Set of all predicted labels from the test set
y_predicted = np.argmax(model.predict(X_test), axis=-1)
# Recognition of 5 random pictures
for ind in example_indexes:
    plt.imshow(X_test[ind])
    plt.show()
    print(f'Model has recognized: {counter_labels[y_predicted[ind]]} here')
    print(f'In reality there was : {labels[y_test[ind][0]]} here')
    # Model score
    scores = model.evaluate(X_test, Y_test, verbose=0)
    print(f"Accuracy of recognition: {scores[1] * 100} %")
