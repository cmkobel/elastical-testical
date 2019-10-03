from ctypes import *
import os

# Load the shared library into c types.
libhmm = CDLL(os.path.abspath("libhmm.so"))


# Tell python how to interpret the structs
class HMM(Structure):
    _fields_ = [("hiddenStates", c_uint64),
                ("observations", c_uint),
                ("transitionProbs", POINTER(c_double)),
                ("emissionProbs", POINTER(c_double)),
                ("initProbs", POINTER(c_double))]


hmm_object = libhmm.HMMCreate(7, 7)


print(HMM(hmm_object).hiddenStates)
print(HMM(hmm_object)._fields_)
