#ifndef SETTINGSTREE__BRANCH_HPP
#define SETTINGSTREE__BRANCH_HPP

#include <list>

#include <boost/unordered_map.hpp>

#include <settingstree/node.hpp>
#include <settingstree/branch_callback.hpp>

namespace settingstree {

class branch : public node {
  public:
    typedef std::unique_ptr<branch> ptr;
    typedef std::unique_ptr<const branch> const_ptr;

    branch(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent,
        branch_callback&
      );
  private:
    boost::unordered_map<std::string, node::ptr> children_;
    branch_callback& callback_;
  protected:
    virtual node* getNodeByListRef(std::list<std::string>& nodeAddress);
    virtual std::string changeRequestListRef(
        std::list<std::string>& setting,
        const std::string& value,
        const user& user
      );
    virtual boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const user& user
      ) const;
  public:
    node* addChild(node::ptr child);
    void removeChild(std::string name);
    bool is_leaf() const { return false; }
    std::set<std::string> child_names() const;
    /* Returns NULL if no such child */
    node* child(std::string name);
    /* Returns NULL if no such child */
    node const* child(std::string name) const;
};

}

#endif // SETTINGSTREE__BRANCH_HPP

