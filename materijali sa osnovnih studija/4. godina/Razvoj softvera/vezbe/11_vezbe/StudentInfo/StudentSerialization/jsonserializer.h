#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "Serializer.h"

class STUDENTSERIALIZATION_EXPORT JSONSerializer : public Serializer
{
public:
    JSONSerializer();

    // Serializer interface
public:
    void save(const Serializable &serializable, const QString &filepath, const QString &rootName) override;
    void load(Serializable &serializable, const QString &filepath) override;
};

#endif // JSONSERIALIZER_H
