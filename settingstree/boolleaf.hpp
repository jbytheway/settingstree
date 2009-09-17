#ifndef SETTINGSTREE__BOOLLEAF_HPP
#define SETTINGSTREE__BOOLLEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingsTree {

class BoolLeaf : public Leaf {
  public:
    BoolLeaf(
        const String& name,
        const String& readers,
        const String& writers,
        Branch* parent,
        Server* server,
        bool value = false
      );
    virtual ~BoolLeaf() {}
  private:
    bool value;
  protected:
    virtual String setValue(const String& v);
    virtual std::set<String> getValue() const;
  public:
    inline bool getValueAsBool() const { return value; }
};

}

#endif // SETTINGSTREE__BOOLLEAF_HPP

