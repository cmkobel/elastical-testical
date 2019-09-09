#
# hmm_jointprob.py <hmm> <seqs_and_decodings>
#
# Outputs the joint probability of the sequences and corresponding decodings in the
# file <seqs_and_decodings> using the HMM defined in the file <hmm>. The format <hmm>
# and <seqs_and_decodings> are as described in the projects in MLiB Q3/2015.
#
# Christian Storm Pedersen, 08-feb-2015

import sys
import string
from hmm import hmm
from fasta import fasta

m = hmm(sys.argv[1])
d = fasta(sys.argv[2])

for key in sorted(d.keys()):
    x, z = [s.strip() for s in d[key].split('#')]
    x = m.str_to_obs(x)
    z = m.str_to_states(z)
    
    if len(x) != len(z):
        print ("ERROR: The sequence of observables and hidden states for %s have different lenghts!" % (key))
        sys.exit(1)

    print (">" + key)
    print ("p(x,z) = ", m.joint_prob(x, z))
#   print ("log p(x,z) = ", m.log_joint_prob(x, z))
    print ()
