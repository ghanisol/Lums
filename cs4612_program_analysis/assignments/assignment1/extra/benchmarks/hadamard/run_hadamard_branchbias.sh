clang-3.9 -c -emit-llvm hadamard_test.c -o hadamard_test.bc;
clang-3.9 -c -emit-llvm transform.c -o transform.bc

llvm-link-3.9 hadamard_test.bc transform.bc -o hadamard.bc

opt-3.9 -load ../../../llvm_passes/ProfileBranchBias/build/profile_branch_bias/libProfileBranchBias.so -profilebb hadamard.bc -o hadamard_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/branchbias/BranchBias.cpp -o branchbias.bc

llvm-link-3.9 hadamard_opt.bc branchbias.bc -o hadamard_branchbias.bc

llc-3.9 -filetype=obj hadamard_branchbias.bc -o=hadamard_branchbias.o 

g++ hadamard_branchbias.o -o hadamard_branchbias

./hadamard_branchbias > ../../output/hadamard.branchbias.log

rm *.bc 
rm hadamard_branchbias.o hadamard_branchbias