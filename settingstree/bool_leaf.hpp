#ifndef SETTINGSTREE__BOOL_LEAF_HPP
#define SETTINGSTREE__BOOL_LEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingstree {

class bool_leaf : public leaf {
  public:
    bool_leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        leaf_callback<bool>&,
        bool value = false
      );
    virtual ~bool_leaf() {}
  private:
    bool value_;
    leaf_callback<bool>& callback_;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> value_set() const;
    virtual leaf_callback<bool>& callback() { return callback_; }
  public:
    inline bool value() const { return value_; }
};

}

#endif // SETTINGSTREE__BOOL_LEAF_HPP

