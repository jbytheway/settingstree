#ifndef SETTINGSTREE__SETTINGS_USER_HPP
#define SETTINGSTREE__SETTINGS_USER_HPP

#include <set>
#include <string>
#include <cassert>

namespace settingstree {

class node;

/** \brief Abstract class representing an object which can access or alter the
 * settings tree
 *
 * This class keeps track of what groups a user of the settings tree belongs to
 * so that permissions can be calculated appropriately. */
class user {
  protected:
    /** \brief Standard constructor
     *
     * Initializes user as a member of the groups "world" and each group in
     * \a groups. */
    template<typename... String>
    user(String&&... groups);
    user(const user&);
  public:
    /** \brief Destructor */
    virtual ~user() = 0;
  private:
    std::set<std::string> groups_;

  public:
    /** \return true iff this user belongs to the group \a group */
    inline bool hasGroup(const std::string& group) const {
      return groups_.find(group) != groups_.end();
    }
    /** \return true iff this user belongs to at least one of the groups in \a
     * groupsToCheck */
    bool hasGroupIn(const std::set<std::string>& groupsToCheck) const;
    /** \brief Adds a group to those of which this user is a member */
    inline void addGroup(const std::string& group) { groups_.insert(group); }
    inline void addGroups() {}
    /** \brief Adds each group given */
    template<typename HString, typename... String>
    void addGroups(HString&&, String&&...);
    /** \brief Removes a group from those to which this user is a member */
    inline void removeGroup(const std::string& group) {
      assert(hasGroup(group));
      groups_.erase(group);
    }
    /** \brief Clears all groups of which this user is a member */
    inline void clearGroups() { groups_.clear(); }
    /** \return true iff this user has permission to read \a node */
    bool hasReadPermissionFor(const node* node) const;
    /** \return true iff this user has permission to write \a node */
    bool hasWritePermissionFor(const node* node) const;
};

inline user::user(const user&) = default;
inline user::~user() = default;

template<typename... String>
user::user(String&&... groups)
{
  groups_.insert("world");
  addGroups(std::forward<String>(groups)...);
}

template<typename HString, typename... String>
inline void user::addGroups(
    HString&& hgroup,
    String&&... groups
  )
{
  addGroup(std::forward<HString>(hgroup));
  addGroups(std::forward<String>(groups)...);
}

}

#endif // SETTINGSTREE__SETTINGS_USER_HPP

