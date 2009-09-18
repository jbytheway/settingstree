#include <settingstree/node.hpp>

#include <sstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <settingstree/branch.hpp>
#include <settingstree/delimiter.hpp>

namespace settingstree {

Node::Node(
    const std::string& n,
    const std::string& readers,
    const std::string& writers,
    Branch* p,
    settings_callback* callback
  ) :
  callback_(callback),
  name(n),
  parent(p),
  readingGroups(),
  writingGroups()
{
  assert((p == NULL) == n.empty());
  assert(callback != NULL);

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

std::string Node::getFullName() const
{
  std::ostringstream nameStream;
  streamFullName(nameStream);
  return nameStream.str();
}

void Node::appendFullNameAsList(std::list<std::string>& fullName) const
{
  if (parent != NULL) {
    parent->appendFullNameAsList(fullName);
  }
  if (!name.empty()) {
    fullName.push_back(name);
  }
}

std::list<std::string> Node::getFullNameAsList() const
{
  std::list<std::string> fullName;
  appendFullNameAsList(fullName);
  return fullName;
}

void Node::streamFullName(std::ostream& nameStream) const
{
  if (parent != NULL) {
    parent->streamFullName(nameStream);
  }
  if (!name.empty()) {
    nameStream << SETTINGSTREE_DELIMITER << name;
  }
}

}

