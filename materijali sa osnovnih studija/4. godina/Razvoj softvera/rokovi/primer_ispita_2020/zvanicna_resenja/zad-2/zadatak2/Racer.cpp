#include "Racer.hpp"

Racer::Racer()
{

}

QString Racer::name() const
{
    return m_name;
}

unsigned Racer::speed() const
{
    return m_speed;
}

double Racer::percent() const
{
    return m_percent;
}

void Racer::setPercent(double value)
{
    m_percent = value;
}

QString Racer::toQString() const
{
    QString result;

    result += name();
    result += ":";
    const auto columns = static_cast<unsigned>(percent() / 10);
    result += QString(columns, '#');

    return result;
}

void Racer::fromVariant(const QVariant &variant)
{
    const auto map = variant.toMap();
    m_name = map.value("name").toString();
    m_speed = map.value("speed").toUInt();
    m_percent = map.value("percent").toDouble();
}
