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



def running_time_viterbi(start = 1000, stop = 100000, increment = 5000, replicates = 5, file = 'data/pantro3_X.fasta', linewidth = 60):
    ## Test viterbi setup ##
    o = hmm_binding.binded_HMM(7, 4)
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

    ## Test viterbi loop ##
    for i in range(start, stop, increment):
        test_viterbi_data = [i for i in read_fasta(i, file)]
        print(f'viterbi {i}', file = sys.stderr)
        for replicate in range(replicates):
            
            t0 = time.time()
            test_viterbi_output = o.viterbi(test_viterbi_data)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, viterbi_1D')
    o.deallocate()
        





def running_time_forward(start = 1000, stop = 100000, increment = 5000, replicates = 5, file = 'data/pantro3_X.fasta', linewidth = 60):
    ## Test forward setup ##
    o = hmm_binding.binded_HMM(7, 4)
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


    ## Test forward loop ##
    for i in range(start, stop, increment):
        test_forward_data = [i for i in read_fasta(i, file)]
        print(f'forward {i}', file = sys.stderr)
        for replicate in range(replicates):
            
            
            t0 = time.time()
            test_forward_output = o.forward(test_forward_data)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, forward_1D')
    o.deallocate()

        







def running_time_backward(start = 1000, stop = 100000, increment = 5000, replicates = 5, file = 'data/pantro3_X.fasta', linewidth = 60):
    ## Test backward setup ##
    o = hmm_binding.binded_HMM(7, 4)
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


    ## Test backward loop ##
    for i in range(start, stop, increment):
        test_backward_data = [i for i in read_fasta(i, file)]
        print(f'backward {i}', file = sys.stderr)
        for replicate in range(replicates):
            
            
            # collect scalefactors from forward
            scalefactor_from_forward = o.forward(test_backward_data)[1]
            
            t0 = time.time()
            test_backward_output = o.backward(test_backward_data, scalefactor_from_forward)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, backward_1D')
    o.deallocate()




def running_time_baumWelch(start = 1000, stop = 100000, increment = 5000, replicates = 5, file = 'data/pantro3_X.fasta', linewidth = 60, n_iterations = 1):
    ## Test baumWelch setup ##
    o = hmm_binding.binded_HMM(7, 4)
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


    ## Test baumWelch loop ##
    for i in range(start, stop, increment):
        test_baumWelch_data = [i for i in read_fasta(i, file)]
        print(f'baumWelch {i}', file = sys.stderr, end = '\t', flush = True)

        for replicate in range(replicates):
            print('.', end = '', file = sys.stderr, flush = True)    
            
            t0 = time.time()
            test_baumWelch_output = o.baumWelch(test_baumWelch_data, n_iterations)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}, baumWelch_1D_1it')
        print('', file = sys.stderr, flush = True) # newline

    o.deallocate()










start = 1000
stop = 10000
increment = 100
replicates = 3


print('observations, time, algorithm')

print('starting running_time_viterbi', file = sys.stderr)
#running_time_viterbi(start, stop, increment, replicates)

print('starting running_time_forward', file = sys.stderr)
#running_time_forward(start, stop, increment, replicates)

print('starting running_time_backward', file = sys.stderr)
#running_time_backward(start, stop, increment, replicates)

print('starting running_time_baumWelch', file = sys.stderr)
running_time_baumWelch(start, stop, increment, replicates, n_iterations = 1)


