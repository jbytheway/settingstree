#ifndef SETTINGSTREE__INT_LEAF_METHODS_HPP
#define SETTINGSTREE__INT_LEAF_METHODS_HPP

#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>

#include <settingstree/int_leaf.hpp>

namespace settingstree {

template<typename T>
int_leaf<T>::int_leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    leaf_callback<T>& callback,
    T v
  ) :
  leaf(name, readers, writers, parent),
  value_(v),
  callback_(callback)
{
}  

template<typename T>
std::string int_leaf<T>::setValue(const std::string& s)
{
  T v = boost::lexical_cast<T>(s);
  if (v == value_) {
    return "setting already has that value";
  }
  std::string reason;
  if ("" != (reason = callback_.setting_altering(*this, v))) {
    return reason;
  }

  value_ = v;
  return "";
}

template<typename T>
std::set<std::string> int_leaf<T>::value_set() const
{
  return boost::assign::list_of(boost::lexical_cast<std::string>(value_));
}

}

#endif // SETTINGSTREE__INT_LEAF_METHODS_HPP

