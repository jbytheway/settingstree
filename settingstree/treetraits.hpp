#ifndef SETTINGSTREE__TREETRAITS_H
#define SETTINGSTREE__TREETRAITS_H

#include <settingstree/intleaf.hpp>
#include <settingstree/stringleaf.hpp>
#include <settingstree/stringsetleaf.hpp>
#include <settingstree/boolleaf.hpp>

namespace settingsTree {

/** \brief Traits class for helping with settings tree generic programming */
template<typename T>
struct TreeTraits {
  /** \brief Allows determination of the correct type of leaf to use to store
   * data of type T */
  typedef IntLeaf<T> LeafType;
};

template<>
struct TreeTraits<String> {
  typedef StringLeaf LeafType;
};

template<>
struct TreeTraits<std::set<String> > {
  typedef StringSetLeaf LeafType;
};

template<>
struct TreeTraits<bool> {
  typedef BoolLeaf LeafType;
};

}

#endif // SETTINGSTREE__TREETRAITS_H

