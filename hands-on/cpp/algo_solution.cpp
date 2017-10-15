#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include <cassert>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& c)
{
  os << "{ ";
  std::copy(
      std::begin(c),
      std::end(c),
      std::ostream_iterator<T>{os, " "}
  );
  os << '}';

  return os;
}

int main()
{
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::mt19937 eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> uniform_dist{1, MAX_N};

  // fill a vector with SIZE random numbers
  int const SIZE = 10;
  std::vector<int> v;
  v.reserve(SIZE);
  std::generate_n(
      std::back_inserter(v)
      , SIZE
      , [&]() { return uniform_dist(eng); }
  );

  std::cout << v << '\n';

  // alternative way to fill the vector (but less efficient, why?)
  // std::vector<int> v(SIZE);
  // std::generate_n(std::begin(v), SIZE, [&]() { return uniform_dist(e); });

  // sum all the elements of the vector
  std::cout << "sum = "
            << std::accumulate(std::begin(v), std::end(v), 0)
            << '\n';

  // multiply all the elements of the vector
  std::cout << "product = "
            << std::accumulate(std::begin(v), std::end(v), 1LL, std::multiplies<long long>())
            << '\n';

  // sort the vector in ascending order
  std::sort(std::begin(v), std::end(v));
  std::cout << "sorted: " << v << '\n';

  // sort the vector in descending order
  std::sort(std::begin(v), std::end(v), std::greater<int>());
  // or
  // std::sort(std::begin(v), std::end(v), [](int i, int j) { return j < i; });
  std::cout << "inverted sorted: " << v << '\n';

  // move the even numbers at the beginning of the vector
  auto first_odd = std::partition(std::begin(v), std::end(v), [](int i) { return !(i % 2);});
  std::cout << "partitioned: " << v << '\n';
  std::cout << "first odd number at position "
            << std::distance(std::begin(v), first_odd)
            << '\n';
  
  // move the three central elements to the beginning of the vector
  assert(v.size() >= 3);
  auto mid_it = std::begin(v) + v.size() / 2;
  auto n_first = std::prev(mid_it);
  auto last = std::next(mid_it, 2);
  std::rotate(std::begin(v), n_first, last);
  std::cout << "rotated: " << v << '\n';

  // find the first element that is multiple of 3 or 7
  auto found_it = std::find_if(
      std::begin(v),
      std::end(v),
      [](int i) { return !(i % 3) || !(i % 7);}
  );
  std::cout << "first multiple of 3 or 7 at position "
            << std::distance(std::begin(v), found_it)
            << '\n';

  // erase from the vector the multiples of 3 or 7
  // use std::remove_if followed by vector::erase
  v.erase(
      std::remove_if(
          std::begin(v)
          , std::end(v)
          , [](int i) { return (i % 3) == 0 || (i % 7) == 0;}
      ),
      std::end(v)
  );
  std::cout << "multiples of 3 or 7 erased: " << v << '\n';
};
