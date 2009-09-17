#include <settingstree/branch.hpp>

namespace settingsTree {

Branch::Branch(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    Server* server
  ) :
  Node(name, readers, writers, parent, server)
{
}

Node::Ptr Branch::addChild(Node::Ptr child) {
  children[child->getName()] = child;
  /* Can't use ptrToThis() because might still be constructing Server */
  server->settingAlteredCallback(Node::Ptr(this, null_deleter()));
  return child;
}

void Branch::removeChild(std::string name) {
  assert(children.count(name));
  children.erase(name);
  server->settingAlteredCallback(ptrToThis());
}

Node::Ptr Branch::getNodeByListRef(
    list<std::string>& nodeAddress
  )
{
  if (nodeAddress.empty()) {
    return ptrToThis();
  }

  Node::Ptr child = getChild(nodeAddress.front());
  
  if (!child) {
    Fatal("node '" << nodeAddress.front() << "' not found in '" <<
        getFullName() << "'");
  }

  nodeAddress.pop_front();
  
  return child->getNodeByListRef(nodeAddress);
}

std::string Branch::changeRequestListRef(
    list<std::string>& setting,
    const std::string& value,
    const SettingsUser* user)
{
  if (!user->hasReadPermissionFor(ptrToThis())) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (setting.empty()) {
    return "requested node '" + getFullName() + "' not a leaf";
  }

  Node::Ptr child = getChild(setting.front());

  if (child == NULL) {
    return std::string("node '") + setting.front() + "' not found in '" +
      getFullName() + "'";
  }

  setting.pop_front();
  
  return child->changeRequestListRef(setting, value, user);
}

boost::tuple<std::string, std::set<std::string>, Node::ConstPtr>
Branch::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const SettingsUser* user
  ) const
{
  if (!user->hasReadPermissionFor(ptrToThis())) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (nodeAddress.empty()) {
    return boost::make_tuple("", getChildNames(), ptrToThis());
  }

  Node::ConstPtr child = getChild(nodeAddress.front());

  if (!child) {
    return boost::make_tuple(
        std::string("node '") + nodeAddress.front() + "' not found in '" +
        getFullName() + "'", set<std::string>(), Ptr()
      );
  }

  nodeAddress.pop_front();
  
  return child->getRequestListRef(nodeAddress, user);
}

set<std::string> Branch::getChildNames() const
{
  set<std::string> childNames;
  for (u_map<std::string, Node::Ptr>::type::const_iterator
      child = children.begin(); child != children.end(); child++) {
    childNames.insert(child->second->getName());
  }
  return childNames;
}

Node::Ptr Branch::getChild(std::string name)
{
  u_map<std::string, Node::Ptr>::type::iterator child =
    children.find(name);

  if (child == children.end()) {
    return Node::Ptr();
  }

  return child->second;
}

Node::ConstPtr Branch::getChild(std::string name) const
{
  u_map<std::string, Node::Ptr>::type::const_iterator child =
    children.find(name);

  if (child == children.end()) {
    return Node::ConstPtr();
  }

  return child->second;
}

}

