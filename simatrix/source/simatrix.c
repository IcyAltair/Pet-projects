//https://pavel-karateev.gitbook.io/intermediate-python/raznoe/python_c_extension
//https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
//https://docs.python.org/3.8/c-api/
//https://docs.scipy.org/doc/scipy-0.14.0/scipy-ref-0.14.0.pdf
//https://stackoverflow.com/questions/36050713/using-py-buildvalue-to-create-a-list-of-tuples-in-c
//https://stackoverflow.com/questions/30330279/how-to-pass-two-dimensional-array-from-c-to-python
//https://stackoverflow.com/questions/31644420/complex-matrix-multiplication-using-gsl

#include "Python.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
//#include <gsl/gsl_blas.h>
//#include <gsl/gsl_matrix.h>
//#include <gsl/gsl_complex_math.h>
#ifdef __unix__
	#include <pthread.h>
#elif defined(_WIN32) || defined(WIN32)
	#define OS_Windows
	#include <windows.h>
#endif

/*
typedef struct {
	long long x;
}unit;

typedef struct {
	int row;
	int col;
	unit* x;
}matrix;

#ifdef OS_Windows
matrix A, B, C, _C;
CRITICAL_SECTION cs;

matrix CreateMatrix(int row, int col, long long** data)
{
	matrix target;
	int i = 0 , j = 0;

	target.row = row;
	target.col = col;
	target.x = (unit*)malloc(row * col * sizeof(unit));

	for(i = 0;i < row; i++)
		for (j = 0; j < col; j++)
		{
			(target.x + i * target.col + j)->x = data[i][j];
		}
	return target;
}

DWORD WINAPI MultWork(LPVOID pM)
{
	for (;;)
	{
		int firstNum = 0;
		int secondNum = 0;
		int res, i, j, flag = 0, close = 0;

		EnterCriticalSection(&cs);
		for (i = 0; i < _C.row; i++)
		{
			for (j = 0; j < _C.col; j++)
			{
				if ((_C.x + i * _C.col + j)->x == NULL)
				{
					firstNum = i;
					secondNum = j;
					(_C.x + i * _C.col + j)->x = 1;
					close = 1;
					break;
				}
			}
			if (close == 1)
				break;
			else if (i == _C.row - 1)
				flag = 1;
		}
		LeaveCriticalSection(&cs);

		if (flag == 1)
			ExitThread(NULL);
		res = CalcuOneUnit(firstNum, secondNum);
		(C.x + firstNum * C.col + secondNum)->x = res;
	}
	ExitThread(NULL);
	
}

int CalcuOneUnit(int first, int second)
{
	int i = 0, res = 0;
	//EnterCriticalSection(&cs);
    //printf("%d,%d is working\n",first,second);
    //Leave Critical Section (& cs);
	for(i = 0; i<A.col;i++)
		res += (A.x + first * A.col + i)->x * (B.x + i * B.col + second)->x;
	return res;
}

long long** GetRes(matrix res, unsigned long long size)
{
	long long** resC;
	int i = 0, j = 0;
	resC = calloc(size, sizeof(long long*));
	for (i = 0; i < size; i++)
		resC[i] = calloc(size, sizeof(long long));

	int row = res.row;
	int col = res.col;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			resC[i][j] = (res.x + i * col + j)->x;
		}
	}

	return resC;
}
#endif
*/
//void multiply(gsl_matrix_complex* A, gsl_matrix_complex* B, gsl_matrix_complex* result)
//{
//	gsl_blas_zgemm(CblasNoTrans, CblasNoTrans,
//		GSL_COMPLEX_ONE, A, B,
//		GSL_COMPLEX_ZERO, result);	
//}


inline static PyObject* simatrix_product(PyObject* self, PyObject* args)
{
	PyObject* listObjA;
	PyObject* listObjB;

	if (!PyArg_ParseTuple(args, "OO", &listObjA, &listObjB))
	{
		return NULL;
	}

	unsigned long long N = PyList_Size(listObjA);
	int i = 0, j = 0, k = 0;

	if (N != PyList_Size(listObjB))
	{
		return NULL;
	}

	const Py_ssize_t list_len = N;


	PyObject* check = PyList_GetItem(listObjA, 0);
	PyObject* value = PyList_GetItem(check, 0);

	if ((!value || !PyFloat_Check(value) && (!value || !PyLong_Check(value))))
	{
		return NULL;
	}


	long long** intA;
	long long** intB;
	long long** intRes;
	long long intSum = 0;
	intA = calloc(N, sizeof(long long*));
	for (i = 0; i < N; i++)
		intA[i] = calloc(N, sizeof(long long));

	intB = calloc(N, sizeof(long long*));
	for (i = 0; i < N; i++)
		intB[i] = calloc(N, sizeof(long long));

	intRes = calloc(N, sizeof(long long*));
	for (i = 0; i < N; i++)
		intRes[i] = calloc(N, sizeof(long long));

	long double** floatA;
	long double** floatB;
	long double** floatRes;
	long double floatSum = 0;
	floatA = calloc(N, sizeof(long double*));
	for (i = 0; i < N; i++)
		floatA[i] = calloc(N, sizeof(long double));

	floatB = calloc(N, sizeof(long double*));
	for (i = 0; i < N; i++)
		floatB[i] = calloc(N, sizeof(long double));

	floatRes = calloc(N, sizeof(long double*));
	for (i = 0; i < N; i++)
		floatRes[i] = calloc(N, sizeof(long double));



	for (i = 0; i < N; i++)
	{
		PyObject* tempA = PyList_GetItem(listObjA, i);
		PyObject* tempB = PyList_GetItem(listObjB, i);

		for (j = 0; j < N; j++)
		{
			PyObject* valueA = PyList_GetItem(tempA, j);
			PyObject* valueB = PyList_GetItem(tempB, j);

			if (PyLong_Check(valueA) && PyLong_Check(valueB))
			{
				if (j == 0)
				{
					intSum = 1;
				}
				intA[i][j] = PyLong_AsLongLong(valueA);
				intB[i][j] = PyLong_AsLongLong(valueB);
				//intSum += intA[i][j];
			}
			else if (PyFloat_Check(valueA) && PyFloat_Check(valueB))
			{
				if (j == 0)
				{
					floatSum = 1;
				}
				floatA[i][j] = PyFloat_AsDouble(valueA);
				floatB[i][j] = PyFloat_AsDouble(valueB);
				//floatSum += floatA[i][j];
			}
			else
			{
				return NULL;
			}

		}
	}
	PyObject* list_res = PyList_New(0);
	if (intSum)
	{
		int threadNum = omp_get_max_threads();
#pragma omp parallel shared(intA, intB, intRes) private(i, j, k)
		{
#pragma omp for
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					intRes[i][j] = 0;
					for (k = 0; k < N; k++)
					{
						intRes[i][j] = intRes[i][j] + intA[i][k] * intB[k][j];
					}
				}
			}
		}
		
		if (list_res == NULL)
		{
			return NULL;
		}

		for (i = 0; i < N; i++)
		{
			PyObject* list_buf = PyList_New(0);
			if (list_buf == NULL)
			{
				return NULL;
			}
			for (Py_ssize_t k = 0; k < list_len; k++)
			{
				PyObject* value_res = PyLong_FromLongLong(intRes[i][k]);// (!)
				if (value_res == NULL)
				{
					return NULL;
				}

				if (PyList_Append(list_buf, value_res) == -1)
				{
					return NULL;
				}
				PyList_SET_ITEM(list_buf, k, value_res);
			}
			if (PyList_Append(list_res, list_buf) == -1)
			{
				return NULL;
			}
			//PyList_SET_ITEM(list_res, i, list_buf);
		}
	}
	else if (floatSum)
	{
		int threadNum = omp_get_max_threads();
#pragma omp parallel shared(floatA, floatB, floatRes) private(i, j, k)
		{
#pragma omp for
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					floatRes[i][j] = 0;
					for (k = 0; k < N; k++)
					{
						floatRes[i][j] = floatRes[i][j] + floatA[i][k] * floatB[k][j];
					}
				}
			}
		}
		
		if (list_res == NULL)
		{
			return NULL;
		}

		for (i = 0; i < N; i++)
		{
			PyObject* list_buf = PyList_New(0);
			if (list_buf == NULL)
			{
				return NULL;
			}
			for (Py_ssize_t k = 0; k < list_len; k++)
			{
				PyObject* value_res = PyFloat_FromDouble(floatRes[i][k]);// (!)
				if (value_res == NULL)
				{
					return NULL;
				}

				if (PyList_Append(list_buf, value_res) == -1)
				{
					return NULL;
				}
				PyList_SET_ITEM(list_buf, k, value_res);
			}
			if (PyList_Append(list_res, list_buf) == -1)
			{
				return NULL;
			}
			//PyList_SET_ITEM(list_res, i, list_buf);
		}
	}

	/*if (intSum)
	{
		A = CreateMatrix(N, N, intA);
		B = CreateMatrix(N, N, intB);

		C = CreateMatrix(N, N, intA);
		for (i = 0; i < C.col * C.row; i++)
			(C.x + i)->x = NULL;
		_C = CreateMatrix(N, N, intA);
		for (i = 0; i < _C.col * _C.row; i++)
			(_C.x + i)->x = NULL;

		InitializeCriticalSection(&cs);
		HANDLE thread1 = CreateThread(NULL, NULL, MultWork, NULL, NULL, NULL);
		HANDLE thread2 = CreateThread(NULL, NULL, MultWork, NULL, NULL, NULL);
		HANDLE thread3 = CreateThread(NULL, NULL, MultWork, NULL, NULL, NULL);
		HANDLE thread4 = CreateThread(NULL, NULL, MultWork, NULL, NULL, NULL);
		WaitForSingleObject(thread1, INFINITE);
		WaitForSingleObject(thread2, INFINITE);
		WaitForSingleObject(thread3, INFINITE);
		WaitForSingleObject(thread4, INFINITE);

		intRes = GetRes(C, N);

		PyObject* list_res = PyList_New(0);
		if (list_res == NULL)
		{
			return NULL;
		}

		for (i = 0; i < N; i++)
		{
			PyObject* list_buf = PyList_New(0);
			if (list_buf == NULL)
			{
				return NULL;
			}
			for (Py_ssize_t k = 0; k < list_len; k++)
			{
				PyObject* value_res = PyLong_FromLongLong(intRes[i][k]);// (!)
				if (value_res == NULL)
				{
					return NULL;
				}

				if (PyList_Append(list_buf, value_res) == -1)
				{
					return NULL;
				}
				PyList_SET_ITEM(list_buf, k, value_res);
			}
			if (PyList_Append(list_res, list_buf) == -1)
			{
				return NULL;
			}
			//PyList_SET_ITEM(list_res, i, list_buf);
		}*/

		free(intA);
		free(intB);
		free(intRes);
		free(floatA);
		free(floatB);
		free(floatRes);

		if (intSum)
		{
			return Py_BuildValue("[O]", list_res);
			//return Py_BuildValue("i", intSum);
		}
		else if (floatSum)
		{
			return Py_BuildValue("[O]", list_res);
			//return Py_BuildValue("f", floatSum);
		}

		return Py_BuildValue("s", "None");


	
}

static char simatrix_docs[] = "product( ): multiply matrix N*N\n";

//DEPRECATED
//static PyMethodDef simatrix_funcs[] = {
//	{"product", (PyCFunction)simatrix_product, METH_VARARGS, simatrix_docs},
//	{NULL, NULL, 0, NULL}
//};

//DEPRECATED
//PyMODINIT_FUNC initsimatrix(void) {
//	Py_InitModule3("simatrix", simatrix_funcs,
//		"Multiply matrix");
//}

static PyMethodDef module_methods[] = {
	{"product", (PyCFunction)simatrix_product,
	 METH_VARARGS, simatrix_docs},
	{NULL}
};

static struct PyModuleDef simatrix =
{
	PyModuleDef_HEAD_INIT,
	"simatrix", /* name of module */
	"usage: simatrix.product(lsMatrixA[N][N], lsMatrixB[N][N])\n", 
	-1,   // size of per-interpreter state of the module, or -1 if the module keeps state in global variables
	module_methods
};

PyMODINIT_FUNC PyInit_simatrix(void)
{
	return PyModule_Create(&simatrix);
}