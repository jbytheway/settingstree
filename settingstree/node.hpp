#ifndef SETTINGSTREE__NODE_HPP
#define SETTINGSTREE__NODE_HPP

#include <list>
#include <iosfwd>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>
#include <boost/tuple/tuple.hpp>

#include <settingstree/settingsuser.hpp>

namespace settingsTree {

class Branch;

class Node : private boost::noncopyable {
  public:
    typedef boost::shared_ptr<Node> Ptr;
    typedef boost::shared_ptr<const Node> ConstPtr;
  protected:
    Node(
        const std::string& name,
        const std::string& readers,
        const std::string& writers,
        Branch* parent,
        fuseki::Server* server
      ); /* both readers and writers are interpreted as a comma-seperated list
            of group names.  'server' is added automatically to both lists */
  public:
    virtual ~Node() {}
  private:
    std::string name;
    Branch* parent;
      /* node above this in the tree (NULL if this is the root node).
       * Not owned by this. */
    std::set<std::string> readingGroups; /* Groups with read permission */
    std::set<std::string> writingGroups; /* Groups with write permission */
  protected:
    fuseki::Server* server; /* The server whose tree this is */

    virtual Node::Ptr ptrToThis();
    virtual Node::ConstPtr ptrToThis() const;
  public:
    inline const std::string& getName() const { return name; }
    virtual bool isLeaf() const = 0;
    inline const std::set<std::string>& getReadingGroups() const {
      return readingGroups;
    }
    inline const std::set<std::string>& getWritingGroups() const {
      return writingGroups;
    }
    virtual Node::Ptr getNodeByListRef(
        std::list<std::string>& nodeAddress
      ) = 0; /* Note: alters its argument nodeAddress */
    inline Node::Ptr getNodeByList(
        std::list<std::string> nodeAddress
      ) { return getNodeByListRef(nodeAddress); }
    virtual void streamFullName(std::ostream& nameStream) const;
    virtual std::string getFullName() const;
    virtual void appendFullNameAsList(std::list<std::string>&) const;
    virtual std::list<std::string> getFullNameAsList() const;
    virtual std::string changeRequestListRef(
        std::list<std::string>& nodeAddress,
        const std::string& value,
        const SettingsUser* user
      ) = 0; /* Note: alters its argument nodeAddress */
    inline std::string changeRequestList(
        std::list<std::string> nodeAddress,
        const std::string& value,
        const SettingsUser* user
      ) { return changeRequestListRef(nodeAddress, value, user); }
    virtual boost::tuple<std::string, std::set<std::string>, Node::ConstPtr>
      getRequestListRef(
        std::list<std::string>& nodeAddress,
        const SettingsUser* user
      ) const = 0; /* Note: alters its argument nodeAddress */
    inline boost::tuple<std::string, std::set<std::string>, Node::ConstPtr>
      getRequestList(
        std::list<std::string> nodeAddress,
        const SettingsUser* user
      ) const { return getRequestListRef(nodeAddress, user); }
};

}

#endif // SETTINGSTREE__NODE_HPP

