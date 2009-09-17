#include <settingstree/leaf.hpp>

namespace settingsTree {

Leaf::Leaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    Server* server
  ) :
  Node(name, readers, writers, parent, server)
{
}

Leaf::~Leaf()
{
}

Node::Ptr Leaf::getNodeByListRef(list<std::string>& nodeAddress)
{
  if (!nodeAddress.empty()) {
    Fatal("sought child of leaf '" << getFullName() << "'");
  }

  return ptrToThis();
}

std::string Leaf::changeRequestListRef(
    list<std::string>& nodeAddress,
    const std::string& value,
    const SettingsUser* user)
{
  //Debug("checking permissions for node " << getFullName());
  
  if (!user->hasReadPermissionFor(ptrToThis())) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }
  
  if (!user->hasWritePermissionFor(ptrToThis())) {
    return std::string("cannot write to node '") + getFullName() +
      "': permission denied";
  }

  std::string reason = setValue(value);

  if (reason == "") {
    server->settingAlteredCallback(ptrToThis());
  }

  return reason;
}

boost::tuple<std::string, std::set<std::string>, Node::ConstPtr>
Leaf::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const SettingsUser* user
  ) const
{
  if (!user->hasReadPermissionFor(ptrToThis())) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (!nodeAddress.empty()) {
    return std::string("node '") + getFullName() + "' is a leaf and has no child";
  }

  return boost::make_tuple("", getValue(), ptrToThis());
}

}

