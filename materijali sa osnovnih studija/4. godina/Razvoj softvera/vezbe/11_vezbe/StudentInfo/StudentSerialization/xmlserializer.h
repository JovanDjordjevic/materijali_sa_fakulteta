#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include "Serializer.h"

class QXmlStreamWriter;
class QXmlStreamReader;

class STUDENTSERIALIZATION_EXPORT XMLSerializer : public Serializer
{
public:
    XMLSerializer();

    // Serializer interface
public:
    void save(const Serializable &serializable, const QString &filepath, const QString &rootName) override;
    void load(Serializable &serializable, const QString &filepath) override;


//dadacemo neke pomocne metode jer je rad sa xmlom malo komplikovaniji
private:
    void writeVariantToStream(const QString &nodeName,
                              const QVariant &variant,
                              QXmlStreamWriter &stream);
    QVariant readVariantFromStream(QXmlStreamReader &stream);

};
#endif // XMLSERIALIZER_H
