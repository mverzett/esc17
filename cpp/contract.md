---
title: Contract-based programming
layout: main
category: cpp
---

The goal of this exercise is to identify:

* the invariant of the String class

* the pre-condition and the post-condition of its member functions
(when applicable)

* other logical checkpoints both at compile time and run time

and how to express them with `static_assert`s, `assert`s and
exceptions, including `noexcept`

Hint: imagine to remove the default constructor of `String` and see what the
consequences are.
