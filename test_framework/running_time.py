import binding as hmm_binding
import time, sys

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



def standard_test(o, test_setup, start, stop, increment, file, algorithm_version = '', linewidth = 60, **kwargs):
    algorithm_name = test_setup.__name__

    print(f'Testing the following range:', file = sys.stderr)
    for i in range(start, stop, increment):
        print(i*linewidth, end = ' ', file = sys.stderr)
    print('', file = sys.stderr)

    ## Test setup ##
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

    ## Test loop ##
    for i in range(start, stop, increment):
        test_standard_data = [i for i in read_fasta(i, file)]
        print(f'{algorithm_name}\t{i*linewidth}', file = sys.stderr, end = '\t', flush = True)

        for replicate in range(replicates):
            print('r', end = '', file = sys.stderr, flush = True)    
            
            t0 = time.time()
            test_standard_output = test_setup(test_standard_data, **kwargs)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, {algorithm_name}, {algorithm_version}')
        print('', file = sys.stderr, flush = True) # newline

    o.deallocate()






start = 10
stop = 10011
increment = 1000
replicates = 5
file = 'data/pantro3_X.fasta'


print('observations, time, algorithm, variant')


# Viterbi
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.viterbi, start, stop, increment, file, '1D')


# Forward
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.forward, start, stop, increment, file, '1D')


# Backward
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.backward, start, stop, increment, file, '1D') 


# Baum-Welch
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_1it', n_iterations = 1)

o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_2it', n_iterations = 2)

o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_3it', n_iterations = 3)

o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_4it', n_iterations = 4)

o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_5it', n_iterations = 5)

o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.baumWelch, start, stop, increment, file, '1D_6it', n_iterations = 6)






