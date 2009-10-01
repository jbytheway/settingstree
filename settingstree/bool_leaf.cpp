#include <settingstree/bool_leaf.hpp>

#include <boost/assign/list_of.hpp>

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
  value_(v),
  callback_(callback)
{
}

std::string bool_leaf::setValue(const std::string& v)
{
  if (v == "true" || v == "1" || v == "on") {
    if (value_) {
      return "setting already has that value";
    } else {
      std::string reason;
      if ("" !=
          (reason = callback_.setting_altering(*this, true))) {
        return reason;
      }
      
      value_ = true;
      return "";
    }
  } else if (v == "false" || v == "0" || v == "off") {
    if (!value_) {
      return "setting already has that value";
    } else {
      std::string reason;
      if ("" !=
          (reason = callback_.setting_altering(*this, false))) {
        return reason;
      }
      
      value_ = false;
      return "";
    }
  }
  return "invalid value for boolean leaf";
}

std::set<std::string> bool_leaf::value_set() const
{
  return boost::assign::list_of(value_ ? "true" : "false");
}

}
