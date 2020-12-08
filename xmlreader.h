#ifndef XMLREADER_H
#define XMLREADER_H

#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "node.h"
#include "atribute.h"

class XmlReader
{
private:
    std::ifstream *file;
    char *buffer;
    std::vector<Node *> listNodes;
    const char *posNew;

    std::string getRowTokens();
    Atribute *getAtributes();

    std::string getTextIsNode();
    std::string getTagName();
    void saveFileInBuffer();
    void getXmlTokens();

public:
    std::vector<Node *> getNodeByName(const std::string &_name);
    XmlReader(std::string fileName);
    ~XmlReader();

    std::vector<Node *> getListNodes() const;
};

#endif // XMLREADER_H
