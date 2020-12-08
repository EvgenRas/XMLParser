#ifndef ATRIBUTE_H
#define ATRIBUTE_H

#include <string>

class Atribute
{
private:
    std::string name;
    std::string value;
public:
    explicit Atribute();
    ~Atribute();
    std::string getName() const;
    void setName(const std::string &value);
    std::string getValue() const;
    void setValue(const std::string &_value);
};

#endif // ATRIBUTE_H
