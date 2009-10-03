#ifndef SETTINGSTREE__LEAF_CALLBACK_HPP
#define SETTINGSTREE__LEAF_CALLBACK_HPP

#include <string>

#include <settingstree/tree_traits.hpp>

namespace settingstree {

class leaf;

namespace detail {

class generic_leaf_callback {
  public:
    virtual void setting_altered(leaf& altered) = 0;
  protected:
    generic_leaf_callback() = default;
    generic_leaf_callback(generic_leaf_callback const&) = default;
    generic_leaf_callback& operator=(generic_leaf_callback const&) = default;
    virtual inline ~generic_leaf_callback() = 0;
};

inline generic_leaf_callback::~generic_leaf_callback() {}

}

template<typename T>
class leaf_callback : public detail::generic_leaf_callback {
  public:
    virtual std::string setting_altering(
        typename tree_traits<T>::leaf_type& altering, T newValue
      ) = 0;
  protected:
    leaf_callback() = default;
    leaf_callback(leaf_callback const&) = default;
    leaf_callback& operator=(leaf_callback const&) = default;
    virtual ~leaf_callback() = 0;
};

template<typename T>
leaf_callback<T>::~leaf_callback() {}

}

#endif // SETTINGSTREE__LEAF_CALLBACK_HPP

