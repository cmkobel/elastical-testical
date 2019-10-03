from ctypes import *
import os


# Load the shared library into ctypes.
libhmm = CDLL(os.path.abspath("libhmm.so"))

# 
class HMM(Structure):
    """ creates a struct to match HMM """
    _fields_ = [("hiddenStates", c_uint),
                ("observations", c_uint),
                ("transitionProbs", POINTER(c_double)),
                ("emissionProbs", POINTER(c_double)),
                ("initProbs", POINTER(c_double))]



# Tell python the restypes of needed functions.
libhmm.HMMCreate.restype = POINTER(HMM)
libhmm.valdidateHMM.restype = c_bool
#libhmm.printHMM.restype = c_void_p
#libhmm.HMMDeallocate.restype = c_void_p


# Create HMM object
hmm_object = libhmm.HMMCreate(6,7)
#print(dir(hmm_object[0]))


print('hiddenStates =', hmm_object[0].hiddenStates)
print('observations =', hmm_object[0].observations)

print('The following variables are accessible from the HMM struct')
for i in [i for i in dir(hmm_object[0]) if str(i)[0:1] != '_']:
    print('\t', i)


print('Validation of the hmm yields:', libhmm.valdidateHMM(hmm_object))


libhmm.printHMM(hmm_object)


#libhmm.HMMDeallocate(hmm_object)



## Test ##

for i in range(10):
    # Jeg ved ikke om det her en den rigtige måde at printe et array på.
    print(hmm_object[0].initProbs[i])
    
new_init_probs = (c_double * 7)(0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00)
hmm_object[0].initProbs = new_init_probs


print('efter indsættelse af ny')
for i in range(7):
    # Jeg ved ikke om det her en den rigtige måde at printe et array på.
    print(hmm_object[0].initProbs[i])