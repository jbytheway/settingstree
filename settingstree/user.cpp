#include <settingstree/user.hpp>

#include <settingstree/node.hpp>

namespace settingstree {

bool user::hasGroupIn(const std::set<std::string>& groupsToCheck) const
{
  /* We have to determine whether the two sets groups and groupsToCheck have an
   * intersection.  I thought there would be an STL algorithm for this, but
   * here doesn't appear to be.  There is the "setintersection" algorithm, but
   * that won't abort when it finds an intersection.  So, we do it "by hand" */
  
  std::set<std::string>::const_iterator i1 = groups_.begin();
  std::set<std::string>::const_iterator i2 = groupsToCheck.begin();

  while (true) {
    if (i1 == groups_.end()) {
      return false;
    } else if (i2 == groupsToCheck.end()) {
      return false;
    } else if (*i1 == *i2) {
      return true;
    } else if (*i1 < *i2) {
      ++i1;
    } else {
      ++i2;
    }
  }
}

bool user::hasReadPermissionFor(node const* node) const
{
  return hasGroupIn(node->reading_groups());
}

bool user::hasWritePermissionFor(node const* node) const
{
  return hasGroupIn(node->writing_groups());
}

}

