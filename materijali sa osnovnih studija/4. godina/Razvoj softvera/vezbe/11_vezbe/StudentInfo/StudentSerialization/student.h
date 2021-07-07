#ifndef STUDENT_H
#define STUDENT_H

#include "Serializable.h"

class CourseItem;

class STUDENTSERIALIZATION_EXPORT Student : public Serializable
{
public:
    Student();
    ~Student();

    // Serializable interface
public:
    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

private:
    QString m_name;
    QString m_surname;
    QString m_index;
    QString m_personalNumber;
    bool m_enrolled;
    QVector<CourseItem*> m_courseItems;

};

#endif // STUDENT_H
