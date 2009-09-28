#ifndef SETTINGSTREE__STRINGSETLEAF_HPP
#define SETTINGSTREE__STRINGSETLEAF_HPP

#include <set>

#include <settingstree/leaf.hpp>

namespace settingstree {

class string_set_leaf : public leaf {
  public:
    typedef boost::shared_ptr<string_set_leaf> Ptr;
    typedef boost::shared_ptr<const string_set_leaf> ConstPtr;
    
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
    std::set<std::string> value;
    leaf_callback<std::set<std::string> >& callback_;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
  public:
    inline const std::set<std::string>& getValueAsSet() const {
      return value;
    }
};

}

#endif // SETTINGSTREE__STRINGSETLEAF_HPP

