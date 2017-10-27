#include <memory>

using SomeType = std::unique_ptr<int>;

SomeType factory();
void do_something();//SomeType);

int main()
{
  auto t = factory();

  do_something();//t);
}

SomeType factory()
{
  return std::make_unique<int>();
}

void do_something()//SomeType)
{
  throw 1;
}
