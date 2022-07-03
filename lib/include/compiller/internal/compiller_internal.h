#ifndef COMPILLER_LIB_COMPILLER_INTERNAL_COMPILLER_INTERNAL_H_
#define COMPILLER_LIB_COMPILLER_INTERNAL_COMPILLER_INTERNAL_H_

namespace cplr {
namespace internal {

class InternalClass {
 public:
  InternalClass(int val);
  ~InternalClass() = default;

  int AnotherTestFunc();

 private:
  int val_;
};

}  // namespace internal
}  // namespace cplr

#endif  // COMPILLER_LIB_COMPILLER_INTERNAL_COMPILLER_INTERNAL_H_
