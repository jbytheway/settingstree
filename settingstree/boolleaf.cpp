#include <settingstree/boolleaf.hpp>

using namespace fuseki;
using namespace fuseki::settingsTree;

BoolLeaf::BoolLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    Server* server,
    bool v
  ) :
  Leaf(name, readers, writers, parent, server),
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
      if ("" != (reason = server->settingAlteringCallback<bool>(this, true))) {
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
      if ("" != (reason = server->settingAlteringCallback<bool>(this, false))) {
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

