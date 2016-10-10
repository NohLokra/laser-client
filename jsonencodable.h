#ifndef JSONENCODABLE_H
#define JSONENCODABLE_H

#include <QJsonObject>

class JsonEncodable
{
public:
    virtual QJsonObject toJson() = 0;
};

#endif // JSONENCODABLE_H
