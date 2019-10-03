from ctypes import *
import os

# Load the shared library into c types.
libhmm = CDLL(os.path.abspath("libhmm.so"))


# Tell python how to interpret the structs
class HMM(Structure):
    """ creates a struct to match HMM """
    _fields_ = [("hiddenStates", c_uint),
                ("observations", c_uint),
                ("transitionProbs", POINTER(c_double)),
                ("emissionProbs", POINTER(c_double)),
                ("initProbs", POINTER(c_double))]


# Load library as normal

# New, so Python knows how to interpret result
libhmm.HMMCreate.restype = POINTER(HMM)
# Call, and Python returns pointer to Python definition of struct
_test = libhmm.HMMCreate(6,7)

print('a', dir(_test[0]))
print(_test[0].hiddenStates)

#print(HMM(_test))



libhmm.valdidateHMM.restype = c_bool
print(libhmm.valdidateHMM(_test))


libhmm.printHMM(_test)

