#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <memory>

#include <boost/assign/list_of.hpp>

#include <settingstree/tree.hpp>
#include <settingstree/make.hpp>

namespace st = settingstree;

class test_callback :
  public st::leaf_callback<bool>,
  public st::leaf_callback<int>,
  public st::leaf_callback<std::string>
{
  virtual std::string settingAlteringCallback(st::leaf*, bool) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual std::string settingAlteringCallback(st::leaf*, int) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual std::string settingAlteringCallback(st::leaf*, std::string) {
    std::cout << "altering" << std::endl;
    return "";
  }
  virtual void settingAlteredCallback(st::leaf*) {
    std::cout << "altered" << std::endl;
  }
};

class test_branch_callback : public st::branch_callback {
  virtual void childrenAlteredCallback(st::branch*) {
    std::cout << "children altered" << std::endl;
  }
};

class server_user : public st::settings_user {
  public:
    server_user() : st::settings_user("server") {}
};

BOOST_AUTO_TEST_CASE(first)
{
  test_callback c;
  test_branch_callback bc;

  st::tree::ptr tree =
    st::make("", bc,
      st::make("var_bool", static_cast<st::leaf_callback<bool>&>(c), true),
      st::make("subtree", bc,
        st::make("var_int", static_cast<st::leaf_callback<int>&>(c), 0),
        st::make("var_string", c, "flibble")
      )
    ).tree_ptr();

  server_user su;

  // Test get_node
  st::node* bool_node = tree->get_node("var_bool");
  BOOST_CHECK(bool_node);

  // Test successful get_request
  std::string result;
  std::set<std::string> value;
  st::node const* node;

  boost::tie(result, value, node) = tree->get_request("var_bool", su);

  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("true"));
  BOOST_CHECK_EQUAL(node, bool_node);

  // Test successful changeRequest
  result = tree->changeRequest("subtree:var_int", "3", su);
  BOOST_CHECK_EQUAL(result, "");

  // Check value actually changed
  boost::tie(result, value, node) = tree->get_request("subtree:var_int", su);
  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("3"));
}

