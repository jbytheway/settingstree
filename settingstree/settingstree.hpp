#ifndef SETTINGSTREE_H
#define SETTINGSTREE_H

#include <list>

#include <settingstree/branch.hpp>
#include <settingstree/settingsuser.hpp>

namespace settingsTree {

class SettingsTree : public Branch {
  public:
    typedef boost::shared_ptr<SettingsTree> Ptr;

    SettingsTree(settings_callback*);
  private:
    std::list<std::string> stringNodeAddressToList(const std::string& nodeAddress) const;
  public:
    std::string changeRequest(
        const std::string& node,
        const std::string& value,
        const SettingsUser* user
      );
    boost::tuple<std::string, std::set<std::string>, Node::ConstPtr> getRequest(
        const std::string& nodeAddress,
        const SettingsUser* user
      ) const;
    Node* getNode(const std::string& nodeAddress);
};

}

#endif // SETTINGSTREE_H

