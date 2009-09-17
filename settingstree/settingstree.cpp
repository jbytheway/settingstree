#include <settingstree/settingstree.hpp>

using namespace std;

using namespace sakusen;
using namespace fuseki;
using namespace fuseki::settingsTree;

SettingsTree::SettingsTree(Server* server) :
  Branch("", "world", "", NULL, server)
{
  addChild(Node::Ptr(new ServerBranch(this, server)));
  addChild(Node::Ptr(new GameBranch(this, server)));
  addChild(Node::Ptr(new ClientsBranch(this, server)));
  addChild(Node::Ptr(new PlayersBranch(this, server)));
  addChild(Node::Ptr(new PluginsBranch(this, server)));
}

list<std::string> SettingsTree::stringNodeAddressToList(
    const std::string& nodeAddress
  ) const
{
  list<std::string> addressAsList =
    stringUtils_split<list<std::string> >(nodeAddress, SETTINGS_DELIMITER);
  /* Remove effect of leading, trailing or duplicate delimiters */
  list<std::string>::iterator name = addressAsList.begin();
  while (name != addressAsList.end()) {
    if (name->empty()) {
      name = addressAsList.erase(name);
    } else {
      name++;
    }
  }
  return addressAsList;
}

Node::Ptr SettingsTree::getNode(const std::string& nodeAddress)
{
  return getNodeByList(stringNodeAddressToList(nodeAddress));
}

std::string SettingsTree::changeRequest(
    const std::string& nodeAddress,
    const std::string& value,
    const SettingsUser* user)
{
  return changeRequestList(
      stringNodeAddressToList(nodeAddress), value, user
    );
}

boost::tuple<std::string, std::set<std::string>, Node::ConstPtr>
SettingsTree::getRequest(
    const std::string& nodeAddress,
    const SettingsUser* user
  ) const
{
  return getRequestList(stringNodeAddressToList(nodeAddress), user);
}

