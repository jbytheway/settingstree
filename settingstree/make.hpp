#ifndef SETTINGSTREE__MAKE_HPP
#define SETTINGSTREE__MAKE_HPP

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <settingstree/leaf.hpp>
#include <settingstree/branch.hpp>
#include <settingstree/tree.hpp>
#include <settingstree/tree_traits.hpp>
#include <settingstree/intleaf-methods.hpp>

namespace settingstree {

namespace detail {

// Metafunction to work around the fact that fusion isn't variadic yet
template<typename... T>
struct variadic_vector {
};

template<>
struct variadic_vector<> {
  typedef boost::fusion::vector<> type;
};

template<typename T1>
struct variadic_vector<T1> {
  typedef boost::fusion::vector<T1> type;
};

template<typename T1, typename T2>
struct variadic_vector<T1, T2> {
  typedef boost::fusion::vector<T1, T2> type;
};

template<typename T>
struct leaf_template {
  leaf_template(std::string name, leaf_callback<T>& callback, T value) :
    name_(std::move(name)), callback_(callback), value_(std::move(value))
  {}

  std::string name_;
  leaf_callback<T>& callback_;
  T value_;

  node::Ptr node_ptr(branch& parent) {
    typedef typename TreeTraits<T>::LeafType leaf_type;
    node::Ptr result(new leaf_type(name_, "", "", &parent, callback_, value_));
    return result;
  }
};

template<typename... Children>
struct branch_template {
  branch_template(
      std::string name,
      branch_callback& callback,
      Children&&... children
    ) :
    name_(std::move(name)),
    callback_(callback),
    children_(std::forward<Children>(children)...)
  {}

  std::string name_;
  branch_callback& callback_;
  typename variadic_vector<Children...>::type children_;

  struct add_to_branch {
    add_to_branch(branch& b) : branch_(b) {}
    branch& branch_;
    template<typename ChildTemplate>
    void operator()(ChildTemplate& child) const {
      branch_.addChild(child.node_ptr(branch_));
    }
  };

  tree::Ptr tree_ptr() {
    assert(name_.empty());
    tree::Ptr result(new tree(callback_));
    boost::fusion::for_each(children_, add_to_branch(*result));
    return result;
  }

  node::Ptr node_ptr(branch& parent) {
    assert(!name_.empty());
    branch::Ptr result(new branch(name_, "", "", &parent, callback_));
    boost::fusion::for_each(children_, add_to_branch(*result));
    return result;
  }
};

struct make_helper {
  template<typename T>
  leaf_template<T> operator()(
      std::string name,
      leaf_callback<T>& callback,
      T value
    ) const {
    return leaf_template<T>(std::move(name), callback, std::move(value));
  }

  leaf_template<std::string> operator()(
      std::string name,
      leaf_callback<std::string>& callback,
      char const* value
    ) const {
    return leaf_template<std::string>(std::move(name), callback, value);
  }

  template<typename... Children>
  branch_template<Children...> operator()(
      std::string name,
      branch_callback& callback,
      Children&&... children
    ) const {
    return branch_template<Children...>(
        std::move(name), callback, std::forward<Children>(children)...
      );
  }
};

}

extern const detail::make_helper make;

}

#endif // SETTINGSTREE__MAKE_HPP

