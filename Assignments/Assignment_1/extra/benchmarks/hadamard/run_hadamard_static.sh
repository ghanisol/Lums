clang-3.9 -c -emit-llvm hadamard_test.c -o hadamard_test.bc
clang-3.9 -c -emit-llvm transform.c -o transform.bc

llvm-link-3.9 hadamard_test.bc transform.bc -o hadamard.bc
llvm-dis-3.9 hadamard.bc

opt-3.9 -load ../../../llvm_passes/StaticInstructionsCount/build/static_instruction_count/libStaticInstructionsCount.so -icount -analyze hadamard.bc -o /dev/null > ../../output/hadamard.static.log

rm *.bc
