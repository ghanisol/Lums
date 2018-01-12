clang-3.9 -c -emit-llvm compression.c -o compression.bc;

opt-3.9 -load ../../../llvm_passes/ProfileBranchBias/build/profile_branch_bias/libProfileBranchBias.so -profilebb compression.bc -o compression_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/branchbias/BranchBias.cpp -o branchbias.bc

llvm-link-3.9 compression_opt.bc branchbias.bc -o compression_branchbias.bc

llc-3.9 -filetype=obj compression_branchbias.bc -o=compression_branchbias.o 

g++ compression_branchbias.o -o compression_branchbias

./compression_branchbias > ../../output/compression.branchbias.log

rm *.bc
rm compression_branchbias.o compression_branchbias
