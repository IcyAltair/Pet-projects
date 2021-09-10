from datetime import timedelta
import numpy as np
import numba
import random
import simatrix
from time import monotonic


START = -1000
END = 1000
N = 500


class Matrix(list):
    @classmethod
    def zeros(cls, shape):
        n_rows, n_cols = shape
        return cls([[0] * n_cols for i in range(n_rows)])

    @classmethod
    def random(cls, shape):
        M, (n_rows, n_cols) = cls(), shape
        for i in range(n_rows):
            M.append([random.randint(-255, 255)
                      for j in range(n_cols)])
        return M

    def transpose(self):
        n_rows, n_cols = self.shape
        return self.__class__(zip(*self))

    @property
    def shape(self):
        return ((0, 0) if not self else
                (len(self), len(self[0])))


def matrix_product(X, Y):
    n_xrows, n_xcols = X.shape
    n_yrows, n_ycols = Y.shape
    Z = Matrix.zeros((n_xrows, n_ycols))
    Yt = Y.transpose()
    for i, (Xi, Zi) in enumerate(zip(X, Z)):
        for k, Ytk in enumerate(Yt):
            Zi[k] = sum(Xi[j] * Ytk[j] for j in range(n_xcols))
    return Z


@numba.jit
def jit_matrix_product(X, Y):
    n_xrows, n_xcols = X.shape
    n_yrows, n_ycols = Y.shape
    Z = np.zeros((n_xrows, n_ycols), dtype=X.dtype)
    for i in range(n_xrows):
        for k in range(n_ycols):
            for j in range(n_xcols):
                Z[i, k] += X[i, j] * Y[j, k]
    return Z


def py_test_int(N: int) -> np.ndarray:
    m1, m2 = [], []
    for i in range(N):
        m1.append([random.randint(START, END) for e in range(N)])
        m2.append([random.randint(START, END) for e in range(N)])
    # matrix_1 = np.random.randint(START, END, (N, N))
    # matrix_2 = np.random.randint(START, END, (N, N))
    matrix_1 = np.asarray(m1)
    matrix_2 = np.asarray(m2)
    start_time = monotonic()
    np.matmul(matrix_1, matrix_2)
    print("py_test_int with numpy takes", timedelta(
        seconds=monotonic() - start_time))


def py_test_float(N: int) -> np.ndarray:
    m1, m2 = [], []
    for i in range(N):
        m1.append([(random.random() * (END-START) + START) for e in range(N)])
        m2.append([(random.random() * (END-START) + START) for e in range(N)])
    # matrix_1 = (END - START) * np.random.random_sample((N, N)) - START
    # matrix_2 = (END - START) * np.random.random_sample((N, N)) - START
    matrix_1 = np.asarray(m1)
    matrix_2 = np.asarray(m2)
    start_time = monotonic()
    np.matmul(matrix_1, matrix_2)
    print("py_test_float with numpy takes", timedelta(
        seconds=monotonic() - start_time))


def C_test_int(N: int) -> list:
    m1, m2 = [], []
    for i in range(N):
        m1.append([random.randint(START, END) for e in range(N)])
        m2.append([random.randint(START, END) for e in range(N)])
    #print(*m1)
    #print(*m2)
    start_time = monotonic()
    simatrix.product(m1, m2)
    print("C_test_int takes", timedelta(
        seconds=monotonic() - start_time))


def C_test_float(N: int) -> list:
    m1, m2 = [], []
    for i in range(N):
        m1.append([(random.random() * (END-START) + START) for e in range(N)])
        m2.append([(random.random() * (END-START) + START) for e in range(N)])
    #print(*m1)
    #print(*m2)
    start_time = monotonic()
    simatrix.product(m1, m2)
    print("C_test_float takes", timedelta(
        seconds=monotonic() - start_time))


def usual_test():
    shape = N, N
    X = np.random.randint(START, END, shape)
    Y = np.random.randint(START, END, shape)
    start_time = monotonic()
    matrix_product(X, Y)
    print("usual test takes", timedelta(
        seconds=monotonic() - start_time))


def jit_test():
    shape = N, N
    X = np.random.randint(START, END, shape)
    Y = np.random.randint(START, END, shape)
    start_time = monotonic()
    jit_matrix_product(X, Y)
    print("jit test takes", timedelta(
        seconds=monotonic() - start_time))


def main():
    py_test_int(N)
    #py_test_float(N)
    C_test_int(N)
    #C_test_float(N)
    #usual_test()
    jit_test()


if __name__ == "__main__":
    main()
