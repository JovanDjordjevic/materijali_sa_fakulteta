#ifndef HORSE_H
#define HORSE_H

#include <QObject>
class QVariant;

class Horse
{
public:
    Horse();
    Horse(QString name, unsigned int numberOfRaces, unsigned int numberOfVictories, unsigned int m_averageTime);

    void load(QVariant data);
    QVariant save() const;

    void toString() const;

private:
    QString m_name;
    unsigned int m_numberOfRaces;
    unsigned int m_numberOfVictories;
    unsigned int m_averageTime;

};

#endif // HORSE_H
