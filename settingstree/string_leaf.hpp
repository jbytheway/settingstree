#ifndef SETTINGSTREE__STRINGLEAF_HPP
#define SETTINGSTREE__STRINGLEAF_HPP

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
    std::string value;
    leaf_callback<std::string>& callback_;

    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
    virtual leaf_callback<std::string>& callback() { return callback_; }
};

}

#endif // SETTINGSTREE__STRINGLEAF_HPP

