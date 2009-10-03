#ifndef SETTINGSTREE__BRANCH_CALLBACK_HPP
#define SETTINGSTREE__BRANCH_CALLBACK_HPP

#include <string>

namespace settingstree {

class branch;

class branch_callback {
  public:
    virtual void children_altered(branch& altered) = 0;
  protected:
    branch_callback() = default;
    branch_callback(branch_callback const&) = default;
    branch_callback& operator=(branch_callback const&) = default;
    virtual inline ~branch_callback() = 0;
};

inline branch_callback::~branch_callback() {}

}

#endif // SETTINGSTREE__BRANCH_CALLBACK_HPP

