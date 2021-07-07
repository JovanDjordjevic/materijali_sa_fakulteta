#include "xmlserializer.h"

#include <QXmlStreamReader> //ove dve klase su nam za xml
#include <QXmlStreamWriter>
#include <QFile>

//sa XML-om ce biti malo komplikovanije. Mi ovde pisemo najopstiji moguci serijalizator
//na ispitu ako nam dodje xml, ne moramo ovako vec mozemo da koristimo cinjenicu da znamo kakvu klasu cemo da
//deserijalizujemo, npr ako znamo da ce biti student, znamo unapred kog oblika je course item, ako je student
//znamo da je enrolled neki bool itd itd
//ovde pisemo uopsteno kao primer

XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootName)
{
    QFile file(filepath);
    file.open(QFile::WriteOnly);

    //slicno kao za bianry, pravimo tok u koji cemo upisivati
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true); //mozemo da ukljucimo da ima lepsi zapis

    //xml daoteke moraju da pocnu onim zaglavljem, a za to imamo vec ugradjen metod
    stream.writeStartDocument();

    QVariant v = serializable.toVariant();
    writeVariantToStream(rootName, v, stream);

    //isto i za kraj xml datoteke
    stream.writeEndDocument();
    file.close();
}


void XMLSerializer::load(Serializable &serializable, const QString &filepath)
{
    QFile file(filepath);
    file.open(QFile::ReadOnly);

    QXmlStreamReader stream(&file);

    //ovaj metod nas pozicionira na prvu etiketu za citanje(u nasem slucaju bice <student> etiketa (ili ona <xml>?) )
    stream.readNextStartElement();

    QVariant v = readVariantFromStream(stream);

    serializable.fromVariant(v);

    file.close();
}


void XMLSerializer::writeVariantToStream(const QString &nodeName, const QVariant &variant, QXmlStreamWriter &stream)
{
    //kada ispisujemo neki element, moramo prvo da napisemo otvorenu etiketu (npr <student>)
    stream.writeStartElement(nodeName);
    //dodajemo atribute koje zelimo, mi hocemo da imamo zapis tipa type="QString" i slicno
    //variant ima metod typeName() koji vraca string reprezentaciju tipa koji cuva (ovako vidimo koji tip variant cuva u sebi generalno)
    stream.writeAttribute("type", variant.typeName());

    //mozemo za variant dobiti i enum koji na daje informacije koji je tip u njemu
    //posto znamo da imamo i trivijalne tipove i mape i liste, treba posebno obraditi upisivanje za sva 3
    switch (variant.type() ){
        case QVariant::Type::List: {
            //NOTE: QT se zalio ovde ako ne stavimo ovaj kod u {}
                QVariantList list = variant.toList();
                for(const auto & v : list){
                //znamo da se u listi cuvaju courseItemi, tako da je dogovor da nam se etiketa za njih zove <item>, da nebi komplikovali
                    writeVariantToStream("item", v, stream);
                }
            }
            break;
        case QVariant::Type::Map: {
                QVariantMap map = variant.toMap();
                //mozemo koristiti ugradjenu klasu za iteraciju kroz mapu
                QMapIterator<QString, QVariant> iter(map);
                while( iter.hasNext() ){
                    iter.next();
                    writeVariantToStream(iter.key(), iter.value(), stream);
                }
            }
            break;
        default:
            //sve trivijalne tipove mozemo obraditi na isti nacin zato sto oni mogu direktno da se konvertuju u QString
            stream.writeCharacters( variant.toString() );
            break;
    }

    //zatvaramo poslednju otvorenu etiketu (npr </student>)
    stream.writeEndElement();
}


QVariant XMLSerializer::readVariantFromStream(QXmlStreamReader &stream)
{
    //dohvatamo atribute za tekucu otvorenu etiketu
    QXmlStreamAttributes attrs = stream.attributes();
    QString typeString = attrs.value("type").toString();
    QVariant v;

    //hocemo da na osnovu atributa "type" odredimo kako popunjavamo nas variant.
    //sa nameToType dobijamo konkretnu vrednost iz enuma, samo sto ova funkcija prihvata bas cosnt char*
    //a za to ne postoji direktna konverzija iz QString, ali mzoemo prvo konvertovati u StdString(), a onda odatle
    //sa c_str() u const char *
    auto variantType = QVariant::nameToType(typeString.toStdString().c_str());

    switch (variantType){
        case QVariant::Type::List:{
                QVariantList list;
                while(stream.readNextStartElement()){
                    QVariant vtemp = readVariantFromStream(stream);
                    list.append(vtemp);
                }
            }
            break;
        case QVariant::Type::Map: {
                QVariantMap map;
                while(stream.readNextStartElement()){
                    //sa stream.name() dobijamo ime tekuce otvorene etikete
                    QString name = stream.name().toString();
                    QVariant vtemp = readVariantFromStream(stream);
                    map.insert(name, vtemp);
                }
            }
            break;
            default:{
                //za trivijalne tipove moramo ih razlicito parsirati u odnosu na to kog tipa treba da budu
                //za pocetak, procitamo kao text ono ono sto je u telu tekuce etikete
                QString dataString = stream.readElementText();
                v = dataString;
                //i obavezno ga moramo konvertovati u odgovarajuci tip, da se nebi uvek vracao kao string
                v.convert(variantType);
            }
            break;
    }

    return v;
}
