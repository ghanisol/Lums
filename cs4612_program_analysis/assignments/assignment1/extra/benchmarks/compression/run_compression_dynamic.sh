clang-3.9 -c -emit-llvm compression.c -o compression.bc;

opt-3.9 -load ../../../llvm_passes/DynamicInstructionsCount/build/dynamic_instruction_count/libDynamicInstructionsCount.so -dcount compression.bc -o compression_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/dynamic/dynamic.cpp -o dynamic.bc

llvm-link-3.9 compression_opt.bc dynamic.bc -o compression_dynamic.bc

llc-3.9 -filetype=obj compression_dynamic.bc -o=compression_dynamic.o 

g++ compression_dynamic.o -o compression_dynamic

./compression_dynamic > ../../output/compression.dynamic.log

rm *.bc 
rm compression_dynamic.o compression_dynamic
