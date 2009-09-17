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
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        settings_callback*
      );
    virtual ~Leaf();
  protected:
    virtual Node* getNodeByListRef(
        std::list<std::string>& nodeAddress
      );
    virtual std::string changeRequestListRef(
        std::list<std::string>& nodeAddress,
        const std::string& value,
        const SettingsUser* client
      );
    virtual boost::tuple<std::string, std::set<std::string>, Node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const SettingsUser* client
      ) const;
    virtual std::string setValue(const std::string& v) = 0;
  public:
    bool isLeaf() const { return true; }
    virtual std::set<std::string> getValue() const = 0;
};

}

#endif // SETTINGSTREE__LEAF_HPP

