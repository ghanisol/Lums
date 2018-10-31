clang-3.9 -c -emit-llvm welcome.cpp -o welcome.bc;

opt-3.9 -load ../../../llvm_passes/ProfileBranchBias/build/profile_branch_bias/libProfileBranchBias.so -profilebb welcome.bc -o welcome_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/branchbias/BranchBias.cpp -o branchbias.bc

llvm-link-3.9 welcome_opt.bc branchbias.bc -o welcome_branchbias.bc

llc-3.9 -filetype=obj welcome_branchbias.bc -o=welcome_branchbias.o 

g++ welcome_branchbias.o -o welcome_branchbias

./welcome_branchbias > ../../output/welcome.branchbias.log

rm *.bc
rm welcome_branchbias.o welcome_branchbias
