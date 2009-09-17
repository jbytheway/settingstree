#ifndef SETTINGSTREE__SETTINGSUSER_HPP
#define SETTINGSTREE__SETTINGSUSER_HPP

#include <set>

#include <boost/shared_ptr.hpp>

namespace settingsTree {

class Node;

/** \brief Abstract class representing an object which can access or alter the
 * settings tree
 *
 * This class keeps track of what groups a user of the settings tree belongs to
 * so that permissions can be calculated appropriately. */
class SettingsUser {
  private:
    SettingsUser();
  protected:
    /** \brief Standard constructor
     *
     * Initializes user as a member of the groups "world" and \a group. */
    SettingsUser(const std::string& group);
    SettingsUser(const SettingsUser&);
  public:
    /** \brief Destructor */
    virtual ~SettingsUser() {}
  private:
    std::set<std::string> groups;

  public:
    /** \return true iff this user belongs to the group \a group */
    inline bool hasGroup(const std::string& group) const {
      return groups.find(group) != groups.end();
    }
    /** \return true iff this user belongs to at least one of the groups in \a
     * groupsToCheck */
    bool hasGroupIn(const std::set<std::string>& groupsToCheck) const;
    /** \brief Adds a group to those of which this user is a member */
    inline void addGroup(const std::string& group) { groups.insert(group); }
    /** \brief Removes a group from those to which this user is a member */
    inline void removeGroup(const std::string& group) {
      assert(hasGroup(group));
      groups.erase(group);
    }
    /** \brief Clears all groups of which this user is a member */
    inline void clearGroups() { groups.clear(); }
    /** \return true iff this user has permission to read \a node */
    bool hasReadPermissionFor(
        boost::shared_ptr<const settingsTree::Node> node
      ) const;
    /** \return true iff this user has permission to write \a node */
    bool hasWritePermissionFor(
        boost::shared_ptr<const settingsTree::Node> node
      ) const;
};

}

#endif // SETTINGSTREE__SETTINGSUSER_HPP

