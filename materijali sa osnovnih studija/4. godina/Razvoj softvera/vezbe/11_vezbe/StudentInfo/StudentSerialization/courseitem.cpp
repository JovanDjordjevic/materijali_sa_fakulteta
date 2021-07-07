#include "courseitem.h"

CourseItem::CourseItem()
    : m_name(""), m_espb(0u)
{
}

QVariant CourseItem::toVariant() const
{
    //QVariantMap je samo typedef za QMap<QString, QVariant>
    QVariantMap map;

    map.insert("name", m_name);
    map.insert("espb", m_espb);

    //primetimo da iako je nas objekat QVariantMap, mozemo da ga vratimo iako u potpisu funkcije stoji QVariant
    //zato sto se implicitno konvertuje (?)
    return map;
}

//toVariant i fromVariant moraju biti implementirane kao inverzne operacije. tj hocemo da
// fromVariant( toVariant(a) )  <=>  a
//mi smo toVariant napisali tako da vraca QVariantMap, tj ocekujemo da QVariant argument
//u fromVariant funckciji bude bas QVariantMap
void CourseItem::fromVariant(const QVariant &variant)
{
    //znaci mi ovde znamo da je variant bas mapa tako da mozemo da ga procitamo kao mapu
    QVariantMap map = variant.toMap();
    //mapa nam cuva parove oblika <QString, QVariant>, tj value("name") je QVariant tako da mora da se konvertuje u stirng
    m_name = map.value("name").toString();

    m_espb = map.value("espb").toUInt();
}
