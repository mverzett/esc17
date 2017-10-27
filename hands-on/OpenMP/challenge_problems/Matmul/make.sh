#! /bin/bash
gcc -std=c99  -fopenmp mm_utils.c -c mm_utils.c
gcc -std=c99  -fopenmp -c mm_tst_cases.c
gcc -std=c99 -g -Ofast -march=native -fopt-info -fopenmp -c mm_ijk.c
gcc -std=c99  -fopenmp mm_testbed.c -o test mm_utils.o mm_tst_cases.o mm_ijk.o 
echo 'starting calculation'
./test > test.log
echo 'done'
