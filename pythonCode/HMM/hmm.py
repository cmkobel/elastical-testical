 #
# hmm.py
#
# Implements a HMM class that can initialize a HMM from a file in the format used
# in the projects in MLiB Q3/2015 and rune the basic algorithms (Viterbi, forward,
# backward, and posterior decoding) on this HMM.
#
# joint_prob(x, z):
#    Computes the joint probability of a sequence of observables x and sequence of
#    hidden states z.
#
# log_joint_prob(x, z):
#    Computes the log joint probability of a sequence of observables x and sequence 
#    of hidden states z.
#
# viterbi_decoding(x):
#    Computes the most likey sequence of hidden states z generating the sequence of
#    observables x.
#
# forward_with_scaling(x):
#    Implements the computation of the forward table in a numerical stable manner.
#    Computes the alpha_hat table and the corresponding list of scaling factors as
#    explained in Bishop.
#
# forward_with_log(x):
#    Implements the computation of the forward table in a numerical stable manner.
#    Computes logalpha table cf. Mann2006.

# backward_with_scaling(x, scaling_factor):
#    Implements the computation of the backward table in a numerical stable manner.
#    Computes the beta_hat table using the scaling factors returned when computing
#    the alpha_hat table by forward_with-scaling as explained in Bishop.
#
# backward_with_log(x)
#    Implements the computation of the backward table in a numerical stable manner.
#    Computes logbeta table cf. Mann2006.

# posterior_decoding(x):
#    Computes the posterior decoding of a sequence of observables x using the
#    alpha_hat and beta_hat tables.
#
# posterior_decoding_with_log(x):
#    Computes the posterior decoding of a sequence of observables x using the
#    logalpha and logbeta.
#
# Christian Storm Pedersen
#
# 07-feb-2015 (initial version)
# 17-feb-2015 (added forward and backward using log transform cf. Mann2006)


import sys
import math
import string
import numpy as np
import time

class hmm:
    """
    Implement basic HMM algorithms: Viterbi, forward, backward, and posterior decoding
    """

    def __init__ (self, file):
        """
        Reads in HMM from file in the format used in the projects in MLiB Q3/2015
        """
        lines = [l.strip() for l in open(file).readlines() if (l != '\n' or l[0] != '#')]
        i = 0
        for l in lines:
            if l == 'hidden':
                hidden = lines[i+1].split()
                self.num_of_states = len(hidden)
                self.state_to_index = {}
                self.index_to_state = {}
                for k in range(self.num_of_states):
                    self.state_to_index[hidden[k]] = k
                    self.index_to_state[k] = hidden[k]
            elif l == 'observables':
                obs = lines[i+1].split()
                self.num_of_obs = len(obs)
                self.obs_to_index = {}
                for k in range(self.num_of_obs):
                    self.obs_to_index[obs[k]] = k
            elif l == 'pi':
                self.init_prob = [float(c) for c in lines[i+1].split()]
            elif l == 'transitions':
                self.trans_prob = []
                for k in range(self.num_of_states):
                    self.trans_prob.append([float(c) for c in lines[i+1+k].split()])
            elif l == 'emissions':
                self.emit_prob = []
                for k in range(self.num_of_states):
                    self.emit_prob.append([float(c) for c in lines[i+1+k].split()])
            i = i + 1

    def str_to_obs (self, s):
        """
        Converts a string of observables to list of observables for input to functions
        """
        return [self.obs_to_index[c] for c in list(s)]

    def str_to_states (self, s):
        """
        Converts a string of states to list of states for input to functions
        """
        return [self.state_to_index[c] for c in list(s)]

    def states_to_str (self, z, space = ''):
        """
        Converts a list of observables to string representation for printing
        """
        return string.join([self.index_to_state[c] for c in z], space)
    
    def exp(self, x):
        """
        Returns exp(x) and 0 if x is -ind
        """
        if x == float("-inf"):
            return 0
        else:
            return math.exp(x)
        
    def log(self, x):
        """
        Returns the natural log of x and -inf if x is 0
        """
        if x == 0:
            return float("-inf")
        else:
            return math.log(x)

    def logsum(self, logx, logy):
        """
        Returns log(x+y) cf. algorithm 3 in Mann2006
        """
        if logx == float("-inf"):
            return logy
        elif logy == float("-inf"):
            return logx
        else:
            if logx > logy:
                return logx + self.log(1 + self.exp(logy - logx))
            else:
                return logy + self.log(1 + self.exp(logx - logy))

    def logproduct(self, logx, logy):
        """
        Returns log(x*y) cf. algorithm 4 in Mann2006
        """
        if logx == float("-inf") or logy == float("-inf"):
            return float("-inf")
        else:
            return logx + logy
        
    def arg_max(self, l):
        """
        Returns the index of the maximum element in list l
        """
        max_val, max_index = l[0], 0
        for i in range(1, len(l)):
            if l[i] > max_val:
                max_val, max_index = l[i], i
        return max_index

    def joint_prob(self, x, z):
        """
        Returns the joint probability of x and z
        """
        p = self.init_prob[z[0]] * self.emit_prob[z[0]][x[0]]
        for i in range(1, len(x)):
            p = p * self.trans_prob[z[i-1]][z[i]] * self.emit_prob[z[i]][x[i]]
        return p

    def log_joint_prob(self, x, z):
        """
        Returns the log transformed joint probability of x and z
        """
        logp = self.log(self.init_prob[z[0]]) + self.log(self.emit_prob[z[0]][x[0]])
        for i in range(1, len(x)):
            logp = logp + self.log(self.trans_prob[z[i-1]][z[i]]) + self.log(self.emit_prob[z[i]][x[i]])
        return logp

    def viterbi_decoding(self, x):
        """
        Returns the Viterbi decoding of x and its loglikelihood
        """
        # Allocate dynamic programming table for Viterbi
        w = [ self.num_of_states * [float("-inf")] for i in range(len(x)) ]

        # Compute column 0 (base case)
        for k in range(self.num_of_states):
            w[0][k] = self.log(self.init_prob[k]) + self.log(self.emit_prob[k][x[0]])

        # Compute columns 1..n-1
        for i in range(1, len(x)):
            for k in range(self.num_of_states):
                val = float("-inf")
                for j in range(self.num_of_states):
                    if w[i-1][j] + self.log(self.trans_prob[j][k]) > val:
                        val = w[i-1][j] + self.log(self.trans_prob[j][k])
                w[i][k] = self.log(self.emit_prob[k][x[i]]) + val               

        # Backtracking
        z = len(x) * [None]
        z[len(z)-1] = self.arg_max(w[len(z)-1])
        for i in range(len(z)-1, 0, -1):
            for j in range(self.num_of_states):
                if w[i-1][j] + self.log(self.trans_prob[j][z[i]]) + self.log(self.emit_prob[z[i]][x[i]]) == w[i][z[i]]:
                    z[i-1] = j
                    break

        return z, w[-1][z[-1]]
        
    def forward_without_scaling(self, x):
        """
        Returns the alpha_hat table and scaling factors as explained in Bishop
        """
        # Allocate dynamic programming table for forward
        alpha_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]

        # Compute column 0 (base case)
        for k in range(self.num_of_states):
            alpha_hat[0][k] = self.init_prob[k] * self.emit_prob[k][x[0]]

        # Compute column 1..n-1
        for i in range(1, len(x)):
            for k in range(self.num_of_states):
                val = 0
                if self.emit_prob[k][x[i]] > 0:
                    for j in range(self.num_of_states):
                        val = val + alpha_hat[i-1][j] * self.trans_prob[j][k]
                    val = val * self.emit_prob[k][x[i]]
                alpha_hat[i][k] = val

        return alpha_hat
        
    
    def forward_using_matrix(self, x):
        """
        Returns the alpha_hat table and scaling factors as explained in Bishop
        """
        # Allocate dynamic programming table for forward
        alpha_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]
        
        emits = [[[self.emit_prob[0][0], 0],[0, self.emit_prob[1][0]]], [[self.emit_prob[0][1], 0],[0, self.emit_prob[1][1]]]]
        
        alpha_hat[0] = np.dot(self.init_prob, emits[0])
        alpha_hat[0] = alpha_hat[0]*(1/np.sum(alpha_hat[0]))
        scaling_factor = [0.0]*len(x)
        
        timenow = time.time()

        for i in range(1, len(x)):
            alpha_hat[i] = np.dot(emits[x[i]], np.dot(alpha_hat[i-1],self.trans_prob))
            scaling_factor[i] = (1/np.sum(alpha_hat[i]))
            alpha_hat[i] = alpha_hat[i]*scaling_factor[i]
            #alpha_hat[i] = alpha_hat[i]*(1/np.sum(alpha_hat[i]))
        print(time.time()-timenow)
        
        return alpha_hat, scaling_factor
        
        

    def forward_with_scaling(self, x):
        """
        Returns the alpha_hat table and scaling factors as explained in Bishop
        """
        # Allocate dynamic programming table for forward
        alpha_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]

        # Allocate vector for scaling factors
        scaling_factor = [0.0] * len(x)

        # Compute column 0 (base case)
        for k in range(self.num_of_states):
            alpha_hat[0][k] = self.init_prob[k] * self.emit_prob[k][x[0]]
            scaling_factor[0] = scaling_factor[0] + alpha_hat[0][k]
        for k in range(self.num_of_states):
            alpha_hat[0][k] = alpha_hat[0][k] / scaling_factor[0]

        # Compute column 1..n-1
        for i in range(1, len(x)):
            for k in range(self.num_of_states):
                val = 0
                if self.emit_prob[k][x[i]] > 0:
                    for j in range(self.num_of_states):
                        val = val + alpha_hat[i-1][j] * self.trans_prob[j][k]
                    val = val * self.emit_prob[k][x[i]]
                alpha_hat[i][k] = val
                scaling_factor[i] = scaling_factor[i] + alpha_hat[i][k]
            #print(alpha_hat[i])
            for k in range(self.num_of_states):
                alpha_hat[i][k] = alpha_hat[i][k] / scaling_factor[i]

        return alpha_hat, scaling_factor

    def forward_with_log(self, x):
        """
        Returns the log-transformed alpha table computed cf. algorithm 5 in Mann 2006
        """
        # Allocate dynamic programming table for forward
        logalpha = [ self.num_of_states * [float("-inf")] for i in range(len(x)) ]

        # Compute column 0 (base case)
        for k in range(self.num_of_states):
            logalpha[0][k] = self.logproduct(self.log(self.init_prob[k]), self.log(self.emit_prob[k][x[0]]))

        # Compute column 1..n-1
        for i in range(1, len(x)):
            for k in range(self.num_of_states):
                logval = float("-inf")
                if self.emit_prob[k][x[i]] > 0:
                    for j in range(self.num_of_states):
                        logval = self.logsum(logval, self.logproduct(logalpha[i-1][j], self.log(self.trans_prob[j][k])))
                    logval = self.logproduct(logval, self.log(self.emit_prob[k][x[i]]))
                logalpha[i][k] = logval

        return logalpha
        
    def backward_using_matrix(self, x, scaling):
        """
        Returns the beta_hat table as explained in Bishop. Needs the list of scaling factors computed by forward
        """
        # Allocate dynamic programming table for forward
        beta_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]

        # Compute column n-1 (base case)
        beta_hat[len(x)-1] = self.num_of_states*[1.0]
        
        emits = [[[self.emit_prob[0][0], 0],[0, self.emit_prob[1][0]]], [[self.emit_prob[0][1], 0],[0, self.emit_prob[1][1]]]]
        
        # Compute column n-2..0
        for i in range(len(x)-2, -1, -1):
            beta_hat[i] = np.dot(beta_hat[i+1], np.dot(self.trans_prob,emits[x[i+1]]).transpose())
            beta_hat[i] = beta_hat[i]*scaling[i+1]
        return beta_hat
        
    def backward_without_scaling(self, x):
        """
        Returns the beta_hat table as explained in Bishop. Needs the list of scaling factors computed by forward
        """
        # Allocate dynamic programming table for forward
        beta_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]

        # Compute column n-1 (base case)
        for k in range(self.num_of_states):
            beta_hat[len(x)-1][k] = 1

        # Compute column n-2..0
        for i in range(len(x)-2, -1, -1):
            for k in range(self.num_of_states):
                val = 0
                for j in range(self.num_of_states):
                    val = val + beta_hat[i+1][j] * self.emit_prob[j][x[i+1]] * self.trans_prob[k][j]
                beta_hat[i][k] = val

        return beta_hat
    
    def backward_with_scaling(self, x, scaling_factor):
        """
        Returns the beta_hat table as explained in Bishop. Needs the list of scaling factors computed by forward
        """
        # Allocate dynamic programming table for forward
        beta_hat = [ self.num_of_states * [0.0] for i in range(len(x)) ]

        # Compute column n-1 (base case)
        for k in range(self.num_of_states):
            beta_hat[len(x)-1][k] = 1

        # Compute column n-2..0
        for i in range(len(x)-2, -1, -1):
            for k in range(self.num_of_states):
                val = 0
                for j in range(self.num_of_states):
                    val = val + beta_hat[i+1][j] * self.emit_prob[j][x[i+1]] * self.trans_prob[k][j]
                beta_hat[i][k] = val / scaling_factor[i+1]

        return beta_hat

    def backward_with_log(self, x):
        """
        Returns the log-transformed beta table computed cf. algorithm 6 in Mann 2006
        """
        # Allocate dynamic programming table for forward
        logbeta = [ self.num_of_states * [float("-inf")] for i in range(len(x)) ]

        # Compute column n-1 (base case)
        for k in range(self.num_of_states):
            logbeta[len(x)-1][k] = 0.0

        # Compute column n-2..0
        for i in range(len(x)-2, -1, -1):
            for k in range(self.num_of_states):
                logval = float("-inf")
                for j in range(self.num_of_states):
                    logval = self.logsum(logval, \
                                    self.logproduct(logbeta[i+1][j], \
                                    self.logproduct(self.log(self.emit_prob[j][x[i+1]]), self.log(self.trans_prob[k][j]))))
                logbeta[i][k] = logval

        return logbeta
   
    def posterior_decoding(self, x):
        """
        Returns the posterior decoding of x and its loglikelihood (which might be -inf if the decoding is not a possible path)
        """
        alpha_hat, scaling_factor = self.forward_with_scaling(x)
        beta_hat = self.backward_with_scaling(x, scaling_factor)

        z = [None] * len(x)
        posterior = [0.0] * self.num_of_states
        for i in range(len(x)):
            for k in range(self.num_of_states):
                posterior[k] = alpha_hat[i][k] * beta_hat[i][k]
            z[i] = self.arg_max(posterior)

        return z, self.log_joint_prob(x, z)

    def posterior_decoding_with_log(self, x):
        """
        Returns the posterior decoding of x (computed using forward and backward with log transform) and
        its loglikelihood (which might be -inf if the decoding is not a possible path)
        """
        logalpha = self.forward_with_log(x)
        logbeta = self.backward_with_log(x)

        z = [None] * len(x)
        logposterior = [0.0] * self.num_of_states
        for i in range(len(x)):
            for k in range(self.num_of_states):
                logposterior[k] = logalpha[i][k] + logbeta[i][k]
            z[i] = self.arg_max(logposterior)

        return z, self.log_joint_prob(x, z)
        
    def output (self):
        """
        Very crude ouput of the (internal) representation of the hmm.
        """
        print (self.no_of_states)
        print (self.state_to_index)
        print (self.index_to_state)
        print ()
        print (self.no_of_obs)
        print (self.obs_to_index)
        print ()
        print (self.init_prob)
        print ()
        print (self.trans_prob)
        print ()
        print (self.emit_prob)

if __name__ == '__main__':

    # Read HMM from file
    m = hmm(sys.argv[1])

    # Get sequence of observables from command line
    x = m.str_to_obs(sys.argv[2])

    # Compute Viterbi decoding and its log-likelihood
    vit_z, vit_logpz = m.viterbi_decoding(x)

    # Compute Posterior decoding and its log-likelihood (using forward and backward with scaling)
    post_z, post_logpz = m.posterior_decoding(x)

    # Compute Posterior decoding and its log-likelihood (using forward and backward with log transform)
    logpost_z, logpost_logpz = m.posterior_decoding_with_log(x)
    
    # Output the results
    print ("loglikelihood of viterbi decoding:", vit_logpz)
    print ("Joint loglikelihood of (x,z):", m.log_joint_prob(x, vit_z))
    print ("Viterbi decoding of x:\n", m.states_to_str(vit_z))
    print ("loglikelihood of posterior decoding (using scaling):", post_logpz)
    print ("Posterior decoding of x (using scaling):", m.states_to_str(post_z))
    print ("loglikelihood of posterior decoding (using log):", logpost_logpz)
    print ("Posterior decoding of x (using log):    ", m.states_to_str(logpost_z))

