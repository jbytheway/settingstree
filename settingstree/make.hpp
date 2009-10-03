#ifndef SETTINGSTREE__MAKE_HPP
#define SETTINGSTREE__MAKE_HPP

#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <settingstree/branch.hpp>
#include <settingstree/tree.hpp>
#include <settingstree/tree_traits.hpp>
#include <settingstree/bool_leaf.hpp>
#include <settingstree/string_leaf.hpp>
#include <settingstree/string_set_leaf.hpp>
#include <settingstree/int_leaf-methods.hpp>

namespace settingstree {

namespace detail {

// Metafunctions to work around the fact that fusion isn't variadic yet
template<typename... Args>
struct variadic_sequence;

template<>
struct variadic_sequence<>
{
  typedef boost::mpl::vector<>::type type;
};

template<typename First, typename... More>
struct variadic_sequence<First, More...>
{
  typedef typename boost::mpl::push_front<
      typename variadic_sequence<More...>::type,
      First
    >::type type;
};

template<typename... Args>
struct variadic_vector {
  typedef typename boost::fusion::result_of::as_vector<
      typename variadic_sequence<Args...>::type
    >::type type;
};

template<typename T>
struct leaf_template {
  leaf_template(std::string name, leaf_callback<T>& callback, T value) :
    name_(std::move(name)), callback_(callback), value_(std::move(value))
  {}

  std::string name_;
  leaf_callback<T>& callback_;
  T value_;

  node::ptr node_ptr(branch& parent) {
    typedef typename tree_traits<T>::leaf_type leaf_type;
    node::ptr result(
        new leaf_type(name_, "world", "", &parent, callback_, value_)
      );
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

  tree::ptr tree_ptr() {
    assert(name_.empty());
    tree::ptr result(new tree("world", "", callback_));
    boost::fusion::for_each(children_, add_to_branch(*result));
    return result;
  }

  node::ptr node_ptr(branch& parent) {
    assert(!name_.empty());
    branch::ptr result(new branch(name_, "world", "", &parent, callback_));
    boost::fusion::for_each(children_, add_to_branch(*result));
    return std::move(result);
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

