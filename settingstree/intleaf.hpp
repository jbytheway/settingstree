#ifndef SETTINGSTREE__INTLEAF_HPP
#define SETTINGSTREE__INTLEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingstree {

/* This defines a leaf storing a value of type T, which is assumed to be an
 * integer type */
template <typename T>
class IntLeaf : public Leaf {
  SAKUSEN_STATIC_ASSERT((boost::is_integral<T>::value));
  SAKUSEN_STATIC_ASSERT((!boost::is_same<T, bool>::value));
  public:
    IntLeaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        settings_callback*,
        T value = 0
      );
    virtual ~IntLeaf() {}
  private:
    T value;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
  public:
    inline T getValueAsInt() const { return value; }
};

}

#endif // SETTINGSTREE__INTLEAF_HPP

