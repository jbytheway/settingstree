#ifndef SETTINGSTREE__LEAF_HPP
#define SETTINGSTREE__LEAF_HPP

#include <settingstree/node.hpp>
#include <settingstree/branch.hpp>

namespace settingstree {

class leaf : public node {
  public:
    typedef boost::shared_ptr<leaf> Ptr;
    typedef boost::shared_ptr<const leaf> ConstPtr;
    leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        settings_callback*
      );
    virtual ~leaf();
  protected:
    virtual node* getNodeByListRef(
        std::list<std::string>& nodeAddress
      );
    virtual std::string changeRequestListRef(
        std::list<std::string>& nodeAddress,
        const std::string& value,
        const settings_user* client
      );
    virtual boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const settings_user* client
      ) const;
    virtual std::string setValue(const std::string& v) = 0;
  public:
    bool isLeaf() const { return true; }
    virtual std::set<std::string> getValue() const = 0;
};

}

#endif // SETTINGSTREE__LEAF_HPP

