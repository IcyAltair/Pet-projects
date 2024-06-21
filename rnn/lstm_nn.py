from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM

def create_LSTM(hidden_units, dense_units, input_shape, activation, loss):
    model = Sequential()
    model.add(LSTM(hidden_units, input_shape=input_shape,
                        activation=activation[0]))
    model.add(Dense(units=dense_units, activation=activation[1]))
    model.compile(loss=loss, optimizer='adam')
    return model