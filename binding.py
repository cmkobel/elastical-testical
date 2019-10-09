from ctypes import *
import os



# Load the shared library into ctypes.
libhmm = CDLL(os.path.abspath("hmmmlib/build/libHMMLIB.so"))

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
libhmm.printHMM.restype = c_void_p
libhmm.HMMDeallocate.restype = c_void_p


# Create HMM object
hmm_object = libhmm.HMMCreate(3, 2)

""" 
print('The following variables are accessible from the HMM struct')
for i in [i for i in dir(hmm_object[0]) if str(i)[0:1] != '_']:
    print('\t', i)
 """




#libhmm.HMMDeallocate(hmm_object) # Jeg ved ikke hvorfor denne ikke virker???




"""
TODO:
1. Lav funktion presentHMM(), som præsenterer indholdet af HMMen
2. Opsæt en test med assertions.
3. Lav det om til en klasse som kan importeres i en anden fil.
"""

def presentHMM(hmm_object):
    hs = hmm_object[0].hiddenStates
    obs = hmm_object[0].observations

    print('Presenting the HMM with the presentHMM()-function from the python-binding')
    print(' hiddenStates =', hs)
    print(' observations =', obs)
    
    print()
    print(' initProbs:', [hmm_object[0].initProbs[i] for i in range(hs)])


    print()
    print(' transitionProbs: [hs][hs]', end = '\n  ')
    for row in range(hs):
        for col in range(hs):
            print(round(hmm_object[0].transitionProbs[row*hs+col], 3), end = '  ')
        print(end = '\n  ')
    print()

    
    print(' emissionProbs: [hs][obs]', end = '\n  ') # [7][4] eller [hs][obs]
    for row in range(hs):
        for col in range(obs):
            print(round(hmm_object[0].emissionProbs[row*obs+col], 3), end = '  ')
        print(end = '\n  ') 
    print()
    print(' The internal validation state is:', libhmm.valdidateHMM(hmm_object))


def setInitProbs(hmm_object, pi):
    if len(pi) != hmm_object[0].hiddenStates:
        raise Exception(f'Failed to set initProbs[]. initProbs[] should contain {hmm_object[0].hiddenStates} values but {len(pi)} were given.')

    hmm_object[0].initProbs = (c_double * hmm_object[0].hiddenStates)(*pi)


def setTransitionProbs(hmm_object, new_trans_p):
    if len(new_trans_p) != hmm_object[0].hiddenStates:
        raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {hmm_object[0].hiddenStates} rows but {len(new_trans_p)} were given.')
    for row in new_trans_p:
        if len(row) != hmm_object[0].hiddenStates:
            raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {hmm_object[0].hiddenStates} columns but {len(row)} were given.')

    one_dimensional = [j for sub in new_trans_p for j in sub]
    # print(one_dimensional)
    hmm_object[0].transitionProbs = (c_double * (hmm_object[0].hiddenStates * hmm_object[0].hiddenStates))(*one_dimensional)


def setEmissionProbs(hmm_object, new_emiss_p):
    if len(new_emiss_p) != hmm_object[0].hiddenStates:
        raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {hmm_object[0].hiddenStates} rows but {len(new_emiss_p)} were given.')
    for row in new_emiss_p:
        if len(row) != hmm_object[0].observations:
            raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {hmm_object[0].observations} columns but {len(row)} were given.')

    one_dimensional = [j for sub in new_emiss_p for j in sub]
    # print(one_dimensional)
    hmm_object[0].emissionProbs = (c_double * (hmm_object[0].hiddenStates * hmm_object[0].observations))(*one_dimensional)



setInitProbs(hmm_object, [0.01, 0.20, 0.33])

setEmissionProbs(hmm_object, 
                 [[0.1, 0.2],
                  [0.22, 0.33],
                  [0.44, 0.555]])



setTransitionProbs(hmm_object, 
                 [[0.1, 0.2, 0.3],
                  [0.22, 0.33, 0.44],
                  [0.33, 0.44, 0.555]])


presentHMM(hmm_object)

