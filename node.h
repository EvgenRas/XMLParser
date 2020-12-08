#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "atribute.h"

class Node
{
private:
    std::string name;
    std::vector<Atribute *> atributeList;
    std::string textIsNode;
    Node *parent;
    std::vector<Node *> childs;
public:
    Node();
    ~Node();
    Node(const Node&) = delete;
    Node& operator= (const Node&) = delete;
    std::string getName() const;
    void setName(const std::string &value);
    std::vector<Atribute *> getAtributeList() const;
    void setAtributeList(const std::vector<Atribute *> &value);
    void addAtribute(Atribute *value);
    std::string getTextIsNode() const;
    void setTextIsNode(const std::string &value);
    Node *getParent() const;
    void setParent(Node *value);
    std::vector<Node *> getChilds() const;
    void setChilds(const std::vector<Node *> &value);
    void addChild(Node *value);
    std::string getValueByAtributeName(const std::string &str) const;
};

#endif // NODE_H
