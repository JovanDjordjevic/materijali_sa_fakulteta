#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>

class Racer;

class Serializer
{
public:
    Serializer();

    void loadFromXML(QVector<Racer> &racers, QString  &filepath);
//dodatno, za vezbu
    void saveToXML(QVector<Racer> &racers, QString  &filepath);

    void loadFromJSON(QVector<Racer> &racers, QString  &filepath);
    void saveToJSON(QVector<Racer> &racers, QString  &filepath);


};

#endif // SERIALIZER_H
