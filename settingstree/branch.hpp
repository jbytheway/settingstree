#ifndef SETTINGSTREE__BRANCH_HPP
#define SETTINGSTREE__BRANCH_HPP

#include <list>

#include <boost/unordered_map.hpp>

#include <settingstree/node.hpp>

namespace settingsTree {

class Branch : public Node {
  public:
    typedef boost::shared_ptr<Branch> Ptr;
    typedef boost::shared_ptr<const Branch> ConstPtr;
  protected:
    Branch(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        settings_callback*
      );
  private:
    boost::unordered_map<std::string, Node::Ptr> children;

  protected:
    Node::Ptr addChild(Node::Ptr child);
    void removeChild(std::string name);
    virtual Node* getNodeByListRef(std::list<std::string>& nodeAddress);
    virtual std::string changeRequestListRef(
        std::list<std::string>& setting,
        const std::string& value,
        const SettingsUser* user
      );
    virtual boost::tuple<std::string, std::set<std::string>, Node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const SettingsUser* user
      ) const;
  public:
    bool isLeaf() const { return false; }
    std::set<std::string> getChildNames() const;
    /* Returns Node::Ptr() if no such child */
    Node::Ptr getChild(std::string name);
    /* Returns Node::ConstPtr() if no such child */
    Node::ConstPtr getChild(std::string name) const;
};

}

#endif // SETTINGSTREE__BRANCH_HPP

