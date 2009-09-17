#include <settingstree/node.hpp>

#include <settingstree/branch.hpp>

#include <sstream>

namespace settingsTree {

Node::Node(
    const std::string& n,
    const std::string& readers,
    const std::string& writers,
    Branch* p,
    Server* s
  ) :
  name(n),
  parent(p),
  readingGroups(),
  writingGroups(),
  server(s)
{
  assert((p == NULL) == n.empty());
  assert(s != NULL);

  readingGroups.insert("server");
  writingGroups.insert("server");

  list<std::string> readerList = stringUtils_split<list<std::string> >(readers, ",");

  for (list<std::string>::iterator reader = readerList.begin();
      reader != readerList.end(); reader++) {
    readingGroups.insert(*reader);
  }

  list<std::string> writerList = stringUtils_split<list<std::string> >(writers, ",");

  for (list<std::string>::iterator writer = writerList.begin();
      writer != writerList.end(); writer++) {
    writingGroups.insert(*writer);
  }
}

std::string Node::getFullName() const
{
  ostringstream nameStream;
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

list<std::string> Node::getFullNameAsList() const
{
  list<std::string> fullName;
  appendFullNameAsList(fullName);
  return fullName;
}

void Node::streamFullName(ostream& nameStream) const
{
  if (parent != NULL) {
    parent->streamFullName(nameStream);
  }
  if (!name.empty()) {
    nameStream << SETTINGS_DELIMITER << name;
  }
}

}

