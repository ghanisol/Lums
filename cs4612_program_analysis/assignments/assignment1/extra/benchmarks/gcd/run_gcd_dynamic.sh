clang-3.9 -c -emit-llvm gcd.cpp -o gcd.bc;

opt-3.9 -load ../../../llvm_passes/DynamicInstructionsCount/build/dynamic_instruction_count/libDynamicInstructionsCount.so -dcount gcd.bc -o gcd_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/dynamic/dynamic.cpp -o dynamic.bc

llvm-link-3.9 gcd_opt.bc dynamic.bc -o gcd_dynamic.bc

llc-3.9 -filetype=obj gcd_dynamic.bc -o=gcd_dynamic.o 

g++ gcd_dynamic.o -o gcd_dynamic

./gcd_dynamic > ../../output/gcd.dynamic.log

rm *.bc
rm gcd_dynamic.o gcd_dynamic
