#ifndef SETTINGSTREE__TREETRAITS_H
#define SETTINGSTREE__TREETRAITS_H

#include <settingstree/int_leaf.hpp>
#include <settingstree/string_leaf.hpp>
#include <settingstree/string_set_leaf.hpp>
#include <settingstree/bool_leaf.hpp>

namespace settingstree {

/** \brief Traits class for helping with settings tree generic programming */
template<typename T>
struct tree_traits {
  /** \brief Allows determination of the correct type of leaf to use to store
   * data of type T */
  typedef int_leaf<T> leaf_type;
};

template<>
struct tree_traits<std::string> {
  typedef string_leaf leaf_type;
};

template<>
struct tree_traits<std::set<std::string> > {
  typedef string_set_leaf leaf_type;
};

template<>
struct tree_traits<bool> {
  typedef bool_leaf leaf_type;
};

}

#endif // SETTINGSTREE__TREETRAITS_H

