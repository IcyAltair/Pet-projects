from distutils.core import setup, Extension

setup(name='simatrix', version='1.0',\
      ext_modules=[Extension('simatrix', ['simatrix.c'])])