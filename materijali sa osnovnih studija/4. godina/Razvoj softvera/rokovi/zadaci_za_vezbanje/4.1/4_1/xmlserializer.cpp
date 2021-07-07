#include "xmlserializer.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVariant>
#include "song.h"

#include <QFile>

XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::saveToFile(Song &s, QString &filepath)
{
    QVariantMap vmap = s.save().toMap();
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    stream.writeStartElement("Song");
    stream.writeAttribute("type", "QVariantMap");

    stream.writeStartElement("Artist");
    stream.writeAttribute("type", "QString");
    stream.writeCharacters( vmap.value("Artist").toString() );
    stream.writeEndElement();

    stream.writeStartElement("Title");
    stream.writeAttribute("type", "QString");
    stream.writeCharacters( vmap.value("Title").toString() );
    stream.writeEndElement();

    stream.writeStartElement("Album");
    stream.writeAttribute("type", "QString");
    stream.writeCharacters( vmap.value("Album").toString() );
    stream.writeEndElement();

    stream.writeStartElement("Features");
    stream.writeAttribute("type", "QVariantList");
        QVariantList featureList = vmap.value("Features").toList();
        for(const auto& f : featureList)
        {
            stream.writeStartElement("Feature");
            stream.writeAttribute("type", "QString");
            stream.writeCharacters( f.toString() );
            stream.writeEndElement();
        }
    stream.writeEndElement();

    stream.writeStartElement("Rating");
    stream.writeAttribute("type", "double");
    stream.writeCharacters( vmap.value("Rating").toString() );
    stream.writeEndElement();

    stream.writeStartElement("Genres");
    stream.writeAttribute("type", "QVariantList");
        QVariantList genreList = vmap.value("Genres").toList();
        for(const auto& g : genreList)
        {
            stream.writeStartElement("Genre");
            stream.writeAttribute("type", "QString");
            stream.writeCharacters( g.toString() );
            stream.writeEndElement();
        }
    stream.writeEndElement();

    stream.writeStartElement("Year");
    stream.writeAttribute("type", "uint");
    stream.writeCharacters( vmap.value("Year").toString() );
    stream.writeEndElement();

    stream.writeEndDocument();
}

void XMLSerializer::loadFromFile(Song &s, QString &filepath)
{
    QVariantMap vmap;

    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QXmlStreamReader stream(&file);

    stream.readNextStartElement(); // song

    stream.readNextStartElement(); //artist
    vmap.insert("Artist", stream.readElementText());

    stream.readNextStartElement(); //title
    vmap.insert("Title", stream.readElementText());

    stream.readNextStartElement(); //Album
    vmap.insert("Album", stream.readElementText());

    stream.readNextStartElement(); //Features
    QVariantList featureList;
    while(stream.readNextStartElement())    //Feature
        featureList.append(stream.readElementText());
    vmap.insert("Features", featureList);

    stream.readNextStartElement(); //Rating
    vmap.insert("Rating", stream.readElementText());

    stream.readNextStartElement(); //Genres
    QVariantList genreList;
    while(stream.readNextStartElement()) //Genre
        genreList.append(stream.readElementText());
    vmap.insert("Genres", genreList);

    stream.readNextStartElement(); //Year
    vmap.insert("Year", stream.readElementText());


    s.load(vmap);
}


