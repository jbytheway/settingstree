#ifndef SETTINGSTREE__STRINGSETLEAF_HPP
#define SETTINGSTREE__STRINGSETLEAF_HPP

#include <set>

#include <settingstree/leaf.hpp>

namespace settingstree {

class StringSetLeaf : public Leaf {
  public:
    typedef boost::shared_ptr<StringSetLeaf> Ptr;
    typedef boost::shared_ptr<const StringSetLeaf> ConstPtr;
    
    StringSetLeaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        settings_callback*,
        const std::set<std::string>& initialValue = std::set<std::string>()
      );
    virtual ~StringSetLeaf() { }
  private:
    std::set<std::string> value;
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

