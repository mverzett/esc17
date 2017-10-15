---
title: Data layout
layout: main
category: cpp
---

The goal of this exercise is to appreciate the impact on performance
of the physical design of data structures, i.e. their layout in
memory.

Inspect, build and run the following programs:

* `sort_packed.cpp`
* `sort_cold.cpp`
* `aos.cpp`
* `aos_impr.cpp`
* `soa.cpp`

Vary the build parameter `EXTSIZE` and record the differences in
execution time. Check also the output of `perf`.

The commands to build and run the code are:

    [studentNM@esc-XY ~]$ cd esc16/hands-on/cpp
    [studentNM@esc-XY cpp]$ g++ -O3 -DEXTSIZE=8 -o sort_cold sort_cold.cpp
    [studentNM@esc-XY cpp]$ ./sort_cold
    [studentNM@esc-XY cpp]$ perf stat -d ./sort_cold
    
Similarly for the other programs.
