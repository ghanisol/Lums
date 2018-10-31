clang-3.9 -c -emit-llvm hadamard_test.c -o hadamard_test.bc;
clang-3.9 -c -emit-llvm transform.c -o transform.bc

llvm-link-3.9 hadamard_test.bc transform.bc -o hadamard.bc

opt-3.9 -load ../../../llvm_passes/DynamicInstructionsCount/build/dynamic_instruction_count/libDynamicInstructionsCount.so -dcount hadamard.bc -o hadamard_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/dynamic/dynamic.cpp -o dynamic.bc

llvm-link-3.9 hadamard_opt.bc dynamic.bc -o hadamard_dynamic.bc

llc-3.9 -filetype=obj hadamard_dynamic.bc -o=hadamard_dynamic.o 

g++ hadamard_dynamic.o -o hadamard_dynamic

./hadamard_dynamic > ../../output/hadamard.dynamic.log

rm *.bc 
rm hadamard_dynamic.o hadamard_dynamic
