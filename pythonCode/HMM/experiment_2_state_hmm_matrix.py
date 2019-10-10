from hmm import hmm

m = hmm("hmm-2-state.txt")

"""

    #
    # 2-state HMM
    #

    hidden
    1 2

    observables
    A C

    pi
    0.2 0.8

    transitions
    0.5 0.5
    0.3 0.7

    emissions
    0.3 0.7
    0.8 0.2

"""
print("\n\nFORWARD:")
alpha, scale = m.forward_with_scaling([0, 0, 0, 0, 0, 1, 1, 0, 0, 0])
print("""\nUsing forloops""")
for i in alpha:
    print(i)
    
print("\n\n")
alpha, scaling = m.forward_using_matrix([0, 0, 0, 0, 0, 1, 1, 0, 0, 0])
print("""\nUsing Matrix """)
for i in alpha:
    print(i)

print("\n\nBACKWARD:")
beta = m.backward_with_scaling([0, 0, 0, 0, 0, 1, 1, 0, 0, 0], scale)
print("""\nUsing forloops - no scaling""")
for i in beta:
    print(i)
    
beta = m.backward_using_matrix([0, 0, 0, 0, 0, 1, 1, 0, 0, 0], scaling)
print("""\nUsing matrix - no scaling""")
for i in beta:
    print(i)

