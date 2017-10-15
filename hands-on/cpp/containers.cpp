#include <vector>
#include <list>
#include <chrono>
#include <iostream>
#include <random>
#include <cassert>
#include <cstdlib>

using Duration = std::chrono::duration<float>;

std::default_random_engine e{std::random_device{}()};
using Distribution = std::uniform_int_distribution<>;
Distribution d;

int N = 10000;

Duration fill(std::vector<int>& cont)
{
  auto start = std::chrono::high_resolution_clock::now();

  cont.clear();
  for (int i = 0; i != N; ++i) {
    auto n = d(e, Distribution::param_type{0, static_cast<int>(cont.size())});
    auto it = cont.begin();
    advance(it, n);
    cont.insert(it, n);
  }
  assert(cont.size() == N);

  return std::chrono::high_resolution_clock::now() - start;
}

Duration process(std::vector<int> const& cont)
{
  auto start = std::chrono::high_resolution_clock::now();

  // the volatile is to avoid complete removal by the optimizer
  auto volatile _ = std::accumulate(std::begin(cont), std::end(cont), 0, [](int a, int n) {
      return a ^ n;
    });

  return std::chrono::high_resolution_clock::now() - start;  
}

int main(int argc, char* argv[])
{
  if (argc > 1) {
    int const n = std::atoi(argv[1]);
    if (n > 0) {
      N = n;
    }
  }

  std::vector<int> v;
  std::cout << "vector fill: " << fill(v).count() << " s\n";
  std::cout << "vector process: " << process(v).count() << " s\n";
  std::list<int> l;
  // std::cout << "list fill: " << fill(l).count() << " s\n";
  // std::cout << "list process: " << process(l).count() << " s\n";
}
