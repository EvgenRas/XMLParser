#include "node.h"

std::string Node::getName() const
{
    return name;
}

void Node::setName(const std::string &value)
{
    name = value;
}

std::vector<Atribute *> Node::getAtributeList() const
{
    return atributeList;
}

void Node::setAtributeList(const std::vector<Atribute *> &value)
{
    atributeList = value;
}

void Node::addAtribute(Atribute *value)
{
    atributeList.push_back(value);
}

std::string Node::getTextIsNode() const
{
    return textIsNode;
}

void Node::setTextIsNode(const std::string &value)
{
    textIsNode = value;
}

Node *Node::getParent() const
{
    return parent;
}

void Node::setParent(Node *value)
{
    parent = value;
}

std::vector<Node *> Node::getChilds() const
{
    return childs;
}

void Node::setChilds(const std::vector<Node *> &value)
{
    childs = value;
}

void Node::addChild(Node *value)
{
    childs.push_back(value);
}

std::string Node::getValueByAtributeName(const std::string &str) const
{
    std::string res = "";
    for(const Atribute * atr: atributeList)
    {
        if(atr->getName() == str)
            res = atr->getValue();
    }
    return res;
}

Node::Node() : name(""), textIsNode(""), parent(0)
{
}
Node::~Node()
{
    std::vector<Atribute*>::iterator itAtr;
    for (itAtr = atributeList.begin(); itAtr != atributeList.end(); ++itAtr)
    {
        delete *itAtr;
        *itAtr = 0;
    }
    atributeList.clear();
    childs.clear();
    parent = 0;
}
