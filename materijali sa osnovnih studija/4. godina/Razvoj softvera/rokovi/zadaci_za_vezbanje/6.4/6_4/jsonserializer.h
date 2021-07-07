#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "map.h"

class JSONSerializer
{
public:
    JSONSerializer();
    void load(Map &map, QString &filepath);
};

#endif // JSONSERIALIZER_H
