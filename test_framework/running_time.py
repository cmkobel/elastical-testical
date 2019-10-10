import binding as hmm_binding
import time

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
    print('observations, time')
    for i in range(start, stop, increment):
        test_viterbi_data = [i for i in read_fasta(i, file)]
        for replicate in range(replicates):
            
            t0 = time.time()
            test_viterbi_output = o.viterbi(test_viterbi_data)
            t1 = time.time()
            print(f'{i*linewidth}, {t1-t0}')
        
        #print(test_viterbi_output[:100])


running_time_viterbi(1000000, 2000000, 1000000)


