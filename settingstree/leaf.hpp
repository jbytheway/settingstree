#ifndef SETTINGSTREE__LEAF_HPP
#define SETTINGSTREE__LEAF_HPP

#include <settingstree/node.hpp>
#include <settingstree/branch.hpp>
#include <settingstree/leaf_callback.hpp>

namespace settingstree {

class leaf : public node {
  public:
    typedef std::unique_ptr<leaf> ptr;
    typedef std::unique_ptr<const leaf> const_ptr;
    leaf(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent
      );
  protected:
    virtual ~leaf() = 0;
    virtual node* getNodeByListRef(
        std::list<std::string>& nodeAddress
      );
    virtual std::string changeRequestListRef(
        std::list<std::string>& nodeAddress,
        const std::string& value,
        const settings_user& client
      );
    virtual boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const settings_user& client
      ) const;
    virtual std::string setValue(const std::string& v) = 0;
    virtual detail::generic_leaf_callback& callback() = 0;
  public:
    bool isLeaf() const { return true; }
    virtual std::set<std::string> value_set() const = 0;
};

}

#endif // SETTINGSTREE__LEAF_HPP

