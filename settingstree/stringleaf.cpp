#include <settingstree/stringleaf.hpp>

namespace settingsTree {

StringLeaf::StringLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    Server* server,
    const std::string& initialValue
  ) :
  Leaf(name, readers, writers, parent, server),
  value(initialValue)
{
}

std::string StringLeaf::setValue(const std::string& v)
{
  std::string reason;
  if ("" != (reason = server->settingAlteringCallback(this, v))) {
    return reason;
  }
  value = v;
  return "";
}

std::set<std::string> StringLeaf::getValue() const
{
  std::set<std::string> result;
  result.insert(value);
  return result;
}

}

