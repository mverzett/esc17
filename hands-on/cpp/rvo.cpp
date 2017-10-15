#include "tracking.hpp"
#include <random>

using RandomNumber = std::mt19937::result_type;

Tracking make_urvo(RandomNumber r)
{
  if (r % 2) {
    return Tracking{};
  }
  return Tracking{};
}

Tracking make_nrvo(RandomNumber r)
{
  Tracking result;
  if (r % 2) {
    result.k = 2;
  }
  return result;
}

Tracking make_no_rvo(RandomNumber r)
{
  Tracking result;
  if (r % 2) {
    return Tracking{};
  }
  return result;
}

Tracking make_move(RandomNumber r)
{
  Tracking result;
  if (r % 2) {
    result.k = 2;
  }
  return std::move(result);
}

int main()
{
  std::mt19937 eng{std::random_device{}()};

  auto r = eng();
  std::cout << "# Unnamed RVO\n";
  auto t1 = make_urvo(r);
  std::cout << "# Named RVO\n";
  auto t2 = make_nrvo(r);
  std::cout << "# No RVO\n";
  auto t3 = make_no_rvo(r);
  std::cout << "# Move\n";
  auto t4 = make_move(r);
  std::cout << "Exiting\n";
}
