#include <settingstree/boolleaf.hpp>

namespace settingsTree {

BoolLeaf::BoolLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    settings_callback* callback,
    bool v
  ) :
  Leaf(name, readers, writers, parent, callback),
  value(v)
{
}

std::string BoolLeaf::setValue(const std::string& v)
{
  if (v == "true" || v == "1" || v == "on") {
    if (value) {
      return "setting already has that value";
    } else {
      std::string reason;
      if ("" !=
          (reason = callback_->settingAlteringCallback<bool>(this, true))) {
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
          (reason = callback_->settingAlteringCallback<bool>(this, false))) {
        return reason;
      }
      
      value = false;
      return "";
    }
  }
  return "invalid value for boolean leaf";
}

std::set<std::string> BoolLeaf::getValue() const
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
