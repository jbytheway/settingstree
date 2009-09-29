#include <iostream>
#include <memory>

#include <settingstree/tree.hpp>
#include <settingstree/make.hpp>

namespace st = settingstree;

class test_callback :
  public st::leaf_callback<bool>,
  public st::leaf_callback<int>,
  public st::leaf_callback<std::string>
{
  virtual std::string settingAlteringCallback(st::leaf*, bool) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual std::string settingAlteringCallback(st::leaf*, int) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual std::string settingAlteringCallback(st::leaf*, std::string) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual void settingAlteredCallback(st::leaf*) {
    std::cout << "altered" << std::endl;
  }
};

class test_branch_callback : public st::branch_callback {
  virtual void childrenAlteredCallback(st::branch*) {
    std::cout << "children altered" << std::endl;
  }
};

int main()
{
  test_callback c;
  test_branch_callback bc;

  st::tree::ptr tree =
    st::make("", bc,
      st::make("var_bool", static_cast<st::leaf_callback<bool>&>(c), true),
      st::make("subtree", bc,
        st::make("var_int", static_cast<st::leaf_callback<int>&>(c), 0),
        st::make("var_string", c, "flibble")
      )
    ).tree_ptr();
  return 0;
}

