from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, GRU, BatchNormalization

def create_GRU(hidden_units, dense_units, input_shape, activation, loss):
    model = Sequential()
    model.add(GRU(hidden_units, input_shape=input_shape,
                        activation=activation[0]))
    model.add(BatchNormalization())
    model.add(Dense(units=dense_units, activation=activation[1]))
    model.compile(loss=loss, optimizer='adam')
    return model