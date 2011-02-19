#ifndef SETTINGSTREE__BRANCH_CALLBACK_HPP
#define SETTINGSTREE__BRANCH_CALLBACK_HPP

#include <string>

namespace settingstree {

class branch;

class branch_callback {
  public:
    virtual void children_altered(branch& altered) = 0;
  protected:
    branch_callback() {}
    branch_callback(branch_callback const&);
    branch_callback& operator=(branch_callback const&);
    virtual inline ~branch_callback() = 0;
};

inline branch_callback::branch_callback(branch_callback const&) = default;
inline branch_callback&
branch_callback::operator=(branch_callback const&) = default;
inline branch_callback::~branch_callback() = default;

}

#endif // SETTINGSTREE__BRANCH_CALLBACK_HPP

