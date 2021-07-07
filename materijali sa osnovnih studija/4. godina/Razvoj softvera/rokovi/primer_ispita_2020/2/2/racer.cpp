#include "racer.h"
#include <QVariant>

Racer::Racer()
{
}

Racer::Racer(QString name, unsigned speed, double percentage)
    : m_name(name), m_speed(speed), m_percentage(percentage)
{

}

QString Racer::toQString() const
{
    QString res = m_name + ": " + QString{int(m_percentage)/10, '#'};
    return res;
}

void Racer::fromVariant(const QVariant &variant)
{
    QVariantMap vmap = variant.toMap();
    m_name = vmap.value("name").toString();
    m_speed = vmap.value("speed").toUInt();
    m_percentage = vmap.value("percentage").toDouble();
}

QVariant Racer::toVariant() const
{
    QVariantMap vmap;

    vmap.insert("name", m_name);
    vmap.insert("speed", m_speed);
    vmap.insert("percentage", m_percentage);

    return vmap;
}
