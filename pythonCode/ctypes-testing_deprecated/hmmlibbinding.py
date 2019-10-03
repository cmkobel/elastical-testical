import ctypes

import os




testlib = ctypes.CDLL(os.path.abspath('hmmlib.so'))

testlib.my_func()
testlib.test()




pyarr = [1, 2, 3, 4]
arr = (ctypes.c_int * len(pyarr))(*pyarr)

def py2c(input):
    return (ctypes.c_int * len(input))(*input)

testlib.loop_through(py2c([1,2,3,3,4]), 5)