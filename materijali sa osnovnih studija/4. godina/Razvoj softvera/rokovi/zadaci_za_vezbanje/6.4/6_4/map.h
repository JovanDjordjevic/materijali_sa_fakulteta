#ifndef MAP_H
#define MAP_H

#include <QObject>

class Map
{

public:
    Map();
    Map(QVector<QVector<int>> &map, QVector<QPair<int, int>> &sources, int rows, int columns);

    void fromVariant(const QVariant &variant);

    void toString();

//private:
public:
    QVector<QVector<int>> m_map;
    QVector<QPair<int, int>> m_sources;
    int m_rows;
    int m_columns;
};

#endif // MAP_H
