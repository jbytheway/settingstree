#include <settingstree/stringsetleaf.hpp>

using namespace std;

using namespace sakusen;
using namespace fuseki;
using namespace fuseki::settingsTree;

StringSetLeaf::StringSetLeaf(
    const std::string& name,
    const std::string& readers,
    const std::string& writers,
    Branch* parent,
    Server* server,
    const std::set<std::string>& initialValue
  ) :
  Leaf(name, readers, writers, parent, server),
  value(initialValue)
{
}

std::string StringSetLeaf::setValue(const std::string& v)
{
  if (v.empty()) {
    return "When setting the value of a list leaf, the first character must "
        "be '0', '+' or '-'";
  }
  
  set<std::string> newValue = value;
  
  switch (v[0]) {
    case '0':
      if (v.length() > 1) {
        return "When clearing a list node, the value specified must be "
          "exactly '0'";
      }
      newValue.clear();
      break;
    case '+':
      {
        std::string adding = v.substr(1);
        if (newValue.count(adding)) {
          return "std::string to be added already in list";
        }
        newValue.insert(adding);
      }
      break;
    case '-':
      {
        std::string erasing = v.substr(1);
        if (0 == newValue.count(erasing)) {
          return "std::string to be removed not in list";
        }
        newValue.erase(erasing);
      }
      break;
    default:
      return "When setting the value of a list leaf, the first character must "
        "be '0', '+' or '-'";
  }

  std::string reason;
  if ("" != 
      (reason = server->settingAlteringCallback(this, newValue))
    ) {
    return reason;
  }
  value = newValue;
  return "";
}

set<std::string> StringSetLeaf::getValue() const
{
  return value;
}

