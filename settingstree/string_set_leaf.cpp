#include <settingstree/string_set_leaf.hpp>

namespace settingstree {

string_set_leaf::string_set_leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    leaf_callback<std::set<std::string> >& callback,
    const std::set<std::string>& initialValue
  ) :
  leaf(name, readers, writers, parent),
  value_(initialValue),
  callback_(callback)
{
}

std::string string_set_leaf::setValue(const std::string& v)
{
  if (v.empty()) {
    return "When setting the value of a list leaf, the first character must "
        "be '0', '+' or '-'";
  }
  
  std::set<std::string> newValue = value_;
  
  switch (v[0]) {
    case '0':
      if (v.length() > 1) {
        return "When clearing a list node, the value specified must be "
          "exactly '0'";
      }
      newValue.clear();
      break;
    case '+':
      {
        std::string adding = v.substr(1);
        if (newValue.count(adding)) {
          return "String to be added already in list";
        }
        newValue.insert(adding);
      }
      break;
    case '-':
      {
        std::string erasing = v.substr(1);
        if (0 == newValue.count(erasing)) {
          return "String to be removed not in list";
        }
        newValue.erase(erasing);
      }
      break;
    default:
      return "When setting the value of a list leaf, the first character must "
        "be '0', '+' or '-'";
  }

  std::string reason;
  if ("" != 
      (reason = callback_.setting_altering(*this, newValue))
    ) {
    return reason;
  }
  value_ = newValue;
  return "";
}

std::set<std::string> string_set_leaf::value_set() const
{
  return value_;
}

}

