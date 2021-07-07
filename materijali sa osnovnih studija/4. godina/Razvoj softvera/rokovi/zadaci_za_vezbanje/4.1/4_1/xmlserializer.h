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

    void saveToFile(Song &s, QString &filepath);
    void loadFromFile(Song &s, QString &filepath);

};

#endif // XMLSERIALIZER_H
