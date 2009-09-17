#ifndef SETTINGSTREE__STRINGSETLEAF_HPP
#define SETTINGSTREE__STRINGSETLEAF_HPP

#include <set>

#include <settingstree/leaf.hpp>

namespace settingsTree {

class StringSetLeaf : public Leaf {
  public:
    typedef boost::shared_ptr<StringSetLeaf> Ptr;
    typedef boost::shared_ptr<const StringSetLeaf> ConstPtr;
    
    StringSetLeaf(
        const String& name,
        const String& readers,
        const String& writers,
        Branch* parent,
        Server* server,
        const std::set<String>& initialValue = std::set<String>()
      );
    virtual ~StringSetLeaf() { }
  private:
    std::set<String> value;
  protected:
    virtual String setValue(const String& v);
    virtual std::set<String> getValue() const;
  public:
    inline const std::set<String>& getValueAsSet() const {
      return value;
    }
};

}

#endif // SETTINGSTREE__STRINGSETLEAF_HPP

