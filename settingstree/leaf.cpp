#include <settingstree/leaf.hpp>

#include <sstream>

namespace settingstree {

leaf::leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent
  ) :
  node(name, readers, writers, parent)
{
}

leaf::~leaf()
{
}

node* leaf::getNodeByListRef(std::list<std::string>& nodeAddress)
{
  if (!nodeAddress.empty()) {
    std::ostringstream os;
    os << "sought child of leaf '" << getFullName() << "'";
    throw std::logic_error(os.str());
  }

  return this;
}

std::string leaf::changeRequestListRef(
    std::list<std::string>& nodeAddress,
    const std::string& value,
    const settings_user& user)
{
  //Debug("checking permissions for node " << getFullName());
  
  if (!user.hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }
  
  if (!user.hasWritePermissionFor(this)) {
    return std::string("cannot write to node '") + getFullName() +
      "': permission denied";
  }

  std::string reason = setValue(value);

  if (reason == "") {
    callback().settingAlteredCallback(this);
  }

  return reason;
}

boost::tuple<std::string, std::set<std::string>, node const*>
leaf::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const settings_user& user
  ) const
{
  if (!user.hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }

  return boost::make_tuple("", getValue(), this);
}

}

