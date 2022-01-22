
#include <iostream>

namespace internal {
template <typename T>
struct AlwaysFalse {
  static const bool value = false;
};
}  // namespace internal

template <typename T>
struct DependentFalse : std::false_type
{};

template <class P> struct ParamTraits {
  static_assert(internal::AlwaysFalse<P>::value,
                "Cannot find the IPC::ParamTraits specialization. Did you "
                "forget to include the corresponding header file?");
                
  static_assert(DependentFalse<P>::value,
                "Cannot find the IPC::ParamTraits specialization. Did you "
                "forget to include the corresponding header file?");
};

struct GURL {};

template <>
struct ParamTraits<GURL> {
  typedef GURL param_type;
  static void Write() { std::cout << "hi there" << std::endl; }
};

int main() {
    using TestType = ParamTraits<GURL>;
    TestType::Write();
    std::cout << "Hello Lucy Nguyen!\n";}
