#ifndef SETTINGSTREE__INTLEAF_METHODS_HPP
#define SETTINGSTREE__INTLEAF_METHODS_HPP

#include <settingstree/intleaf.hpp>

namespace settingsTree {

template<typename T>
IntLeaf<T>::IntLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    settings_callback*,
    T v
  ) :
  Leaf(name, readers, writers, parent, server),
  value(v)
{
}  

template<typename T>
std::string IntLeaf<T>::setValue(const std::string& s)
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
std::set<std::string> IntLeaf<T>::getValue() const
{
  std::set<std::string> result;
  result.insert(sakusen::numToString(value));
  return result;
}

}

#endif // SETTINGSTREE__INTLEAF_METHODS_HPP

