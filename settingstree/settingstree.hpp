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
    Node::Ptr getNode(const std::string& nodeAddress);
    inline ServerBranch::Ptr getServerBranch() {
      return boost::dynamic_pointer_cast<ServerBranch>(
          getNode("server")
        );
    }
    inline ClientsBranch::Ptr getClientsBranch() {
      return boost::dynamic_pointer_cast<ClientsBranch>(
          getNode("clients")
        );
    }
    inline PlayersBranch::Ptr getPlayersBranch() {
      return boost::dynamic_pointer_cast<PlayersBranch>(
          getNode("players")
        );
    }
    inline PluginsBranch::Ptr getPluginsBranch() {
      return boost::dynamic_pointer_cast<PluginsBranch>(
          getNode("plugins")
        );
    }
};

}

#endif // SETTINGSTREE_H

