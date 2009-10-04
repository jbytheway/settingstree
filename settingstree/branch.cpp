#include <settingstree/branch.hpp>

#include <sstream>

namespace settingstree {

branch::branch(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    branch* parent,
    branch_callback& callback
  ) :
  node(name, readers, writers, parent),
  callback_(callback)
{
}

node* branch::addChild(node::ptr child) {
  node* cp = child.get();
  children_[child->name()] = std::move(child);
  callback_.children_altered(*this);
  return cp;
}

void branch::removeChild(std::string name) {
  assert(children_.count(name));
  children_.erase(name);
  callback_.children_altered(*this);
}

node* branch::getNodeByListRef(
    std::list<std::string>& nodeAddress
  )
{
  if (nodeAddress.empty()) {
    return this;
  }

  node* ch = child(nodeAddress.front());
  
  if (!ch) {
    std::ostringstream os;
    os << "node '" << nodeAddress.front() << "' not found in '" <<
        full_name() << "'";
    throw std::logic_error(os.str());
  }

  nodeAddress.pop_front();
  
  return ch->getNodeByListRef(nodeAddress);
}

std::string branch::changeRequestListRef(
    std::list<std::string>& setting,
    const std::string& value,
    const user& user)
{
  if (!user.hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + full_name() +
      "': permission denied";
  }
  
  if (setting.empty()) {
    return "requested node '" + full_name() + "' not a leaf";
  }

  node* ch = child(setting.front());

  if (!ch) {
    return std::string("node '") + setting.front() + "' not found in '" +
      full_name() + "'";
  }

  setting.pop_front();
  
  return ch->changeRequestListRef(setting, value, user);
}

boost::tuple<std::string, std::set<std::string>, node const*>
branch::getRequestListRef(
    std::list<std::string>& nodeAddress,
    const user& user
  ) const
{
  if (!user.hasReadPermissionFor(this)) {
    return std::string("cannot read node '") + full_name() +
      "': permission denied";
  }
  
  if (nodeAddress.empty()) {
    return boost::make_tuple("", child_names(), this);
  }

  node const* ch = child(nodeAddress.front());

  if (!ch) {
    return boost::make_tuple(
        std::string("node '") + nodeAddress.front() + "' not found in '" +
        full_name() + "'", std::set<std::string>(), static_cast<node*>(NULL)
      );
  }

  nodeAddress.pop_front();
  
  return ch->getRequestListRef(nodeAddress, user);
}

std::set<std::string> branch::child_names() const
{
  std::set<std::string> childNames;
  for (boost::unordered_map<std::string, node::ptr>::const_iterator
      child = children_.begin(); child != children_.end(); child++) {
    childNames.insert(child->second->name());
  }
  return childNames;
}

node* branch::child(std::string name)
{
  boost::unordered_map<std::string, node::ptr>::iterator child =
    children_.find(name);

  if (child == children_.end()) {
    return NULL;
  }

  return child->second.get();
}

node const* branch::child(std::string name) const
{
  boost::unordered_map<std::string, node::ptr>::const_iterator child =
    children_.find(name);

  if (child == children_.end()) {
    return NULL;
  }

  return child->second.get();
}

}

