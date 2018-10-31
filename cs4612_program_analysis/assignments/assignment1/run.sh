## Part 1
# Static Instruction Count
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/welcome/ && bash ./run_welcome_static.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/hadamard/ && bash run_hadamard_static.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/gcd/ && bash run_gcd_static.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/compression/ && bash run_compression_static.sh

## Part 2
# Dynamic Instruction Count
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/welcome/ && bash ./run_welcome_dynamic.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/hadamard/ && bash run_hadamard_dynamic.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/gcd/ && bash run_gcd_dynamic.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/compression/ && bash run_compression_dynamic.sh

## Part 3
# Profile Branch Bias
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/welcome/ && bash ./run_welcome_branchbias.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/hadamard/ && bash run_hadamard_branchbias.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/gcd/ && bash run_gcd_branchbias.sh
cd ~/Documents/Courses/Assignment_1/extra/benchmarks/compression/ && bash run_compression_branchbias.sh