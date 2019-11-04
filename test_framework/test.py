from binding import *
from copy import copy

## These tests are equivalent to the ones in main_test.c
## Made in order to check that the python-binding is successfull.

def test_viterbi():
    # create HMM for testing viterbi
    o = binded_HMM(7, 4)
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

    test_viterbi_data = [3, 0, 2, 0, 2, 3, 3, 2, 3, 3, 2, 1, 3, 1, 0, 2, 3, 1, 0, 1, 0, 1, 0, 1, 3, 0, 1, 0, 2, 1, 0, 3, 0, 0, 0, 2, 3, 2, 0, 3, 0, 2, 3, 0, 2, 3, 0, 2, 2, 0, 1, 0, 2, 1, 0, 0, 3, 1, 2, 3, 1, 0, 3, 1, 0, 3, 1, 2, 0, 1, 0, 2, 0, 2, 1, 3, 0, 1, 2, 0, 3, 1, 0, 2, 3, 0, 2, 0, 0, 2, 0, 1, 0, 3, 1, 0, 3, 0, 0]
    test_viterbi_output = o.viterbi(test_viterbi_data)
    test_viterbi_expected = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1]
    for i, j in zip(test_viterbi_output, test_viterbi_expected):
        assert i == j

    returnvalue = copy(o.validate())
    o.deallocate()
    return returnvalue



def test_posterior_decoding():
    # create HMM for testing posterior_decoding
    o = binded_HMM(7, 4)
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

    test_posterior_decoding_data = [0, 1, 3, 3, 2, 1, 2, 3, 0, 0, 1, 2, 1, 0, 2, 3, 0, 1, 3, 1, 2, 0, 3, 1, 2, 0, 3, 1, 2, 3, 0, 1, 2, 1, 0, 3, 2, 1, 0, 0, 1, 0, 3, 2, 0, 3, 0, 0, 0, 3, 1, 1, 0, 0, 3, 1, 0, 3, 1, 0, 3, 0, 1, 0, 3, 2, 0, 1, 0, 3, 1, 0, 2, 1, 3, 0, 2, 1, 0, 3, 2, 0, 1, 2, 0, 3, 1, 0, 2, 3, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 3, 1, 2, 3, 0]
    test_posterior_decoding_output = o.posterior_decoding(test_posterior_decoding_data)
    test_posterior_decoding_expected = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0]
    for i, j in zip(test_posterior_decoding_output, test_posterior_decoding_expected):
        assert i == j

    returnvalue = copy(o.validate())
    o.deallocate()
    return returnvalue





def test_forward():
    o2 = binded_HMM(2, 2)
    o2.setInitProbs([.2, .8])
    o2.setTransitionProbs([[0.5, 0.5],
                        [0.3, 0.7]])
    o2.setEmissionProbs([[.3, .7],
                        [.8, .2]])
    test_for_back_bw_data = [0, 0, 0, 0, 0, 1, 1, 0, 0, 0]

    test_forward_output, scalefactor_from_forward = o2.forward(test_for_back_bw_data)
    test_forward_expected = [0.085714, 0.148330, 0.155707, 0.156585, 0.156690, 0.634280, 0.722736, 0.230843, 0.165653, 0.157773, 0.914286, 0.851670, 0.844293, 0.843415, 0.843310, 0.365720, 0.277264, 0.769157, 0.834347, 0.842227]
    for i, j in zip(test_forward_output, test_forward_expected):
        assert (i - j) < 0.00001
    assert o2.validate()

    return o2.validate()





def test_backward():
    o2 = binded_HMM(2, 2)
    o2.setInitProbs([.2, .8])
    o2.setTransitionProbs([[0.5, 0.5],
                        [0.3, 0.7]])
    o2.setEmissionProbs([[.3, .7],
                        [.8, .2]])
    test_for_back_bw_data = [0, 0, 0, 0, 0, 1, 1, 0, 0, 0]


    test_forward_output, scalefactor_from_forward = o2.forward(test_for_back_bw_data)


    test_backward_output = o2.backward(test_for_back_bw_data, scalefactor_from_forward)
    test_backward_expected = [0.838486, 0.848495, 0.854859, 0.898964, 1.267584, 1.076550, 0.944879, 0.862481, 0.868282, 1.000000, 1.015142, 1.026387, 1.026767, 1.018758, 0.950282, 0.867237, 1.143683, 1.041273, 1.026152, 1.000000]
    for i, j, in zip(test_backward_output, test_backward_expected):
        assert (i - j) < 0.00001
    assert o2.validate()

    return o2.validate()








def test_baumwelch():
    o2 = binded_HMM(2, 2)
    o2.setInitProbs([.2, .8])
    o2.setTransitionProbs([[0.5, 0.5],
                        [0.3, 0.7]])
    o2.setEmissionProbs([[.3, .7],
                        [.8, .2]])
    test_for_back_bw_data = [0, 0, 0, 0, 0, 1, 1, 0, 0, 0]


    test_baumwelch_output = o2.baumWelch(test_for_back_bw_data, 1)

    epsilon = 0.000001
    assert o2.hmm[0].transitionProbs[0] - 0.43921478415604948 < epsilon
    assert o2.hmm[0].transitionProbs[1*o2.hmm[0].hiddenStates + 1] - 0.78554317773503979 < epsilon
    assert o2.hmm[0].emissionProbs[0] - 0.46160107308583781 < epsilon
    assert o2.hmm[0].emissionProbs[1*o2.hmm[0].observations + 1] - 0.084984433203479412 < epsilon
    assert o2.validate()

    return o2.validate()



print('viterbi', test_viterbi())
"""
print('fw', test_forward())
print('bw', test_backward())
print('baumwelch', test_baumwelch()) """