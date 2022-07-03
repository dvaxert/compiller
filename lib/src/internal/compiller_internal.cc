#include "compiller/internal/compiller_internal.h"

namespace cplr {
namespace internal {

InternalClass::InternalClass(int val) : val_(val) {}

int InternalClass::AnotherTestFunc() { return val_; }

}  // namespace internal
}  // namespace cplr
