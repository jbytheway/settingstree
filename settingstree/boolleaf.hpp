#ifndef SETTINGSTREE__BOOLLEAF_HPP
#define SETTINGSTREE__BOOLLEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingsTree {

class BoolLeaf : public Leaf {
  public:
    BoolLeaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        settings_callback*,
        bool value = false
      );
    virtual ~BoolLeaf() {}
  private:
    bool value;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
  public:
    inline bool getValueAsBool() const { return value; }
};

}

#endif // SETTINGSTREE__BOOLLEAF_HPP

