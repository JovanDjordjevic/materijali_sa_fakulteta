#ifndef RACER_H
#define RACER_H

#include <QObject>

class Racer
{
public:
    Racer();
    Racer(QString name, unsigned speed, double percentage);

    QString toQString() const;
    void fromVariant(const QVariant &variant);
    //ovaj ne treba ali implementirao sam ga za vezbu
    QVariant toVariant() const;

//private:
public:
    QString m_name;
    unsigned m_speed;
    double m_percentage;
};

#endif // RACER_H
