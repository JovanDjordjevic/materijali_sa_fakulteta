#include "binaryserializer.h"

#include <QDataStream>  //ovde su nam stvari potrebne za binarne podatke
#include <QFile>

//sve slicno kao za json serializer

BinarySerializer::BinarySerializer()
{

}

void BinarySerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    Q_UNUSED(rootName);

    //za binarnu serijalizaciju korsitimo QDataStream. Ideja je da napravimo taj stream ka nekom vec postojecem IO resursu
    //to moze biti fajl, soket itd itd.

    QFile file(filepath);
    file.open(QFile::WriteOnly);

    QDataStream data(&file);

    QVariant v = serializable.toVariant();

    //da bismo sad bianrno upisali te podatke na tok, dovoljno je da samo koristimo  operatore za tokove.
    //oni su vec definisani za QVariant, a tok je vec binaran tako da ne treba nista drugo da radimo
    data << v;

    file.close();
}

void BinarySerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QDataStream data(&file);

    QVariant v;
    //sa ovog toka mozemo i da citamo
    data >> v;

    serializable.fromVariant(v);

    file.close();
}
