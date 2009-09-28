#ifndef SETTINGSTREE__INT_LEAF_HPP
#define SETTINGSTREE__INT_LEAF_HPP

#include <settingstree/leaf.hpp>

namespace settingstree {

/* This defines a leaf storing a value of type T, which is assumed to be an
 * integer type */
template <typename T>
class int_leaf : public leaf {
  BOOST_STATIC_ASSERT((boost::is_integral<T>::value));
  BOOST_STATIC_ASSERT((!boost::is_same<T, bool>::value));
  public:
    int_leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        leaf_callback<T>&,
        T value = 0
      );
    virtual ~int_leaf() {}
  private:
    T value;
    leaf_callback<T>& callback_;
  protected:
    virtual std::string setValue(const std::string& v);
    virtual std::set<std::string> getValue() const;
    virtual leaf_callback<T>& callback() { return callback_; }
  public:
    inline T getValueAsInt() const { return value; }
};

}

#endif // SETTINGSTREE__INT_LEAF_HPP

