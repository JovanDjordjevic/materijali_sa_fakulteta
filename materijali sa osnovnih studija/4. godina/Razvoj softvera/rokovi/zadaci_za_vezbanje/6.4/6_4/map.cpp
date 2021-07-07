#include "map.h"
#include <QVariant>
#include <QDebug>

Map::Map()
{
}

Map::Map(QVector<QVector<int>> &map, QVector<QPair<int, int>> &sources, int rows, int columns)
    : m_map(map), m_sources(sources), m_rows(rows), m_columns(columns)
{
}

void Map::fromVariant(const QVariant &variant)
{
    m_map.clear();
    m_sources.clear();

    QVariantMap vmap = variant.toMap();

    m_rows = vmap.value("n").toInt();
    m_columns = vmap.value("m").toInt();

    m_map.resize(m_rows);
    for(auto &row : m_map)
    {
        row.resize(m_columns);
        row.fill(0);
    }


    QVariantList vlist = vmap.value("sources").toList();
    for(auto &elem : vlist)
    {
        QVariantMap vm = elem.toMap();
        int i = vm.value("i").toInt();
        int j = vm.value("j").toInt();
        int sourcePower = vm.value("sourcePower").toInt();
        m_sources.push_back(QPair<int, int>{i, j});
        m_map[i][j] = sourcePower;
    }
}

void Map::toString()
{
    qDebug() << "Rows:" << m_rows << " Columns: " << m_columns;
    for(int i = 0; i < m_rows; i++)
    {
        QString matrix = "";
        for(int j = 0; j < m_columns; j++)
        {
            matrix += QString::number(m_map[i][j]);
            matrix += " ";
        }
        qDebug() << matrix;
    }

}
