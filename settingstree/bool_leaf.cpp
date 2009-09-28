#include <settingstree/bool_leaf.hpp>

namespace settingstree {

bool_leaf::bool_leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    leaf_callback<bool>& callback,
    bool v
  ) :
  leaf(name, readers, writers, parent),
  value(v),
  callback_(callback)
{
}

std::string bool_leaf::setValue(const std::string& v)
{
  if (v == "true" || v == "1" || v == "on") {
    if (value) {
      return "setting already has that value";
    } else {
      std::string reason;
      if ("" !=
          (reason = callback_.settingAlteringCallback(this, true))) {
        return reason;
      }
      
      value = true;
      return "";
    }
  } else if (v == "false" || v == "0" || v == "off") {
    if (!value) {
      return "setting already has that value";
    } else {
      std::string reason;
      if ("" !=
          (reason = callback_.settingAlteringCallback(this, false))) {
        return reason;
      }
      
      value = false;
      return "";
    }
  }
  return "invalid value for boolean leaf";
}

std::set<std::string> bool_leaf::getValue() const
{
  std::set<std::string> result;
  if (value) {
    result.insert("true");
  } else {
    result.insert("false");
  }
  return result;
}

}
