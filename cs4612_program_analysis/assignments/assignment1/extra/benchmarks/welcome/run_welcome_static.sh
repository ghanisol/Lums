clang-3.9 -c -emit-llvm welcome.cpp -o welcome.bc

opt-3.9 -load ../../../llvm_passes/StaticInstructionsCount/build/static_instruction_count/libStaticInstructionsCount.so -icount -analyze welcome.bc -o /dev/null > ../../output/welcome.static.log

rm welcome.bc
