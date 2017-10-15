#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <iterator>
#include <memory>
#include <cassert>

using namespace std;

default_random_engine e { std::random_device{}() };
uniform_real_distribution<> d;

struct Vec
{
  double x, y;
  Vec& operator+=(Vec const& o) {
    x += o.x;
    y += o.y;
    return *this;
  }
};

#ifndef EXTSIZE
#define EXTSIZE 0
#endif

constexpr int const ExtSize = EXTSIZE;

using Ext = std::array<char, ExtSize>;

struct Particles
{
  vector<Vec> positions;
  vector<Ext> exts;
};

void translate(Particles& particles, Vec const& t)
{
  auto& positions = particles.positions; 
  for_each(positions.begin(), positions.end(), [=](Vec& p) {
      p += t;
    });
}

chrono::duration<double> test(Particles& particles)
{
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i != 1000; ++i) {
    Vec t { d(e), d(e) };
    translate(particles, t);
  }

  return chrono::high_resolution_clock::now() - start;
}

int main()
{
  int const N = 1000000;

  Particles particles;

  auto& positions = particles.positions;
  positions.reserve(N);
  generate_n(back_inserter(positions), N, []() -> Vec { return {d(e), d(e)}; });

  auto& exts = particles.exts;
  exts.reserve(N);
  generate_n(back_inserter(exts), N, []() { return Ext{}; });

  assert(positions.size() == exts.size());

  cout << test(particles).count() << " s\n";
}
