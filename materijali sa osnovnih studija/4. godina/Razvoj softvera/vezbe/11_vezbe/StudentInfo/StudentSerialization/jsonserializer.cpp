#include "jsonserializer.h"
#include <QJsonDocument>
#include <QFile>

JSONSerializer::JSONSerializer()
{

}

void JSONSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    Q_UNUSED(rootName); //samo makro neki da nam se okruzenje nebi zalilo sto je rootName unused (a znamod a nam za json nece trebati)

    //da bismo neki objekat serijalizovali u json, moramo prvo da ga pretvorimo u variant,a  onda odatle u json
    //(tj tako smo osmislili da radi, zeleli smo nekako da iskoristimo qt klase za json, i ostale tipove, zato sto imamo
    //ugradjene metode koje citaju json iz nekog varianta)
    QVariant v = serializable.toVariant();

    //dobijamo json objekat iz varianta
    QJsonDocument doc = QJsonDocument::fromVariant(v);

    QFile file(filepath);
    file.open(QFile::WriteOnly);

    //i od tog json objekat sad rpavimo tekst koji upisujemo u fajl
    //mozemo da prosledimo i enum koji koaze kako ce biti zapisano, Compact ili Indented
    file.write( doc.toJson( QJsonDocument::JsonFormat::Indented ) );
    file.close();
}

void JSONSerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    //iamo funkc koja iz nekog byteArray-a cita json, a mi ga imamo u tekstualnom fajlu. Ako za taj fajl pozovemo
    //readAll() metod, to bas vraca byte array pa nam je zgodno
    QJsonDocument doc = QJsonDocument::fromJson( file.readAll() );

    //pravimo variant od naseg jsona
    QVariant v = doc.toVariant();

    //i onda iz tog varianta izvlacimo podatke koji se upisuju u nas serializable objekat
    serializable.fromVariant(v);

    file.close();
}
