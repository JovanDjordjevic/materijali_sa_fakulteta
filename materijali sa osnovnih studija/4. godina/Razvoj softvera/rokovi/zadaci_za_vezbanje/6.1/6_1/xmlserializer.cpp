#include "xmlserializer.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVariant>
#include "song.h"

#include <QFile>

XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::saveToFile(const Song &song, const QString &filename, const QString &rootName)
{
    QFile file(filename);
    file.open(QFile::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);

    stream.writeStartDocument();

    QVariant v = song.save();
    writeVariantToStream(rootName, v, stream);

    stream.writeEndDocument();

    file.close();
}

void XMLSerializer::loadFromFile(Song &song, const QString &filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);

    QXmlStreamReader stream(&file);

    stream.readNextStartElement();

    QVariant v = readVariantFromStream(stream);
    song.load(v);

    file.close();
}

void XMLSerializer::writeVariantToStream(const QString &nodeName, const QVariant &variant, QXmlStreamWriter &stream)
{
    stream.writeStartElement(nodeName);
    stream.writeAttribute("type", variant.typeName());

    switch(variant.type())
    {
        case QVariant::Type::List:
            {
                QVariantList vlist = variant.toList();
                for(const auto &elem : vlist)
                {
                    if(nodeName == "genres"){ writeVariantToStream("genre", elem, stream);  }
                    else writeVariantToStream("feature", elem, stream);
                }
            }
            break;
        case QVariant::Type::Map:
            {
                QVariantMap vmap = variant.toMap();
                QMapIterator<QString, QVariant> it(vmap);
                while(it.hasNext()){
                    it.next();
                    writeVariantToStream(it.key(), it.value(), stream);
                }
            }
            break;
        default:
            stream.writeCharacters(variant.toString());
            break;
    }

    stream.writeEndElement();
}

QVariant XMLSerializer::readVariantFromStream(QXmlStreamReader &stream)
{
    QVariant v;
    QXmlStreamAttributes attrs = stream.attributes();
    QString typeName = attrs.value("type").toString();
    const auto type = QVariant::nameToType(typeName.toStdString().c_str());

    switch(type)
    {
        case QVariant::Type::List:
            {
                QVariantList vlist;
                while(stream.readNextStartElement())
                {
                    QVariant vtemp = readVariantFromStream(stream);
                    vlist.append(vtemp);
                }
            }
            break;
        case QVariant::Type::Map:
            {
                QVariantMap vmap;
                while(stream.readNextStartElement())
                {
                    QVariant vtemp = readVariantFromStream(stream);
                    QString name = stream.name().toString();
                    vmap.insert(name, vtemp);
                }
            }
            break;
        default:
            QString dataText = stream.readElementText();
            v = dataText;
            v.convert(type);
            break;
    }

    return v;
}
