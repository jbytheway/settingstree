#ifndef SETTINGSTREE_H
#define SETTINGSTREE_H

#include <list>

#include <settingstree/branch.hpp>
#include <settingstree/settings_user.hpp>

namespace settingstree {

class settings_tree : public branch {
  public:
    typedef boost::shared_ptr<settings_tree> Ptr;

    settings_tree(settings_callback*);

    std::string changeRequest(
        const std::string& node,
        const std::string& value,
        const settings_user* user
      );
    boost::tuple<std::string, std::set<std::string>, node::ConstPtr> getRequest(
        const std::string& nodeAddress,
        const settings_user* user
      ) const;
    node* getNode(const std::string& nodeAddress);
  private:
    std::list<std::string> stringNodeAddressToList(const std::string& nodeAddress) const;
};

}

#endif // SETTINGSTREE_H

