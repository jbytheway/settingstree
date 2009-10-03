#include <settingstree/node.hpp>

#include <sstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <settingstree/branch.hpp>
#include <settingstree/delimiter.hpp>

namespace settingstree {

node::~node()
{
}

node::node(
    const std::string& n,
    const std::string& readers,
    const std::string& writers,
    branch* p
  ) :
  name_(n),
  parent_(p),
  reading_groups_(),
  writing_groups_()
{
  assert((p == NULL) == n.empty());

  reading_groups_.insert("server");
  writing_groups_.insert("server");

  std::list<std::string> readerList;
  boost::algorithm::split(
      readerList, readers, boost::phoenix::arg_names::arg1 == ','
    );

  for (std::list<std::string>::iterator reader = readerList.begin();
      reader != readerList.end(); reader++) {
    reading_groups_.insert(*reader);
  }

  std::list<std::string> writerList;
  boost::algorithm::split(
      writerList, writers, boost::phoenix::arg_names::arg1 == ','
    );

  for (std::list<std::string>::iterator writer = writerList.begin();
      writer != writerList.end(); writer++) {
    writing_groups_.insert(*writer);
  }
}

std::string node::full_name() const
{
  std::ostringstream nameStream;
  streamFullName(nameStream);
  return nameStream.str();
}

void node::appendFullNameAsList(std::list<std::string>& fullName) const
{
  if (parent_) {
    parent_->appendFullNameAsList(fullName);
  }
  if (!name_.empty()) {
    fullName.push_back(name_);
  }
}

std::list<std::string> node::getFullNameAsList() const
{
  std::list<std::string> fullName;
  appendFullNameAsList(fullName);
  return fullName;
}

void node::streamFullName(std::ostream& nameStream) const
{
  if (parent_) {
    parent_->streamFullName(nameStream);
  }
  if (!name_.empty()) {
    nameStream << SETTINGSTREE_DELIMITER << name_;
  }
}

}

