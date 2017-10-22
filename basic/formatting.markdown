---
title: clang-format
category: basic
layout: main
---

The goal of this exercise is to learn how to use `clang-format` to format your
code automatically and uniformly.

Consider [hello.cc]({{site.exercises_repo}}/hands-on/basic/hello.cc):

    [studentNM@esc-XY ~]$ cd esc17/hands-on/basic
    [studentNM@esc-XY basic]$ cat hello.cc
    #include <iostream>
    int main(int argc, char*argv[]){std::cout<<"Hello, ";...
    [studentNM@esc-XY basic]$ clang-format hello.cc
    #include <iostream>
    int main(int argc, char *argv[]) {
      std::cout << "Hello, ";
      if (argc > 1)
        std::cout << argv[1];
    ...

Note how the `*` in `char *argv` is attached to the argument. Instead we want it
attached to the type as in `char* argv`.

    [studentNM@esc-XY basic]$ clang-format -style="{PointerAlignment: Left}" hello.cc
    #include <iostream>
    int main(int argc, char* argv[]) {
      std::cout << "Hello, ";
      if (argc > 1)
        std::cout << argv[1];
    ...

Much better. We can save our settings in a configuration file, starting from a
dump of the default settings.

    [studentNM@esc-XY basic]$ clang-format -dump-config -style="{PointerAlignment: Left}" > .clang-format
    [studentNM@esc-XY basic]$ clang-format hello.cc
    #include <iostream>
    int main(int argc, char* argv[]) {
      std::cout << "Hello, ";
      if (argc > 1)
        std::cout << argv[1];
    ...


If we use the same `.clang-format` for all our projects, it can also be saved in
${HOME}.

To format a file _in place_ use the `-i` option.

    [studentNM@esc-XY basic]$ clang-format -i hello.cc
    [studentNM@esc-XY basic]$ cat hello.cc
    #include <iostream>
    int main(int argc, char* argv[]) {
      std::cout << "Hello, ";
      if (argc > 1)
        std::cout << argv[1];
    ...
