#include <compiller/compiller.h>

#include <iostream>

int main() {
  cplr::TestBuild tb{};

  std::cout << tb.TestFunc() << std::endl;

  return 0;
}
