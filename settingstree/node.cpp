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
  name(n),
  parent(p),
  readingGroups(),
  writingGroups()
{
  assert((p == NULL) == n.empty());

  readingGroups.insert("server");
  writingGroups.insert("server");

  std::list<std::string> readerList;
  boost::algorithm::split(
      readerList, readers, boost::phoenix::arg_names::arg1 == ','
    );

  for (std::list<std::string>::iterator reader = readerList.begin();
      reader != readerList.end(); reader++) {
    readingGroups.insert(*reader);
  }

  std::list<std::string> writerList;
  boost::algorithm::split(
      writerList, writers, boost::phoenix::arg_names::arg1 == ','
    );

  for (std::list<std::string>::iterator writer = writerList.begin();
      writer != writerList.end(); writer++) {
    writingGroups.insert(*writer);
  }
}

std::string node::getFullName() const
{
  std::ostringstream nameStream;
  streamFullName(nameStream);
  return nameStream.str();
}

void node::appendFullNameAsList(std::list<std::string>& fullName) const
{
  if (parent != NULL) {
    parent->appendFullNameAsList(fullName);
  }
  if (!name.empty()) {
    fullName.push_back(name);
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
  if (parent != NULL) {
    parent->streamFullName(nameStream);
  }
  if (!name.empty()) {
    nameStream << SETTINGSTREE_DELIMITER << name;
  }
}

}

