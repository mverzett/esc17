---
title: How to compile
category: basic
layout: main
---

The goal of this exercise is to understand how to compile and run test
programs on esc-XY. The default C++ compiler is 64-bit g++ v. 6.2.0,
which by defaults compiles in C++14 mode.

Build [cputicks.cc]({{site.exercises_repo}}/hands-on/basic/cputicks.cc):

    [studentNM@esc-XY ~]$ cd esc17/hands-on/basic
    [studentNM@esc-XY basic]$ g++ -Wall -Wextra -o cputicks cputicks.cc
    [studentNM@esc-XY basic]$ ./cputicks 1000
    pi = 3.14159 for 1000 iterations in 2.7878e-05 s

Run the code multiple times with different arguments.

Compile the code with different optimization levels (-O0 to -O3 and
-Ofast) and see if the execution time changes.

Look at the code and see how `std::chrono` is used to do some basic
time measurements, thanks to its `high_resolution_clock`.
