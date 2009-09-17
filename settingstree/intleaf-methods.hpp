#ifndef SETTINGSTREE__INTLEAF_METHODS_HPP
#define SETTINGSTREE__INTLEAF_METHODS_HPP

#include "intleaf.h"

#include "server-methods.h"

namespace settingsTree {

template<typename T>
IntLeaf<T>::IntLeaf(
    const String& name,
    const String& readers,
    const String& writers,
    Branch* parent,
    Server* server,
    T v
  ) :
  Leaf(name, readers, writers, parent, server),
  value(v)
{
}  

template<typename T>
String IntLeaf<T>::setValue(const String& s)
{
  T v = sakusen::numFromString<T>(s);
  if (v == value) {
    return "setting already has that value";
  }
  String reason;
  if ("" != (reason = server->settingAlteringCallback<T>(this, v))) {
    return reason;
  }

  value = v;
  return "";
}

template<typename T>
std::set<String> IntLeaf<T>::getValue() const
{
  std::set<String> result;
  result.insert(sakusen::numToString(value));
  return result;
}

}

#endif // SETTINGSTREE__INTLEAF_METHODS_HPP

