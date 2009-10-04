#ifndef SETTINGSTREE__TREE_H
#define SETTINGSTREE__TREE_H

#include <list>

#include <settingstree/branch.hpp>
#include <settingstree/user.hpp>

namespace settingstree {

class tree : public branch {
  public:
    typedef std::unique_ptr<tree> ptr;
    typedef std::unique_ptr<tree const> const_ptr;

    tree(
        const std::string& readers,
        const std::string& writers,
        branch_callback&
      );

    std::string change_request(
        const std::string& node,
        const std::string& value,
        const user& user
      );
    boost::tuple<std::string, std::set<std::string>, node const*> get_request(
        const std::string& nodeAddress,
        const user& user
      ) const;
    node& get_node(const std::string& nodeAddress);
  private:
    std::list<std::string>
      stringNodeAddressToList(const std::string& nodeAddress) const;
};

}

#endif // SETTINGSTREE__TREE_H

