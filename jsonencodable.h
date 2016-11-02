#ifndef JSONENCODABLE_H
#define JSONENCODABLE_H

#include <QJsonObject>

//Classe abstraite dont tout objet contenant une fonction toJson doit implémenter
class JsonEncodable
{
public:
    virtual QJsonObject toJson() = 0;
};

#endif // JSONENCODABLE_H
