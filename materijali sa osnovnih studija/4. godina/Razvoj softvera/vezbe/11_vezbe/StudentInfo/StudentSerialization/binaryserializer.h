#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "Serializer.h"

class STUDENTSERIALIZATION_EXPORT BinarySerializer : public Serializer
{
public:
    BinarySerializer();

    // Serializer interface
public:
    void save(const Serializable &serializable, const QString &filepath, const QString &rootName) override;
    void load(Serializable &serializable, const QString &filepath) override;
};

#endif // BINARYSERIALIZER_H
