#ifndef SETTINGSTREE__STRING_LEAF_HPP
#define SETTINGSTREE__STRING_LEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingstree {

class string_leaf : public leaf {
  public:
    string_leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        leaf_callback<std::string>&,
        const std::string& initialValue = ""
      );
    virtual ~string_leaf() { }
  protected:
    std::string value_;
    leaf_callback<std::string>& callback_;

    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> value_set() const;
    virtual leaf_callback<std::string>& callback() { return callback_; }
  public:
    inline const std::string& value() const { return value_; }
};

}

#endif // SETTINGSTREE__STRING_LEAF_HPP

