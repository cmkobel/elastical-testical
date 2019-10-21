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



def standard_test(o, test_setup, start, stop, increment, algorithm = '', file = 'data/pantro3_X.fasta', linewidth = 60, **kwargs):
    name = test_setup.__name__
    

    ## Test standard setup ##
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



    print(name)
    ## Test standard loop ##
    for i in range(start, stop, increment):
        test_standard_data = [i for i in read_fasta(i, file)]
        print(f'{name}\t{i*linewidth}', file = sys.stderr, end = '\t', flush = True)

        for replicate in range(replicates):
            print('r', end = '', file = sys.stderr, flush = True)    
            
            t0 = time.time()
            test_standard_output = test_setup(test_standard_data, **kwargs)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, {name}_{algorithm}')
        print('', file = sys.stderr, flush = True) # newline

    o.deallocate()















start = 100
stop = 1101
increment = 500
replicates = 5



# Viterbi
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.viterbi, start, stop, increment, '1D')


# Forward
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.forward, start, stop, increment, '1D')


# Backward
o = hmm_binding.binded_HMM(7, 4)
standard_test(o, o.backward, start, stop, increment, '1D')







o = hmm_binding.binded_HMM(7, 4)
# Baum-Welch
standard_test(o, o.baumWelch, start, stop, increment, '1D', n_iterations = 1)


