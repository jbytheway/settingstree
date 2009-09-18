#include <settingstree/string_leaf.hpp>

namespace settingsTree {

StringLeaf::StringLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    settings_callback* callback,
    const std::string& initialValue
  ) :
  Leaf(name, readers, writers, parent, callback),
  value(initialValue)
{
}

std::string StringLeaf::setValue(const std::string& v)
{
  std::string reason;
  if ("" != (reason = callback_->settingAlteringCallback(this, v))) {
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

