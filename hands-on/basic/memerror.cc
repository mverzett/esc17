#include <iostream>

void f(int n, char const* arg)
{
  std::cout << "prog = " << arg << ", n = " << n << '\n';
}

int main(int, char* argv[])
{
  int x;
  f(x, argv[0]);
  int* p = new int;
  f(*p, argv[1]);
}
