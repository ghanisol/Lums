clang-3.9 -c -emit-llvm gcd.cpp -o gcd.bc

opt-3.9 -load ../../../llvm_passes/StaticInstructionsCount/build/static_instruction_count/libStaticInstructionsCount.so -icount -analyze gcd.bc -o /dev/null > ../../output/gcd.static.log

rm gcd.bc
