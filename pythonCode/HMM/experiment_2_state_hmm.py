from hmm import hmm

m = hmm("hmm-2-state.txt")

alpha, scale = m.forward_with_scaling([0, 0, 0, 0, 0, 1, 1, 0, 0, 0])

for i in alpha:
    print(i)

for i in scale:
    print(i)

beta = m.backward_with_scaling([0, 0, 0, 0, 0, 1, 1, 0, 0, 0], scale)

for i in beta:
    print(i)
