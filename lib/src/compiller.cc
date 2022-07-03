#include "compiller/internal/compiller_internal.h"
#include "compiller/compiller.h"

namespace cplr {

TestBuild::TestBuild() {}

int TestBuild::TestFunc() {
  auto internal = std::make_unique<internal::InternalClass>(5);
  return internal->AnotherTestFunc();
}

}  // namespace cplr
