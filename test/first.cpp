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
  virtual std::string setting_altering(st::string_leaf& l, std::string v) {
    BOOST_CHECK_EQUAL(l.value(), "flibble");
    BOOST_CHECK_EQUAL(v, "wobble");
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

class server_user : public st::user {
  public:
    server_user() : st::user("server") {}
};

class untrusted_user : public st::user {
  public:
    untrusted_user() : st::user("world") {}
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
  untrusted_user uu;

  // Test get_node
  st::node& b_node = tree->get_node("var_bool");
  st::bool_leaf& bool_node = dynamic_cast<st::bool_leaf&>(b_node);
  BOOST_CHECK_EQUAL(bool_node.value(), true);

  // Simple accessors
  BOOST_CHECK_EQUAL(bool_node.is_leaf(), true);
  BOOST_CHECK_EQUAL(bool_node.name(), "var_bool");
  BOOST_CHECK_EQUAL(tree->is_leaf(), false);
  BOOST_CHECK_EQUAL(tree->name(), "");
  BOOST_CHECK(
      tree->child_names() == boost::assign::list_of("subtree")("var_bool")
    );
  BOOST_CHECK_EQUAL(tree->child("var_bool"), &bool_node);
  BOOST_CHECK_EQUAL(tree->full_name(), "");
  BOOST_CHECK_EQUAL(bool_node.full_name(), ":var_bool");
  BOOST_CHECK(
      tree->reading_groups() == boost::assign::list_of("server")("world")
    );
  BOOST_CHECK(tree->writing_groups() == boost::assign::list_of("server"));
  BOOST_CHECK(
      b_node.reading_groups() == boost::assign::list_of("server")("world")
    );
  BOOST_CHECK(b_node.writing_groups() == boost::assign::list_of("server"));

  // Test successful get_request
  std::string result;
  std::set<std::string> value;
  st::node const* node;

  boost::tie(result, value, node) = tree->get_request("var_bool", su);

  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("true"));
  BOOST_CHECK_EQUAL(node, &bool_node);

  // Test successful change_request
  result = tree->change_request("subtree:var_int", "3", su);
  BOOST_CHECK_EQUAL(result, "");

  // Check value actually changed
  boost::tie(result, value, node) = tree->get_request("subtree:var_int", uu);
  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("3"));
  BOOST_REQUIRE(node);
  BOOST_CHECK_EQUAL(node->full_name(), ":subtree:var_int");

  // Repeat with more superfluous name
  result = tree->change_request("::subtree:var_string", "wobble", su);
  BOOST_CHECK_EQUAL(result, "");

  // Check value actually changed
  boost::tie(result, value, node) =
    tree->get_request("::subtree:var_string", uu);
  BOOST_CHECK_EQUAL(result, "");
  BOOST_CHECK(value == boost::assign::list_of("wobble"));
  BOOST_REQUIRE(node);
  BOOST_CHECK_EQUAL(node->full_name(), ":subtree:var_string");

  // Mutating the tree
  auto s2 = tree->add_child(st::make("var_string2", c, "foo").node_ptr(*tree));
  BOOST_CHECK(
      tree->child_names() ==
      boost::assign::list_of("subtree")("var_bool")("var_string2")
    );
  BOOST_CHECK_EQUAL(s2, tree->child("var_string2"));
  BOOST_CHECK_EQUAL(s2, &tree->get_node("var_string2"));
  BOOST_CHECK_EQUAL(s2, &tree->get_node(":var_string2:"));
  tree->remove_child("var_string2");
  BOOST_CHECK(!tree->child("var_string2"));
}

