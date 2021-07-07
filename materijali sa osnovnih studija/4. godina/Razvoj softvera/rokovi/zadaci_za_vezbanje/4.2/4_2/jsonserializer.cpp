#include "jsonserializer.h"
#include <QJsonDocument>
#include <QJsonArray>
#include "horse.h"
#include <QFile>

JSONSerializer::JSONSerializer()
{

}

void saveToJson(QVector<Horse> &horses, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QVariantList vlist;
    for(auto &h : horses)
    {
        QVariant v = h.save();
        vlist.append(v);
    }

    file.write(QJsonDocument::fromVariant(vlist).toJson());

    file.close();
}

void JSONSerializer::loadFromFile(QVector<Horse> &horses, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    QVariant v = doc.toVariant();

    QVariantList vlist = v.toList();
    for(auto& elem : vlist)
    {
        Horse h;
        h.load(elem);
        h.toString();
        horses.append(h);
    }

    file.close();
}

void JSONSerializer::temp(QVector<Horse> &horses, QString &filepath)
{
    QVector<Horse> newHorses{ {"SuperHorsey", 10, 5, 1000}, {"LucyInTheSky", 20, 2, 4500},
                              {"SuperMoose", 10, 9, 1500}, {"TimTheEnchanter", 50, 40, 2000} };

    QString dest = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/4.2/4_2/horsesNew.json";

    QFile file(dest);
    file.open(QFile::WriteOnly);

    QVariantList vlist;
    for(auto &h : newHorses)
    {
        QVariant v = h.save();
        vlist.append(v);
    }

    file.write(QJsonDocument::fromVariant(vlist).toJson());

    file.close();
}
