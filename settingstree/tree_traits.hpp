#ifndef SETTINGSTREE__TREETRAITS_H
#define SETTINGSTREE__TREETRAITS_H

#include <settingstree/intleaf.hpp>
#include <settingstree/string_leaf.hpp>
#include <settingstree/stringsetleaf.hpp>
#include <settingstree/bool_leaf.hpp>

namespace settingstree {

/** \brief Traits class for helping with settings tree generic programming */
template<typename T>
struct TreeTraits {
  /** \brief Allows determination of the correct type of leaf to use to store
   * data of type T */
  typedef IntLeaf<T> LeafType;
};

template<>
struct TreeTraits<std::string> {
  typedef StringLeaf LeafType;
};

template<>
struct TreeTraits<std::set<std::string> > {
  typedef StringSetLeaf LeafType;
};

template<>
struct TreeTraits<bool> {
  typedef BoolLeaf LeafType;
};

}

#endif // SETTINGSTREE__TREETRAITS_H

