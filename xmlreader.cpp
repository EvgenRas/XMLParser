#include "xmlreader.h"
#include<iostream>

std::vector<Node *> XmlReader::getListNodes() const
{
    return listNodes;
}
std::string XmlReader::getRowTokens()
{
    std::string tmp = "";
    if(*buffer== '<')
        ++buffer;
    for(; *buffer != '<'; ++buffer)
    {
        if(*buffer == 0)
            break;
        if(*buffer == 13 || *buffer == 10 || *buffer == '\t')
            continue;
        tmp += *buffer;
    }
    return tmp;
}
Atribute *XmlReader::getAtributes()
{
    char sym = '"';
    std::string tmpNew = "";
    Atribute *atrib = new Atribute;        
    for(; *posNew != '='; ++posNew)
            tmpNew += *posNew;
    if(tmpNew[0] == ' ')
        tmpNew.assign(tmpNew, 1);
    /// atrName
    atrib->setName(tmpNew);
    if(*posNew == '=')
        ++posNew;    
    if(*posNew == '"' || *posNew == '\'')
        sym = *posNew;
    ++posNew;
    tmpNew = "";
    for(; *posNew != sym; ++posNew)
    {
        if(*posNew == ' ' && *(posNew + 1) == ' ')
            continue;
        tmpNew += *posNew;
    }
    if(*posNew == sym)
        ++posNew;
    /// atrVal
    atrib->setValue(tmpNew);
    return atrib;
}
std::string XmlReader::getTextIsNode()
{
    std::string str = "";
    if(*posNew == '/' || *posNew == '?' || (*posNew == '>' && std::string(posNew).size() == 1))
        for(; *posNew; ++posNew);
    if(*posNew == '>')
        ++posNew;
    for(; *posNew; ++posNew)
    {
        if(*posNew == ' ' && *(posNew + 1) == ' ')
            continue;
        str += *posNew;
    }
    return str;
}
std::string XmlReader::getTagName()
{
    std::string tmpNew = "";
    for(; *posNew; ++posNew)
    {
        if(*posNew == '>' || *posNew == ' ' || (*posNew == '?' && *(buffer + 1) == '>') || (*posNew == '/' && *(buffer + 1) == '>'))
            break;
        tmpNew += *posNew;
    }
    return tmpNew;
}
void XmlReader::saveFileInBuffer()
{
    file->seekg(0, std::ios::end);
    int fileSize = file->tellg();
    file->seekg(0, std::ios::beg);
    buffer =  new char[fileSize];
    file->read(buffer, fileSize);
    file->close();
    delete file;
    file = 0;
}
void XmlReader::getXmlTokens()
{
    std::stack<Node*> stackNodes;
    stackNodes.push(0);
    do
    {
        std::string rowToken = getRowTokens();
        Node *node = new Node;
        posNew = rowToken.c_str();
        std::string tmpNew = "";
        if(rowToken[0] != '?' && rowToken[0] != '/' && rowToken[rowToken.length() - 2] != '/')
        {
            node->setParent(stackNodes.top());
            stackNodes.push(node);
        }
        if(rowToken[rowToken.length() - 2] == '/')
            node->setParent(stackNodes.top());
        if(rowToken[0] == '/')
        {
            stackNodes.pop();
            node->setParent(stackNodes.top());
        }
        node->setName(getTagName());
        //std::cout << node->getName() << "--- parent: " << (node->getParent() != 0? node->getParent()->getName(): "null" ) << std::endl;
        if(node->getParent() != 0 && node->getName()[0] != '/')
           node->getParent()->addChild(node);
        while(*posNew == ' ')
        {
            if((*(posNew+1) == '/' && *(posNew+2) == '>') || (*(posNew+1) == '?' && *(posNew+2) == '>') || *(posNew+1) == '/')
                break;
            node->addAtribute(getAtributes());
        }
        node->setTextIsNode(getTextIsNode());
        if(node->getName()[0] != '/')
            listNodes.push_back(node);
    }while(*buffer);

}

std::vector<Node *> XmlReader::getNodeByName(const std::string &_name)
{
    std::vector<Node *> tmp;
    for(Node *item : listNodes)
    {
        if(item->getName() == _name)
            tmp.push_back(item);
    }
    return tmp;
}
XmlReader::XmlReader(std::string fileName)
{
    file = new std::ifstream;
    file->exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit) ;
    try
    {
        file->open(fileName) ;
    }
    catch (const std::ios_base::failure & e)
    {
        perror("");
    }
    if(file->is_open())
    {
        saveFileInBuffer();
        getXmlTokens();
    }
}
XmlReader::~XmlReader()
{
    std::vector<Node *>::iterator itNode;
    for (itNode = listNodes.begin(); itNode != listNodes.end(); ++itNode)
    {
        delete *itNode;
        *itNode = 0;
    }
    listNodes.clear();
}
