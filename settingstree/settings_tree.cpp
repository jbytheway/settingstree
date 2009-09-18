#include <settingstree/settings_tree.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>

#include <settingstree/delimiter.hpp>

namespace settingstree {

SettingsTree::SettingsTree(settings_callback* callback) :
  Branch("", "world", "", NULL, callback)
{
}

std::list<std::string> SettingsTree::stringNodeAddressToList(
    const std::string& nodeAddress
  ) const
{
  std::list<std::string> addressAsList;
  boost::algorithm::split(
      addressAsList, nodeAddress,
      boost::phoenix::arg_names::arg1 == SETTINGSTREE_DELIMITER
    );
  /* Remove effect of leading, trailing or duplicate delimiters */
  std::list<std::string>::iterator name = addressAsList.begin();
  while (name != addressAsList.end()) {
    if (name->empty()) {
      name = addressAsList.erase(name);
    } else {
      name++;
    }
  }
  return addressAsList;
}

Node* SettingsTree::getNode(const std::string& nodeAddress)
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

}

