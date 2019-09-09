 #
# hmm_posterior.py <hmm> <seqs>
#
# Outputs the posterior decodings of the sequences in the fasta file <seqs> using
# the HMM defined in the file <hmm>. The format <hmm> and <seqs> are as described
# in the projects in MLiB Q3/2015.
#
# Christian Storm Pedersen, 08-feb-2015

import sys
import string
from hmm import hmm
from fasta import fasta

m = hmm(sys.argv[1])
d = fasta(sys.argv[2])

print '; Posterior-decodings of %s using HMM %s' % (sys.argv[2], sys.argv[1])
print
for key in sorted(d.keys()):
    x = m.str_to_obs(d[key])

    # Compute Viterbi decoding and its log-likelihood
    post_z, post_logpz = m.posterior_decoding(x)

    print '>' + key
    print d[key]
    print '# ' + m.states_to_str(post_z)
    print '; log P(x,z) = %f' % (post_logpz)
    print
