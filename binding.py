from ctypes import *
import os

"""
TODO
* make getters for the datastructures
* set up tests for each algorithm

"""


class binded_HMM:

    def __init__(self, n_hiddenstates, n_observations, address_to_so = "hmmmlib/build/libHMMLIB.so"):
        
        class HMM(Structure): # Jeg kan ikke finde ud af at definere denne klasse udenfor __init__, medmindre det er udenfor binded_HMM
            """ creates a struct to match HMM """
            _fields_ = [("hiddenStates", c_uint),
                        ("observations", c_uint),
                        ("transitionProbs", POINTER(c_double)),
                        ("emissionProbs", POINTER(c_double)),
                        ("initProbs", POINTER(c_double))]
        
        # Load the shared library into ctypes.
        self.libhmm = CDLL(os.path.abspath(address_to_so))
        
        # Set restypes of needed functions.
        self.libhmm.HMMCreate.restype = POINTER(HMM)
        self.libhmm.valdidateHMM.restype = c_bool
        self.libhmm.printHMM.restype = c_void_p
        self.libhmm.HMMDeallocate.restype = c_void_p

        # Create HMM object
        self.hmm_object = self.libhmm.HMMCreate(n_hiddenstates, n_observations)
        

        """ 
        print('The following variables are accessible from the HMM struct')
        for i in [i for i in dir(hmm_object[0]) if str(i)[0:1] != '_']:
            print('\t', i)
        """


    def presentHMM(self):
        hs = self.hmm_object[0].hiddenStates
        obs = self.hmm_object[0].observations

        print('Presenting the HMM with the presentHMM()-function from the python-binding')
        print(' hiddenStates =', hs)
        print(' observations =', obs)
        
        print()
        print(' initProbs:', [self.hmm_object[0].initProbs[i] for i in range(hs)])


        print()
        print(' transitionProbs: [hs][hs]', end = '\n  ')
        for row in range(hs):
            for col in range(hs):
                print(round(self.hmm_object[0].transitionProbs[row*hs+col], 3), end = '  ')
            print(end = '\n  ')
        print()

        
        print(' emissionProbs: [hs][obs]', end = '\n  ') # [7][4] eller [hs][obs]
        for row in range(hs):
            for col in range(obs):
                print(round(self.hmm_object[0].emissionProbs[row*obs+col], 3), end = '  ')
            print(end = '\n  ') 
        print()
        print(' The internal validation state is:', self.libhmm.valdidateHMM(self.hmm_object))


    ## Setters ##
    def setInitProbs(self, pi):
        if len(pi) != self.hmm_object[0].hiddenStates:
            raise Exception(f'Failed to set initProbs[]. initProbs[] should contain {self.hmm_object[0].hiddenStates} values but {len(pi)} were given.')

        self.hmm_object[0].initProbs = (c_double * self.hmm_object[0].hiddenStates)(*pi)


    def setTransitionProbs(self, new_trans_p):
        if len(new_trans_p) != self.hmm_object[0].hiddenStates:
            raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {self.hmm_object[0].hiddenStates} rows but {len(new_trans_p)} were given.')
        for row in new_trans_p:
            if len(row) != self.hmm_object[0].hiddenStates:
                raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {self.hmm_object[0].hiddenStates} columns but {len(row)} were given.')

        one_dimensional = [j for sub in new_trans_p for j in sub]
        # print(one_dimensional)
        self.hmm_object[0].transitionProbs = (c_double * (self.hmm_object[0].hiddenStates * self.hmm_object[0].hiddenStates))(*one_dimensional)


    def setEmissionProbs(self, new_emiss_p):
        if len(new_emiss_p) != self.hmm_object[0].hiddenStates:
            raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {self.hmm_object[0].hiddenStates} rows but {len(new_emiss_p)} were given.')
        for row in new_emiss_p:
            if len(row) != self.hmm_object[0].observations:
                raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {self.hmm_object[0].observations} columns but {len(row)} were given.')

        one_dimensional = [j for sub in new_emiss_p for j in sub]
        # print(one_dimensional)
        self.hmm_object[0].emissionProbs = (c_double * (self.hmm_object[0].hiddenStates * self.hmm_object[0].observations))(*one_dimensional)


    ## Getters ##
    def getInitProbs(self):
        return [self.hmm_object[0].initProbs[i] for i in range(self.hmm_object[0].hiddenStates)]

    def getTransitionProbs(self):
        hs = self.hmm_object[0].hiddenStates
        return [[self.hmm_object[0].transitionProbs[row * hs + col] for col in range(hs)] for row in range(hs)]

    def getEmissionProbs(self):
        hs = self.hmm_object[0].hiddenStates
        obs = self.hmm_object[0].observations

        return [[self.hmm_object[0].emissionProbs[row*obs + col] for col in range(obs)] for row in range(hs)]
        



    def deallocate(self):
        self.libhmm.HMMDeallocate(self.hmm_object) # Jeg ved ikke hvorfor denne ikke virker???




o = binded_HMM(3, 2)


o.setInitProbs([0.01, 0.20, 0.33])
o.setTransitionProbs([[0.1111, 0.2, 0.3],
                      [0.22, 0.33, 0.44],
                      [0.33, 0.44, 0.555]])

o.setEmissionProbs([[0.1, 0.2],
                  [0.22, 0.33],
                  [0.44, 0.55555555]])

o.presentHMM()


#o.deallocate()  # Jeg ved ikke hvorfor denne ikke virker???

print('getInitProbs:', o.getInitProbs())

print('getTransitionProbs', o.getTransitionProbs())

print('getEmissionProbs', o.getEmissionProbs())
