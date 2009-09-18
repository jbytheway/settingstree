#include <settingstree/branch.hpp>

#include <sstream>

namespace settingstree {

branch::branch(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    settings_callback* callback
  ) :
  node(name, readers, writers, parent, callback)
{
}

node::Ptr branch::addChild(node::Ptr child) {
  children[child->getName()] = child;
  callback_->settingAlteredCallback(this);
  return child;
}

void branch::removeChild(std::string name) {
  assert(children.count(name));
  children.erase(name);
  callback_->settingAlteredCallback(this);
}

node* branch::getNodeByListRef(
    std::list<std::string>& nodeAddress
  )
{
  if (nodeAddress.empty()) {
    return this;
  }

  node::Ptr child = getChild(nodeAddress.front());
  
  if (!child) {
    std::ostringstream os;
    os << "node '" << nodeAddress.front() << "' not found in '" <<
        getFullName() << "'";
    throw std::logic_error(os.str());
  }

  nodeAddress.pop_front();
  
  return child->getNodeByListRef(nodeAddress);
}

std::string branch::changeRequestListRef(
    std::list<std::string>& setting,
    const std::string& value,
    const settings_user* user)
{
  if (!user->hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (setting.empty()) {
    return "requested node '" + getFullName() + "' not a leaf";
  }

  node::Ptr child = getChild(setting.front());

  if (child == NULL) {
    return std::string("node '") + setting.front() + "' not found in '" +
      getFullName() + "'";
  }

  setting.pop_front();
  
  return child->changeRequestListRef(setting, value, user);
}

boost::tuple<std::string, std::set<std::string>, node const*>
branch::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const settings_user* user
  ) const
{
  if (!user->hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + getFullName() +
      "': permission denied";
  }
  
  if (nodeAddress.empty()) {
    return boost::make_tuple("", getChildNames(), this);
  }

  node::ConstPtr child = getChild(nodeAddress.front());

  if (!child) {
    return boost::make_tuple(
        std::string("node '") + nodeAddress.front() + "' not found in '" +
        getFullName() + "'", std::set<std::string>(), static_cast<node*>(NULL)
      );
  }

  nodeAddress.pop_front();
  
  return child->getRequestListRef(nodeAddress, user);
}

std::set<std::string> branch::getChildNames() const
{
  std::set<std::string> childNames;
  for (boost::unordered_map<std::string, node::Ptr>::const_iterator
      child = children.begin(); child != children.end(); child++) {
    childNames.insert(child->second->getName());
  }
  return childNames;
}

node::Ptr branch::getChild(std::string name)
{
  boost::unordered_map<std::string, node::Ptr>::iterator child =
    children.find(name);

  if (child == children.end()) {
    return node::Ptr();
  }

  return child->second;
}

node::ConstPtr branch::getChild(std::string name) const
{
  boost::unordered_map<std::string, node::Ptr>::const_iterator child =
    children.find(name);

  if (child == children.end()) {
    return node::ConstPtr();
  }

  return child->second;
}

}

