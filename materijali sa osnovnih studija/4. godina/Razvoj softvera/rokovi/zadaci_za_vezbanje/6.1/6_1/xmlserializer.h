#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QObject>

class Song;

class QXmlStreamWriter;
class QXmlStreamReader;

class XMLSerializer
{
public:
    XMLSerializer();

    void saveToFile(const Song &song, const QString &filename, const QString &rootName);
    void loadFromFile(Song &song, const QString &filename);

    void writeVariantToStream(const QString &nodeName, const QVariant &variant, QXmlStreamWriter &stream);
    QVariant readVariantFromStream(QXmlStreamReader &stream);

};

#endif // XMLSERIALIZER_H
