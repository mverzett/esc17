---
title: std::vector vs std::list
layout: main
category: cpp
---

The goal of this exercise is to appreciate the importance of
manipulating data structures that are contiguous in memory.

Take `containers.cpp`. It implements for an `std::vector<int>` two
operations:

* `fill()`, which fills the container with `N` integers randomly
generated. Each integer is inserted in a random position.

* `process()`, which applies a reduction operation to the
previously-filled vector.

Inspect, build and run `containers.cpp`, also through `perf`, varying
the number of elements:

    [studentNM@esc-XY ~]$ cd esc17/hands-on/cpp
    [studentNM@esc-XY cpp]$ g++ -O3 -o containers containers.cpp
    [studentNM@esc-XY cpp]$ ./containers 100000
    vector fill: 0.526868 s
    vector process: 2.9868e-05 s
    [studentNM@esc-XY cpp]$ perf stat -d ./containers

Then extend the program to implemente `fill()` and `process()` for an
`std::list<int>`. Compare the performance obtained with the two
containers.

Run the program through the `igprof` memory profiler:

    [studentNM@esc-XY cpp]$ igprof -mp -z -o containers.gz ./containers 10000
    [studentNM@esc-XY cpp]$ igprof-analyze -d -g containers.gz ./containers 10000

and interpret the data.
