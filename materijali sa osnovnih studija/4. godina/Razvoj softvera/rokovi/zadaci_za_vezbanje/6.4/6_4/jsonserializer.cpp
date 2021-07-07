#include "jsonserializer.h"

#include <QFile>
#include <QJsonDocument>
#include <QDebug>

JSONSerializer::JSONSerializer()
{
}

void JSONSerializer::load(Map &map, QString &filepath)
{
    QFile file{filepath};
    file.open(QFile::ReadOnly);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    QVariant v = doc.toVariant();

    map.fromVariant(v);

    file.close();
}
