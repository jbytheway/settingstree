#ifndef SETTINGSTREE__BOOLLEAF_HPP
#define SETTINGSTREE__BOOLLEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingstree {

class bool_leaf : public leaf {
  public:
    bool_leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        settings_callback*,
        bool value = false
      );
    virtual ~bool_leaf() {}
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

