import ctypes as c
import os

# authors: Thornado & Carl Koder

"""
TODO
* make getters for the datastructures
* set up tests for each algorithm

"""

class HMM(c.Structure): 
    """ creates a struct to match HMM """
    _fields_ = [("hiddenStates", c.c_uint),
                ("observations", c.c_uint),
                ("transitionProbs", c.POINTER(c.c_double)),
                ("emissionProbs", c.POINTER(c.c_double)),
                ("initProbs", c.POINTER(c.c_double))]

class binded_HMM:

    def __init__(self, n_hiddenstates, n_observations, address_to_so = "../../hmmmlib/build/libHMMLIB.so", hmmType = None):
        
        
        # Load the shared library into ctypes.
        self.libhmm = c.CDLL(os.path.abspath(address_to_so))
        
        # Set restypes for internal functions.
        #self.libhmm.HMMCreate.restype = c.POINTER(HMM)
        self.libhmm.HMMConventional.restype = c.POINTER(HMM)
        self.libhmm.HMMBLAS.restype = c.POINTER(HMM)
        
        self.libhmm.valdidateHMM.restype = c.c_bool
        self.libhmm.printHMM.restype = c.c_void_p
        self.libhmm.HMMDeallocate.restype = c.c_void_p

        # Set restypes for algorithms.
        #self.libhmm.forward.restype = c.POINTER(c.c_double)
        self.libhmm.F.restype = c.c_void_p
        self.libhmm.B.restype = c.c_void_p
        self.libhmm.viterbi.restype = c.POINTER(c.c_uint)
        self.libhmm.baumWelch.restype = c.c_void_p
        self.libhmm.posteriorDecoding.restype = c.POINTER(c.c_uint)


        # Create HMM object
        if hmmType == None:
            print("Warning, the hmmType defaults to Conventional when none is given.")

        if hmmType == "Conventional" or hmmType == None:
            self.hmm = self.libhmm.HMMConventional(n_hiddenstates, n_observations)
            #print(" (A conventional hmm was created)")
        elif hmmType == "BLAS":
            self.hmm = self.libhmm.HMMBLAS(n_hiddenstates, n_observations)
            #print(" (A BLAS hmm was created)")

        """ 
        print('The following variables are accessible from the HMM struct')
        for i in [i for i in dir(hmm[0]) if str(i)[0:1] != '_']:
            print('\t', i)
        """


    def presentHMM(self):
        hs = self.hmm[0].hiddenStates
        obs = self.hmm[0].observations

        print('Presenting the HMM with the presentHMM()-function from the python-binding')
        print(' hiddenStates =', hs)
        print(' observations =', obs)
        
        print()
        formattedInitProbs = ["{:7.3f}".format(self.hmm[0].initProbs[i]) for i in range(hs)]
        print(' initProbs:', ''.join(formattedInitProbs))


        print()
        print(' transitionProbs: [hs][hs]', end = '\n  ')
        for row in range(hs):
            for col in range(hs):
                print("{:7.3f}".format(self.hmm[0].transitionProbs[row*hs+col]), end = ' ')
            print(end = '\n  ')
        print()

        
        print(' emissionProbs: [hs][obs]', end = '\n  ') # [7][4] eller [hs][obs]
        for row in range(hs):
            for col in range(obs):
                #print(round(self.hmm[0].emissionProbs[row*obs+col], 3), end = '  ')
                print("{:7.3f}".format(self.hmm[0].emissionProbs[row*obs+col]), end = ' ')
            print(end = '\n  ') 
        print()
        print(' The internal validation state is:', self.libhmm.valdidateHMM(self.hmm))

    def validate(self):
        return self.libhmm.valdidateHMM(self.hmm)

    ## Setters ##
    def setInitProbs(self, pi):
        if len(pi) != self.hmm[0].hiddenStates:
            #raise Exception(f'Failed to set initProbs[]. initProbs[] should contain {self.hmm[0].hiddenStates} values but {len(pi)} were given.')
            pass
        self.hmm[0].initProbs = (c.c_double * self.hmm[0].hiddenStates)(*pi)


    def setTransitionProbs(self, new_trans_p):
        if len(new_trans_p) != self.hmm[0].hiddenStates:
            raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {self.hmm[0].hiddenStates} rows but {len(new_trans_p)} were given.')
        for row in new_trans_p:
            if len(row) != self.hmm[0].hiddenStates:
                raise Exception(f'Failed to set transitionProbs[]. transitionProbs[] should contain {self.hmm[0].hiddenStates} columns but {len(row)} were given.')

        one_dimensional = [j for sub in new_trans_p for j in sub]
        # print(one_dimensional)
        self.hmm[0].transitionProbs = (c.c_double * (self.hmm[0].hiddenStates * self.hmm[0].hiddenStates))(*one_dimensional)


    def setEmissionProbs(self, new_emiss_p):
        if len(new_emiss_p) != self.hmm[0].hiddenStates:
            raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {self.hmm[0].hiddenStates} rows but {len(new_emiss_p)} were given.')
        for row in new_emiss_p:
            if len(row) != self.hmm[0].observations:
                raise Exception(f'Failed to set emissionProbs[]. emissionProbs[] should contain {self.hmm[0].observations} columns but {len(row)} were given.')

        one_dimensional = [j for sub in new_emiss_p for j in sub]
        # print(one_dimensional)
        self.hmm[0].emissionProbs = (c.c_double * (self.hmm[0].hiddenStates * self.hmm[0].observations))(*one_dimensional)


    ## Getters ##
    def getInitProbs(self):
        return [self.hmm[0].initProbs[i] for i in range(self.hmm[0].hiddenStates)]

    def getTransitionProbs(self):
        hs = self.hmm[0].hiddenStates
        return [[self.hmm[0].transitionProbs[row * hs + col] for col in range(hs)] for row in range(hs)]

    def getEmissionProbs(self):
        hs = self.hmm[0].hiddenStates
        obs = self.hmm[0].observations
        return [[self.hmm[0].emissionProbs[row*obs + col] for col in range(obs)] for row in range(hs)]
        

    ## Algorithms ##
    def forward(self, observation_data, as_pointers = True):
        """ Returns a tuple. 1: pointer to alpha 2: Pointer to scalefactor """
        
        hs = self.hmm[0].hiddenStates
        
        scalefactor = len(observation_data) * [0]
        scalefactor_c = (c.c_double * len(observation_data))(*scalefactor)

        # empty alpha matrix
        alpha_matrix = len(observation_data) * hs * [0]
        alpha_matrix_c = (len(observation_data) * hs * c.c_double)(*alpha_matrix)
        
    
        self.libhmm.F(self.hmm,
                      (c.c_int * len(observation_data))(*observation_data),
                      len(observation_data),
                      scalefactor_c,
                      alpha_matrix_c)
        
        return alpha_matrix_c, scalefactor_c
    
    def backward(self, observation_data, scalefactor_c = None, as_pointers = True):
        """ Returns a tuple. 1: pointer to alpha 2: Pointer to scalefactor_c """
    
        if scalefactor_c == None: # Compute scalefactor yourself
            scalefactor_c = self.forward(observation_data)[1]
        
        hs = self.hmm[0].hiddenStates

        
        # empty beta matrix
        beta_matrix = len(observation_data) * hs * [0]
        beta_matrix_c = (len(observation_data) * hs * c.c_double)(*beta_matrix)
        
    
        self.libhmm.B(self.hmm,
                      (c.c_int * len(observation_data))(*observation_data),
                      len(observation_data),
                      scalefactor_c,
                      beta_matrix_c)
        
        return beta_matrix_c, scalefactor_c

    def obackward(self, observation_data, alpha_from_forward, scalefactor_from_forward = None):
        """ Inputs: 1: observation data: a list of integers, 2: scalefactors
                for each columnn in observation data provided from forward. If
                not supplied, the scalefactors will be retrieved automatically, 
                though this may be a waste of resources if already computed.
            Outputs: Returns the table denoting the probability of each 
                state for each observation. 2: The scalefactors used for each 
                column in said table. """
        
        if scalefactor_from_forward == None: # retrieve scalefactors automatically
            scalefactor = len(observation_data) * [0]
            scalefactor_from_forward = (c.c_double * len(observation_data))(*scalefactor)
            output = self.libhmm.forward(self.hmm,
                                         (c.c_int * len(observation_data))(*observation_data),
                                         len(observation_data),
                                         scalefactor_from_forward,
                                         (c.c_double * len(observation_data))( *(len(observation_data) * [0] )))
        


        output = self.libhmm.backward(self.hmm,
                                     (c.c_int * len(observation_data))(*observation_data),
                                     len(observation_data),
                                     (c.c_double * len(observation_data))(*scalefactor_from_forward))
        return [output[i] for i in range(len(observation_data)*self.hmm[0].hiddenStates)] # Evt. generator?
    

    def viterbi(self, observation_data):
        output = self.libhmm.viterbi(self.hmm,
                                     (c.c_uint * len(observation_data))(*observation_data),
                                     len(observation_data)) 
        return [output[i] for i in range(len(observation_data))] # Evt. generator?


    def posteriorDecoding(self, observation_data):
        output = self.libhmm.posteriorDecoding(self.hmm,
                                               (c.c_uint * len(observation_data))(*observation_data),
                                               len(observation_data)) 
        return [output[i] for i in range(len(observation_data))] # Evt. generator?


    
    
    def baumWelch(self, observation_data, n_iterations):
        output = self.libhmm.baumWelch(self.hmm,
                                       (c.c_int * len(observation_data))(*observation_data),
                                       len(observation_data),
                                       n_iterations)
        return True


    """ 
    def posteriorDecoding(self, observation_data):
        output = self.libhmm.posteriorDecoding(self.hmm,
                                               (c.c_int * len(observation_data))(*observation_data),
                                               len(observation_data))
        return [output[i] for i in range(len(observation_data))]
     """





    def deallocate(self):
        
        c_struct = c.POINTER(HMM)(self.hmm)
        self.libhmm.HMMDeallocate(c_struct) # Jeg ved ikke hvorfor denne ikke virker???




