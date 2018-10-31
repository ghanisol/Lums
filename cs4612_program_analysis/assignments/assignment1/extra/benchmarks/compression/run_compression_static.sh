clang-3.9 -c -emit-llvm compression.c -o compression.bc

opt-3.9 -load ../../../llvm_passes/StaticInstructionsCount/build/static_instruction_count/libStaticInstructionsCount.so -icount -analyze compression.bc -o /dev/null > ../../output/compression.static.log

rm compression.bc