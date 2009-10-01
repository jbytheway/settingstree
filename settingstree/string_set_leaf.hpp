#ifndef SETTINGSTREE__STRING_SET_LEAF_HPP
#define SETTINGSTREE__STRING_SET_LEAF_HPP

#include <set>

#include <settingstree/leaf.hpp>

namespace settingstree {

class string_set_leaf : public leaf {
  public:
    typedef std::unique_ptr<string_set_leaf> ptr;
    typedef std::unique_ptr<const string_set_leaf> const_ptr;
    
    string_set_leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        leaf_callback<std::set<std::string> >&,
        const std::set<std::string>& initialValue = std::set<std::string>()
      );
    virtual ~string_set_leaf() { }
  private:
    std::set<std::string> value_;
    leaf_callback<std::set<std::string> >& callback_;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
  public:
    virtual std::set<std::string> const value_set() const { return value_; }
};

}

#endif // SETTINGSTREE__STRING_SET_LEAF_HPP

