#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QObject>
class Horse;

class JSONSerializer
{
public:
    JSONSerializer();

    void saveToJson(QVector<Horse> &horses, QString &filepath);
    void loadFromFile(QVector<Horse> &horses, QString &filepath);

    void temp(QVector<Horse> &horses, QString &filepath);

};

#endif // JSONSERIALIZER_H
