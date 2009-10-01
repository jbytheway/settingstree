#include <settingstree/string_leaf.hpp>

#include <boost/assign/list_of.hpp>

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
  value_(initialValue),
  callback_(callback)
{
}

std::string string_leaf::setValue(const std::string& v)
{
  std::string reason;
  if ("" != (reason = callback_.setting_altering(*this, v))) {
    return reason;
  }
  value_ = v;
  return "";
}

std::set<std::string> string_leaf::getValue() const
{
  return boost::assign::list_of(value_);
}

}

