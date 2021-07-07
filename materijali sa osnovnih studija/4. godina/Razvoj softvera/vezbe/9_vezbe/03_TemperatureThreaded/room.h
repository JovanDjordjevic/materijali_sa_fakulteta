#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QVector>

class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(int n, QObject *parent = nullptr);

    //na ispitu ce nam verovatno biti zabranjeno da radimo kopiranje velikih objekata, pa cemo morati da pravimo konstruktor kopije
    //i da ga obrisemo, i operator dodele sa semantikom koppiranja
    Room(const Room &) = delete;
    Room &operator=(const Room &) = delete;
    //isto i za konstruktor pomeranja i operatorom dodele sa semnatikom pomeranja
    Room(const Room &&) = delete;
    Room &operator=(const Room &&) = delete;

    int numberOfRowsAndColumns() const;
    double cellValue(int i, int j) const;

    double getTemperatureDiffFromCellAbove(int i, int j) const;
    double getTemperatureDiffFromCellBelow(int i, int j) const;
    double getTemperatureDiffFromCellLeft(int i, int j) const;
    double getTemperatureDiffFromCellRight(int i, int j) const;

    void updateNewTemperatureForCell(int i, int j, double tempDiff);

private:
    const double TEMP_COEFFICIENT = 0.1;
    QVector<QVector<double>> _matrix;

signals:


};

#endif // ROOM_H
