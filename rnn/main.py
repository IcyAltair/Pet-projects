import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from sklearn.metrics import r2_score
import math
import matplotlib.pyplot as plt

import const
from rnn import create_RNN
from gru_nn import create_GRU
from lstm_nn import create_LSTM


def preprocessing() -> pd.DataFrame:
    df = pd.read_csv('Steel_industry_data.csv', skipinitialspace=True)
    df['date'] = pd.to_datetime(df['date'], format="%d/%m/%Y %H:%M")
    return df


def encoding(df: pd.DataFrame) -> pd.DataFrame:
    le = LabelEncoder()
    for i in df.columns:
        if df[i].dtypes == 'object':
            df[i] = le.fit_transform(df[i])
    return df


def split_data(split_percent=0.8) -> set:
    df = pd.read_csv('Steel_industry_data.csv', usecols=[1], engine='python')
    data = np.array(df.values.astype('float32'))
    scaler = MinMaxScaler(feature_range=(0, 1))
    data = scaler.fit_transform(data).flatten()
    n = len(data)
    split = int(n*split_percent)
    train_data = data[range(split)]
    test_data = data[split:]
    return train_data, test_data, data


def reshape_data(data, time_step):
    Y_ind = np.arange(time_step, len(data), time_step)
    Y = data[Y_ind]
    rows_x = len(Y)
    X = data[range(time_step*rows_x)]
    X = np.reshape(X, (rows_x, time_step, 1))
    return X, Y


def print_error(train_y, test_y, train_predict, test_predict):
    train_mse = mean_squared_error(train_y, train_predict)
    test_mse = mean_squared_error(test_y, test_predict)
    train_rmse = math.sqrt(mean_squared_error(train_y, train_predict))
    test_rmse = math.sqrt(mean_squared_error(test_y, test_predict))
    train_r2 = r2_score(train_y, train_predict)
    test_r2 = r2_score(test_y, test_predict)
    print('Train MSE: %.3f MSE' % (train_mse))
    print('Test MSE: %.3f MSE' % (test_mse))
    print('Train RMSE: %.3f RMSE' % (train_rmse))
    print('Test RMSE: %.3f RMSE' % (test_rmse))
    print('Train R2: %.3f R2' % (train_r2))
    print('Test R2: %.3f R2' % (test_r2))


def rnn_model(train_x, test_x, train_y, test_y, time_step, epochs, loss):
    model = create_RNN(hidden_units=3, dense_units=1, input_shape=(time_step, 1),
                       activation=['tanh', 'tanh'], loss=loss)
    model.fit(train_x, train_y, epochs=epochs, batch_size=1, verbose=2)
    train_predict = model.predict(train_x)
    test_predict = model.predict(test_x)
    print("RNN model")
    print_error(train_y, test_y, train_predict, test_predict)


def gru_model(train_x, test_x, train_y, test_y, time_step, epochs, loss):
    model = create_GRU(hidden_units=3, dense_units=1, input_shape=(time_step, 1),
                       activation=['tanh', 'tanh'], loss=loss)
    model.fit(train_x, train_y, epochs=epochs, batch_size=1, verbose=2)
    train_predict = model.predict(train_x)
    test_predict = model.predict(test_x)
    print("GRU model")
    print_error(train_y, test_y, train_predict, test_predict)


def lstm_model(train_x, test_x, train_y, test_y, time_step, epochs, loss):
    model = create_LSTM(hidden_units=3, dense_units=1, input_shape=(time_step, 1),
                        activation=['tanh', 'tanh'], loss=loss)
    model.fit(train_x, train_y, epochs=epochs, batch_size=1, verbose=2)
    train_predict = model.predict(train_x)
    test_predict = model.predict(test_x)
    print("LSTM model")
    print_error(train_y, test_y, train_predict, test_predict)


def main():
    df = preprocessing()
    df = encoding(df)
    train_data, test_data, data = split_data()
    train_x, train_y = reshape_data(train_data, const.TIME_STEP)
    test_x, test_y = reshape_data(test_data, const.TIME_STEP)
    rnn_model(train_x, test_x, train_y, test_y, const.TIME_STEP,
              const.EPOCHS, "mean_squared_error")
    gru_model(train_x, test_x, train_y, test_y, const.TIME_STEP,
              const.EPOCHS, "mean_squared_error")
    lstm_model(train_x, test_x, train_y, test_y, const.TIME_STEP,
               const.EPOCHS, "mean_squared_error")


if __name__ == '__main__':
    main()
