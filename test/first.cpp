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
  virtual std::string setting_altering(st::bool_leaf&, bool) {
    std::cout << "altering bool" << std::endl;
    return "";
  }
  virtual std::string setting_altering(st::int_leaf<int>& l, int v) {
    BOOST_CHECK_EQUAL(l.value(), 1);
    BOOST_CHECK_EQUAL(v, 3);
    std::cout << "altering int" << std::endl;
    return "";
  }
  virtual std::string setting_altering(st::string_leaf&, std::string) {
    std::cout << "altering string" << std::endl;
    return "";
  }
  virtual void setting_altered(st::leaf&) {
    std::cout << "altered" << std::endl;
  }
};

class test_branch_callback : public st::branch_callback {
  virtual void children_altered(st::branch&) {
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
        st::make("var_int", static_cast<st::leaf_callback<int>&>(c), 1),
        st::make("var_string", c, "flibble")
      )
    ).tree_ptr();

  server_user su;

  // Test get_node
  st::node* b_node = tree->get_node("var_bool");
  BOOST_CHECK(b_node);
  st::bool_leaf* bool_node = dynamic_cast<st::bool_leaf*>(b_node);
  BOOST_REQUIRE(bool_node);
  BOOST_CHECK_EQUAL(bool_node->value(), true);

  // Simple accessors
  BOOST_CHECK_EQUAL(bool_node->is_leaf(), true);
  BOOST_CHECK_EQUAL(bool_node->getName(), "var_bool");
  BOOST_CHECK_EQUAL(tree->is_leaf(), false);
  BOOST_CHECK_EQUAL(tree->getName(), "");
  BOOST_CHECK(
      tree->getChildNames() == boost::assign::list_of("subtree")("var_bool")
    );

  // Test successful get_request
  std::string result;
  std::set<std::string> value;
  st::node const* node;

  boost::tie(result, value, node) = tree->get_request("var_bool", su);

  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("true"));
  BOOST_CHECK_EQUAL(node, bool_node);

  // Test successful change_request
  result = tree->change_request("subtree:var_int", "3", su);
  BOOST_CHECK_EQUAL(result, "");

  // Check value actually changed
  boost::tie(result, value, node) = tree->get_request("subtree:var_int", su);
  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("3"));
}

