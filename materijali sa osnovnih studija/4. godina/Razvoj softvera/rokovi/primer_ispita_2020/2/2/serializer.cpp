#include "serializer.h"

#include "racer.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QVariant>
#include <QDebug>
#include <QJsonDocument>

Serializer::Serializer()
{

}

void Serializer::loadFromXML(QVector<Racer> &racers, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QXmlStreamReader stream(&file);

    stream.readNextStartElement(); //racers
    while(stream.readNextStartElement())    //racer
    {
        Racer r;
        QVariantMap vmap;

        while(stream.readNextStartElement()) //elementi u svakom raceru
        {
            QString tagName = stream.name().toString();
            QString tagValue = stream.readElementText();

            if(tagName == "name")         vmap.insert("name", tagValue);
            else if(tagName == "speed")   vmap.insert("speed", tagValue.toUInt());
            else if(tagName == "percent") vmap.insert("percent", tagValue.toDouble());
        }

        r.fromVariant(vmap);
        racers.push_back(r);
    }

    file.close();
}

//metodi ispod su za vezbu, nisu deo zadatka
void Serializer::saveToXML(QVector<Racer> &racers, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    stream.writeStartElement("racers");
    stream.writeAttribute("type", "QVariantList");

    for(auto &racer : racers)
    {
        stream.writeStartElement("racer");
        stream.writeAttribute("type", "QVariantMap");

            stream.writeStartElement("name");
            stream.writeAttribute("type", "QString");
            stream.writeCharacters(racer.m_name);
            stream.writeEndElement();

            stream.writeStartElement("speed");
            stream.writeAttribute("type", "uint");
            stream.writeCharacters( QString::number(racer.m_speed) );
            stream.writeEndElement();

            stream.writeStartElement("percent");
            stream.writeAttribute("type", "double");
            stream.writeCharacters( QString::number(racer.m_percentage) );
            stream.writeEndElement();

        stream.writeEndElement();
    }

    stream.writeEndDocument();

    file.close();
}


void Serializer::loadFromJSON(QVector<Racer> &racers, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QJsonDocument doc = QJsonDocument::fromJson( file.readAll() );
    QVariantList vlist = doc.toVariant().toList();

    for(auto &v : vlist){
        Racer r;
        r.fromVariant(v);
        racers.append(r);
    }

    file.close();
}


void Serializer::saveToJSON(QVector<Racer> &racers, QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QVariantList vlist;

    for(auto &racer : racers)
    {
        QVariant vmap = racer.toVariant();
        vlist.append(vmap);
    }

    QJsonDocument doc = QJsonDocument::fromVariant( vlist );

    file.write(doc.toJson(QJsonDocument::Indented));

    file.close();

}
