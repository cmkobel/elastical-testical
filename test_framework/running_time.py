import binding as hmm_binding
import time, sys, random

def read_fasta(n_lines, file):
    mapping = {letter: index for index, letter in enumerate(['A', 'C', 'G', 'T'])}
    
    with open(file, 'r') as fasta_file:
        for line_no, line in enumerate(fasta_file):
            if line[0] == '>':
                continue
            elif n_lines == line_no:
                break
            for number in [mapping[i] for i in str(line).upper().strip()]:
                yield number


def random_row(n):
        row = [random.random() for _ in range(n)]
        row_sum = sum(row)
        row = [i/row_sum for i in row]

        return row


def random_matrix(m, n, custom_seed = None):
    if custom_seed != None:
        random.seed(custom_seed)

    print("test")
    
    
    return [random_row(n) for _ in range(m)]

def set_random(object):

    object.setInitProbs(random_row(object.n_hiddenstates))
    object.setTransitionProbs(random_matrix(object.n_hiddenstates, object.n_hiddenstates))
    object.setEmissionProbs(random_matrix(object.n_hiddenstates, object.n_observations))
    return

def set_sparse_1(object):
    object.setInitProbs([0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00])
    object.setTransitionProbs([[0.00, 0.00, 0.90, 0.10, 0.00, 0.00, 0.00],
                        [1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00],
                        [0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00],
                        [0.00, 0.00, 0.05, 0.90, 0.05, 0.00, 0.00],
                        [0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00],
                        [0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00],
                        [0.00, 0.00, 0.00, 0.10, 0.90, 0.00, 0.00]])
    object.setEmissionProbs([[0.30, 0.25, 0.25, 0.20],
                        [0.20, 0.35, 0.15, 0.30],
                        [0.40, 0.15, 0.20, 0.25],
                        [0.25, 0.25, 0.25, 0.25],
                        [0.20, 0.40, 0.30, 0.10],
                        [0.30, 0.20, 0.30, 0.20],
                        [0.15, 0.30, 0.20, 0.35]])


def standard_test(o, test_setup, start, stop, increment, file= '', algorithm_version = '', linewidth = 60, **kwargs):
    algorithm_name = test_setup.__name__

    print(f'Testing the following range:', file = sys.stderr)
    for i in range(start, stop, increment):
        print(i*linewidth, end = ' ', file = sys.stderr)
    print('', file = sys.stderr)

    ## Test setup ##
    """
    o.setInitProbs([0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00])
    o.setTransitionProbs([[0.00, 0.00, 0.90, 0.10, 0.00, 0.00, 0.00],
                        [1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00],
                        [0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00],
                        [0.00, 0.00, 0.05, 0.90, 0.05, 0.00, 0.00],
                        [0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00],
                        [0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00],
                        [0.00, 0.00, 0.00, 0.10, 0.90, 0.00, 0.00]])
    o.setEmissionProbs([[0.30, 0.25, 0.25, 0.20],
                        [0.20, 0.35, 0.15, 0.30],
                        [0.40, 0.15, 0.20, 0.25],
                        [0.25, 0.25, 0.25, 0.25],
                        [0.20, 0.40, 0.30, 0.10],
                        [0.30, 0.20, 0.30, 0.20],
                        [0.15, 0.30, 0.20, 0.35]])
    """



    ## Test loop ##
    for i in range(start, stop, increment):
        test_standard_data = [i for i in read_fasta(i, file)]
        print(f'{algorithm_name}\t{i*linewidth}', file = sys.stderr, end = '\t', flush = True)

        for replicate in range(replicates):
            print('r', end = '', file = sys.stderr, flush = True)    
            
            t0 = time.time()
            test_standard_output = test_setup(test_standard_data, **kwargs)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, {algorithm_name}, {o.hmmType}, {algorithm_version}')
        print('', file = sys.stderr, flush = True) # newline

    o.deallocate()





if __name__ == "__main__" :
        


    start = 10
    stop = 510
    increment = 500
    replicates = 4
    file = '../../test_framework/data/pantro3_X.fasta'


    print('observations, time, algorithm, variant, iterations')

    
    ## Conventional ##
    # Viterbi
    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    set_random(o)
    o.presentHMM()
    """
    standard_test(o, o.viterbi, start, stop, increment, file)

    # Posterior Decoding
    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.posteriorDecoding, start, stop, increment, file)

    # Forward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.forward, start, stop, increment, file)

    # Backward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.backward, start, stop, increment, file) 

    # Baum-Welch
    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '1', n_iterations = 1)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '2', n_iterations = 2)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '3', n_iterations = 3)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '4', n_iterations = 4)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '5', n_iterations = 5)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "Conventional")
    standard_test(o, o.baumWelch, start, stop, increment, file, '6', n_iterations = 6)




    ## BLAS ##


    # Viterbi
    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.viterbi, start, stop, increment, file)

    # Posterior Decoding
    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.posteriorDecoding, start, stop, increment, file)

    # Forward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.forward, start, stop, increment, file)

    # Backward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.backward, start, stop, increment, file) 

    # Baum-Welch
    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '1', n_iterations = 1)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '2', n_iterations = 2)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '3', n_iterations = 3)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '4', n_iterations = 4)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '5', n_iterations = 5)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "BLAS")
    standard_test(o, o.baumWelch, start, stop, increment, file, '6', n_iterations = 6)


    ## CSR ##

    # Viterbi
    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    o.presentHMM()
    standard_test(o, o.viterbi, start, stop, increment, file)

    # Posterior Decoding
    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.posteriorDecoding, start, stop, increment, file)

    # Forward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.forward, start, stop, increment, file)

    # Backward
    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.backward, start, stop, increment, file) 

    # Baum-Welch
    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '1', n_iterations = 1)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '2', n_iterations = 2)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '3', n_iterations = 3)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '4', n_iterations = 4)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '5', n_iterations = 5)

    o = hmm_binding.binded_HMM(7, 4, hmmType = "CSR")
    standard_test(o, o.baumWelch, start, stop, increment, file, '6', n_iterations = 6)











"""