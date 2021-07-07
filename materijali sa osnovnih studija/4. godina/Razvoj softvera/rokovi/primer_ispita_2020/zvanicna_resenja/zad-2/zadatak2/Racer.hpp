#ifndef RACER_HPP
#define RACER_HPP

#include <QString>
#include <QVariant>

class Racer
{
public:
    Racer();

//    Racer(const Racer &) = delete;
//    Racer(Racer &&) = delete;

//    Racer & operator=(const Racer &) = delete;
//    Racer & operator=(Racer &&) = delete;

    QString name() const;
    unsigned speed() const;
    double percent() const;

    void setPercent(double value);

    QString toQString() const;

    void fromVariant(const QVariant &variant);

private:
    QString m_name;
    unsigned m_speed;
    double m_percent;
};

#endif // RACER_HPP
