#ifndef SETTINGSTREE__LEAF_HPP
#define SETTINGSTREE__LEAF_HPP

#include <settingstree/node.hpp>
#include <settingstree/branch.hpp>

namespace settingsTree {

class Leaf : public Node {
  public:
    typedef boost::shared_ptr<Leaf> Ptr;
    typedef boost::shared_ptr<const Leaf> ConstPtr;
    Leaf(
        const String& name,
        const String& readers,
        const String& writers,
        Branch* parent,
        Server* server
      );
    virtual ~Leaf();
  protected:
    virtual Node::Ptr getNodeByListRef(
        std::list<String>& nodeAddress
      );
    virtual String changeRequestListRef(
        std::list<String>& nodeAddress,
        const String& value,
        const SettingsUser* client
      );
    virtual boost::tuple<String, std::set<String>, Node::ConstPtr>
      getRequestListRef(
        std::list<String>& nodeAddress,
        const SettingsUser* client
      ) const;
    virtual String setValue(const String& v) = 0;
  public:
    bool isLeaf() const { return true; }
    virtual std::set<String> getValue() const = 0;
};

}

#endif // SETTINGSTREE__LEAF_HPP

