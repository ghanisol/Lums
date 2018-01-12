clang-3.9 -c -emit-llvm gcd.cpp -o gcd.bc;

opt-3.9 -load ../../../llvm_passes/ProfileBranchBias/build/profile_branch_bias/libProfileBranchBias.so -profilebb gcd.bc -o gcd_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/branchbias/BranchBias.cpp -o branchbias.bc

llvm-link-3.9 gcd_opt.bc branchbias.bc -o gcd_branchbias.bc

llc-3.9 -filetype=obj gcd_branchbias.bc -o=gcd_branchbias.o 

g++ gcd_branchbias.o -o gcd_branchbias

./gcd_branchbias > ../../output/gcd.branchbias.log

rm *.bc
rm gcd_branchbias.o gcd_branchbias