import ctypes



testlib = ctypes.CDLL('/home/arabthal/bioinformatics/hmm/git_repo_hmmmlib/hmmmlib/build/libHMMLIB.so')

testlib.main_test()

