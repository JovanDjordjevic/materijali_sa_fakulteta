#include "horse.h"
#include <QVariant>
#include <string>
#include <iostream>

Horse::Horse()
    :m_name(""), m_numberOfRaces(0), m_numberOfVictories(0), m_averageTime(0)
{

}

Horse::Horse(QString name, unsigned int numberOfRaces, unsigned int numberOfVictories, unsigned int m_averageTime)
             :m_name(name), m_numberOfRaces(numberOfRaces), m_numberOfVictories(numberOfVictories), m_averageTime(m_averageTime)
{

}

void Horse::load(QVariant data)
{
    QVariantMap vmap = data.toMap();
    m_name = vmap.value("name").toString();
    m_numberOfRaces = vmap.value("numberOfRaces").toUInt();
    m_numberOfVictories = vmap.value("numberOfVictories").toUInt();
    m_averageTime = vmap.value("averageTime").toUInt();
}

QVariant Horse::save() const
{
    QVariantMap vmap;

    vmap.insert("name", m_name);
    vmap.insert("numberOfRaces", m_numberOfRaces);
    vmap.insert("numberOfVictories", m_numberOfVictories);
    vmap.insert("averageTime", m_averageTime);

    return vmap;
}

void Horse::toString() const
{
    std::cout << "Name: " << m_name.toStdString() << "\n"
              << "NumberOfRaces: " << m_numberOfRaces << "\n"
              << "numberOfVictories : " << m_numberOfVictories << "\n"
              << "averageTime: " << m_averageTime << "\n\n";
}
