#ifndef SETTINGSTREE__BRANCH_HPP
#define SETTINGSTREE__BRANCH_HPP

#include <list>

#include <boost/unordered_map.hpp>

#include <settingstree/node.hpp>
#include <settingstree/branch_callback.hpp>

namespace settingstree {

class branch : public node {
  public:
    typedef boost::shared_ptr<branch> Ptr;
    typedef boost::shared_ptr<const branch> ConstPtr;

    branch(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        branch_callback&
      );
  private:
    boost::unordered_map<std::string, node::Ptr> children;
    branch_callback& callback_;
  protected:
    virtual node* getNodeByListRef(std::list<std::string>& nodeAddress);
    virtual std::string changeRequestListRef(
        std::list<std::string>& setting,
        const std::string& value,
        const settings_user* user
      );
    virtual boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const settings_user* user
      ) const;
  public:
    node::Ptr addChild(node::Ptr child);
    void removeChild(std::string name);
    bool isLeaf() const { return false; }
    std::set<std::string> getChildNames() const;
    /* Returns node::Ptr() if no such child */
    node::Ptr getChild(std::string name);
    /* Returns node::ConstPtr() if no such child */
    node::ConstPtr getChild(std::string name) const;
};

}

#endif // SETTINGSTREE__BRANCH_HPP

