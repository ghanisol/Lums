clang-3.9 -c -emit-llvm welcome.cpp -o welcome.bc;

opt-3.9 -load ../../../llvm_passes/DynamicInstructionsCount/build/dynamic_instruction_count/libDynamicInstructionsCount.so -dcount welcome.bc -o welcome_opt.bc;

clang-3.9 -c -emit-llvm ../../instrumentation/dynamic/dynamic.cpp -o dynamic.bc

llvm-link-3.9 welcome_opt.bc dynamic.bc -o welcome_dynamic.bc

llc-3.9 -filetype=obj welcome_dynamic.bc -o=welcome_dynamic.o 

g++ welcome_dynamic.o -o welcome_dynamic

./welcome_dynamic > ../../output/welcome.dynamic.log

rm *.bc
rm welcome_dynamic.o welcome_dynamic
