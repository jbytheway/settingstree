#include <settingstree/tree.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>

#include <settingstree/delimiter.hpp>

namespace settingstree {

tree::tree(
    const std::string& readers,
    const std::string& writers,
    branch_callback& callback
  ) :
  branch("", readers, writers, NULL, callback)
{
}

std::list<std::string> tree::stringNodeAddressToList(
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

node* tree::get_node(const std::string& nodeAddress)
{
  return getNodeByList(stringNodeAddressToList(nodeAddress));
}

std::string tree::change_request(
    const std::string& nodeAddress,
    const std::string& value,
    const user& user)
{
  return changeRequestList(
      stringNodeAddressToList(nodeAddress), value, user
    );
}

boost::tuple<std::string, std::set<std::string>, node const*>
tree::get_request(
    const std::string& nodeAddress,
    const user& user
  ) const
{
  return getRequestList(stringNodeAddressToList(nodeAddress), user);
}

}

