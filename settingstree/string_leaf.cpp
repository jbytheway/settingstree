#include <settingstree/string_leaf.hpp>

namespace settingstree {

string_leaf::string_leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    leaf_callback<std::string>& callback,
    const std::string& initialValue
  ) :
  leaf(name, readers, writers, parent),
  value(initialValue),
  callback_(callback)
{
}

std::string string_leaf::setValue(const std::string& v)
{
  std::string reason;
  if ("" != (reason = callback_.setting_altering(*this, v))) {
    return reason;
  }
  value = v;
  return "";
}

std::set<std::string> string_leaf::getValue() const
{
  std::set<std::string> result;
  result.insert(value);
  return result;
}

}

