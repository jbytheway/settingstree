#include <settingstree/branch.hpp>

#include <sstream>

namespace settingsTree {

Branch::Branch(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    settings_callback* callback
  ) :
  Node(name, readers, writers, parent, callback)
{
}

Node::Ptr Branch::addChild(Node::Ptr child) {
  children[child->getName()] = child;
  callback_->settingAlteredCallback(this);
  return child;
}

void Branch::removeChild(std::string name) {
  assert(children.count(name));
  children.erase(name);
  callback_->settingAlteredCallback(this);
}

Node* Branch::getNodeByListRef(
    std::list<std::string>& nodeAddress
  )
{
  if (nodeAddress.empty()) {
    return this;
  }

  Node::Ptr child = getChild(nodeAddress.front());
  
  if (!child) {
    std::ostringstream os;
    os << "node '" << nodeAddress.front() << "' not found in '" <<
        getFullName() << "'";
    throw std::logic_error(os.str());
  }

  nodeAddress.pop_front();
  
  return child->getNodeByListRef(nodeAddress);
}

std::string Branch::changeRequestListRef(
    std::list<std::string>& setting,
    const std::string& value,
    const SettingsUser* user)
{
  if (!user->hasReadPermissionFor(this)) {
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

boost::tuple<std::string, std::set<std::string>, Node const*>
Branch::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const SettingsUser* user
  ) const
{
  if (!user->hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (nodeAddress.empty()) {
    return boost::make_tuple("", getChildNames(), this);
  }

  Node::ConstPtr child = getChild(nodeAddress.front());

  if (!child) {
    return boost::make_tuple(
        std::string("node '") + nodeAddress.front() + "' not found in '" +
        getFullName() + "'", std::set<std::string>(), static_cast<Node*>(NULL)
      );
  }

  nodeAddress.pop_front();
  
  return child->getRequestListRef(nodeAddress, user);
}

std::set<std::string> Branch::getChildNames() const
{
  std::set<std::string> childNames;
  for (boost::unordered_map<std::string, Node::Ptr>::const_iterator
      child = children.begin(); child != children.end(); child++) {
    childNames.insert(child->second->getName());
  }
  return childNames;
}

Node::Ptr Branch::getChild(std::string name)
{
  boost::unordered_map<std::string, Node::Ptr>::iterator child =
    children.find(name);

  if (child == children.end()) {
    return Node::Ptr();
  }

  return child->second;
}

Node::ConstPtr Branch::getChild(std::string name) const
{
  boost::unordered_map<std::string, Node::Ptr>::const_iterator child =
    children.find(name);

  if (child == children.end()) {
    return Node::ConstPtr();
  }

  return child->second;
}

}

