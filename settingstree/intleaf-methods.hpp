#ifndef SETTINGSTREE__INTLEAF_METHODS_HPP
#define SETTINGSTREE__INTLEAF_METHODS_HPP

#include <settingstree/intleaf.hpp>

namespace settingstree {

template<typename T>
int_leaf<T>::int_leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    settings_callback*,
    T v
  ) :
  leaf(name, readers, writers, parent, server),
  value(v)
{
}  

template<typename T>
std::string int_leaf<T>::setValue(const std::string& s)
{
  T v = sakusen::numFromString<T>(s);
  if (v == value) {
    return "setting already has that value";
  }
  std::string reason;
  if ("" != (reason = server->settingAlteringCallback<T>(this, v))) {
    return reason;
  }

  value = v;
  return "";
}

template<typename T>
std::set<std::string> int_leaf<T>::getValue() const
{
  std::set<std::string> result;
  result.insert(sakusen::numToString(value));
  return result;
}

}

#endif // SETTINGSTREE__INTLEAF_METHODS_HPP

