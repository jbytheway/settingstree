#ifndef SETTINGSTREE__STRINGLEAF_HPP
#define SETTINGSTREE__STRINGLEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingsTree {

class StringLeaf : public Leaf {
  public:
    StringLeaf(
        const String& name,
        const String& readers,
        const String& writers,
        Branch* parent,
        Server* server,
        const String& initialValue = ""
      );
    virtual ~StringLeaf() { }
  protected:
    String value;

    virtual String setValue(const String& v);
    virtual std::set<String> getValue() const;
};

}

#endif // SETTINGSTREE__STRINGLEAF_HPP

