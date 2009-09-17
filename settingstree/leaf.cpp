#include <settingstree/leaf.hpp>

#include <sstream>

namespace settingsTree {

Leaf::Leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    settings_callback* callback
  ) :
  Node(name, readers, writers, parent, callback)
{
}

Leaf::~Leaf()
{
}

Node* Leaf::getNodeByListRef(std::list<std::string>& nodeAddress)
{
  if (!nodeAddress.empty()) {
    std::ostringstream os;
    os << "sought child of leaf '" << getFullName() << "'";
    throw std::logic_error(os.str());
  }

  return this;
}

std::string Leaf::changeRequestListRef(
    std::list<std::string>& nodeAddress,
    const std::string& value,
    const SettingsUser* user)
{
  //Debug("checking permissions for node " << getFullName());
  
  if (!user->hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }
  
  if (!user->hasWritePermissionFor(this)) {
    return std::string("cannot write to node '") + getFullName() +
      "': permission denied";
  }

  std::string reason = setValue(value);

  if (reason == "") {
    callback_->settingAlteredCallback(this);
  }

  return reason;
}

boost::tuple<std::string, std::set<std::string>, Node const*>
Leaf::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const SettingsUser* user
  ) const
{
  if (!user->hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }

  return boost::make_tuple("", getValue(), this);
}

}

