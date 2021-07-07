#ifndef COURSEITEM_H
#define COURSEITEM_H

#include "Serializable.h"

class STUDENTSERIALIZATION_EXPORT CourseItem : public Serializable
{
public:
    CourseItem();

    // Serializable interface
public:
    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

private:
    QString m_name;
    unsigned m_espb;

};

#endif // COURSEITEM_H
