#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "StudentSerialization_global.h"
#include <QVariant>

class STUDENTSERIALIZATION_EXPORT Serializable
{
public:
    virtual ~Serializable() = default;

    virtual QVariant toVariant() const = 0;
    virtual void fromVariant(const QVariant &variant) = 0;

};

#endif // SERIALIZABLE_H
