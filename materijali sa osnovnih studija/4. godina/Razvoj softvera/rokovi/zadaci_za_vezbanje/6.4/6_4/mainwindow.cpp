#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include "jsonserializer.h"
#include "itemthread.h"
#include <QMutexLocker>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbLoadMap, &QPushButton::clicked, this, &MainWindow::loadMap);
    connect(ui->pbEmitSignals, &QPushButton::clicked, this, &MainWindow::emitSignals);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTableWidgetMap()
{
    int rows = m_map.m_rows;
    int columns = m_map.m_columns;

    ui->twMap->setRowCount(rows);
    ui->twMap->setColumnCount(columns);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem();
            if(m_map.m_map[i][j] != 0)
            {
                QFont f;
                f.setBold(true);
                item->setFont(f);
            }
            ui->twMap->setItem(i, j, item);
        }
    }
}

void MainWindow::drawTableWidgetMap()
{
    int rows = m_map.m_rows;
    int columns = m_map.m_columns;

    QMutexLocker locker(&m_mutex);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QString itemText = "";
            if(m_map.m_map[i][j] != 0)
            {
                itemText = QString::number(m_map.m_map[i][j]);
            }
            ui->twMap->item(i, j)->setText( itemText );
        }
    }

}

void MainWindow::loadMap()
{
    ui->twMap->clear();

    QString filename = QFileDialog::getOpenFileName(this, "Odaberi fajl", "", "JSON *.json");
    //qDebug() << filename;
    JSONSerializer jsonser;
    jsonser.load(m_map, filename);

    //m_map.toString();
    initializeTableWidgetMap();
    drawTableWidgetMap();
}

void MainWindow::emitSignals()
{
    QMutexLocker locker(&m_mutex);

    for(auto &source : m_map.m_sources)
    {
        ItemThread* thread = new ItemThread(this, source.first, source.second
                                            , m_map.m_map[source.first][source.second]);

        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(thread, &ItemThread::progressMade, this, &MainWindow::drawTableWidgetMap);

        thread->start();
    }
}

