#ifndef SETTINGSTREE__NODE_HPP
#define SETTINGSTREE__NODE_HPP

#include <list>
#include <iosfwd>
#include <memory>

#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <boost/tuple/tuple.hpp>

#include <settingstree/settings_user.hpp>
#include <settingstree/leaf_callback.hpp>

namespace settingstree {

class branch;

class node :
  public boost::enable_shared_from_this<node>,
  private boost::noncopyable {
  public:
    typedef std::unique_ptr<node> ptr;
    typedef std::unique_ptr<const node> const_ptr;

    virtual ~node() = 0;

    inline const std::string& getName() const { return name; }
    virtual bool is_leaf() const = 0;
    inline const std::set<std::string>& getReadingGroups() const {
      return readingGroups;
    }
    inline const std::set<std::string>& getWritingGroups() const {
      return writingGroups;
    }
    virtual node* getNodeByListRef(
        std::list<std::string>& nodeAddress
      ) = 0; /* Note: alters its argument nodeAddress */
    inline node* getNodeByList(
        std::list<std::string> nodeAddress
      ) { return getNodeByListRef(nodeAddress); }
    virtual void streamFullName(std::ostream& nameStream) const;
    virtual std::string getFullName() const;
    virtual void appendFullNameAsList(std::list<std::string>&) const;
    virtual std::list<std::string> getFullNameAsList() const;
    virtual std::string changeRequestListRef(
        std::list<std::string>& nodeAddress,
        const std::string& value,
        const settings_user& user
      ) = 0; /* Note: alters its argument nodeAddress */
    inline std::string changeRequestList(
        std::list<std::string> nodeAddress,
        const std::string& value,
        const settings_user& user
      ) { return changeRequestListRef(nodeAddress, value, user); }
    virtual boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const settings_user& user
      ) const = 0; /* Note: alters its argument nodeAddress */
    inline boost::tuple<std::string, std::set<std::string>, node const*>
      getRequestList(
        std::list<std::string> nodeAddress,
        const settings_user& user
      ) const { return getRequestListRef(nodeAddress, user); }
  protected:
    node(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        branch* parent
      ); /* both readers and writers are interpreted as a comma-seperated list
            of group names.  'server' is added automatically to both lists */
  private:
    std::string name;
    branch* parent;
      /* node above this in the tree (NULL if this is the root node).
       * Not owned by this. */
    std::set<std::string> readingGroups; /* Groups with read permission */
    std::set<std::string> writingGroups; /* Groups with write permission */
};

}

#endif // SETTINGSTREE__NODE_HPP

