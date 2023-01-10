import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn import preprocessing
import time
import random


class TwoLayeredPerceptron(object):
    def __init__(self, n_iterations=3, dd=0.01):
        # Precision
        self.dd = dd
        self.n_iterations = n_iterations

    def fit(self, X, y, dn):
        self.w = np.array([random.random() * 0.01 for _ in range(1 + X.shape[1])])
        self.errors_ = []
        for _ in range(self.n_iterations):
            errors = 0
            for xi, expected_value in zip(X, y):
                y_predicted = self.predict(xi)
                self.w[1:] = self.w[1:] + self.dd * (expected_value - y_predicted) * xi
                self.w[0] = self.w[0] + self.dd * (expected_value - y_predicted) * 1
                update = self.dd * (expected_value - y_predicted)
                errors += int(update != 0.0)
                self.errors_.append(errors)
        return self.w, self.errors_[-1]

    def activation_function(self, X):
        # sum of weighted input signals
        weighted_sum = np.dot(X, self.w[1:]) + self.w[0]
        return np.where(weighted_sum >= 0.0, 1, 0)

    def predict(self, X):
        return self.activation_function(X)

    def accuracy(self, X, y):
        misclassified_data_count = 0
        for xi, expected_value in zip(X, y):
            predicted_value = self.predict(xi)
            if expected_value != predicted_value:
                misclassified_data_count += 1
        total_data_count = len(X)
        self.score_ = (total_data_count - misclassified_data_count) / total_data_count
        return self.score_


# Headers for data
columns = ['duration', 'protocol_type', 'service', 'flag', 'src_bytes', 'dst_bytes', 'land', 'wrong_fragment', 'urgent',
           'hot', 'num_failed_logins', 'logged_in', 'num_compromised', 'root_shell', 'su_attempted', 'num_root',
           'num_file_creations', 'num_shells', 'num_access_files', 'num_outbound_cmds', 'is_host_login',
           'is_guest_login', 'count', 'srv_count', 'serror_rate', 'srv_serror_rate', 'rerror_rate', 'srv_rerror_rate',
           'same_srv_rate', 'diff_srv_rate', 'srv_diff_host_rate', 'dst_host_count', 'dst_host_srv_count',
           'dst_host_same_srv_rate', 'dst_host_diff_srv_rate', 'dst_host_same_src_port_rate',
           'dst_host_srv_diff_host_rate', 'dst_host_serror_rate', 'dst_host_srv_serror_rate', 'dst_host_rerror_rate',
           'dst_host_srv_rerror_rate', 'attack_type']


def fetch_data():
    # Reading .data file
    df = pd.read_csv('kddcup.data', sep=",")

    # Setting up columns' headers
    df.columns = columns

    # Selecting data only for 8 Variant
    df = df.loc[df['attack_type'].isin(['normal.', 'ftp_write.'])]
    return df


# Encoding
def encoding(df):
    label_encoder = preprocessing.LabelEncoder()
    df = df.apply(label_encoder.fit_transform)
    wo_attack = df.loc[:, df.columns != 'attack_type'].copy()
    normalized_df = preprocessing.normalize(wo_attack)
    scaled_df = pd.DataFrame(normalized_df, columns=columns[:-1])
    scaled_df['attack_type'] = df.attack_type
    print(scaled_df)
    return scaled_df


def split_data(df):
    # Outputting indexes of data with ftp_write errors for future testing
    df_attacks = df.loc[df['attack_type'] < 0.5].copy()
    df = df.loc[df['attack_type'] >= 0.5].copy()
    df = df.iloc[:8000]
    # To exclude the probability of few attacks sample to remain only in train dataset. All in all there are 8
    # ftp_write cases
    train_attacks_df = df_attacks.iloc[:5]
    test_attacks_df = df_attacks.iloc[5:]
    # Select input parameters
    X = df.loc[:, df.columns != 'attack_type'].copy()
    # Select output parameters
    y = df.loc[:, df.columns == 'attack_type'].copy()

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=42)
    wo_attack_train = train_attacks_df.loc[:, train_attacks_df.columns != 'attack_type'].copy()
    w_attack_train = train_attacks_df.loc[:, train_attacks_df.columns == 'attack_type'].copy()
    # X_train.append(wo_attack_train)
    # y_train.append(w_attack_train)
    X_train = pd.concat([X_train, wo_attack_train])
    y_train = pd.concat([y_train, w_attack_train])

    wo_attack_test = test_attacks_df.loc[:, test_attacks_df.columns != 'attack_type'].copy()
    w_attack_test = test_attacks_df.loc[:, test_attacks_df.columns == 'attack_type'].copy()
    X_test = pd.concat([X_test, wo_attack_test])
    y_test = pd.concat([y_test, w_attack_test])
    return X_train, X_test, y_train, y_test


def main():
    model = TwoLayeredPerceptron()
    counter_test = 0

    start_time = time.time()
    X_train, X_test, y_train, y_test = split_data(encoding(fetch_data()))
    # Fetch indexes of rows for later iteration
    train_indexes = X_train.index
    print(f"Count of train samples is {len(train_indexes)}")
    for i in train_indexes.values:
        X_train_for_model = X_train.loc[:i, :].values
        y_train_for_model = y_train.loc[:i, :].values
        weights, error = model.fit(X_train_for_model, y_train_for_model, dn=1000)
        if counter_test == 0 or counter_test == 49 or counter_test == 99:
            print(f"Echo {counter_test+1}. Weights are {weights}. Error is {error}")
        counter_test += 1

    end_time_fitting = time.time()
    print(f"Time spent for fitting model {end_time_fitting - start_time}")

    X_test_for_model = X_test.values
    y_test_for_model = y_test.values
    print(f"Model accuracy = {model.accuracy(X_test_for_model, y_test_for_model)}")

    end_time_predicting = time.time()
    print(f"Time spent for testing model {end_time_predicting - end_time_fitting}")


main()