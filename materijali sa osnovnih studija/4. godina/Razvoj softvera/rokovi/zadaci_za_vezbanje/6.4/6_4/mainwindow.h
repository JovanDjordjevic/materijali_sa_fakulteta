#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map.h"
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeTableWidgetMap();
    void drawTableWidgetMap();
    QMutex& getMutex() { return m_mutex; }
    Map& getMap() { return m_map; }

public slots:
    void loadMap();
    void emitSignals();

private:
    Ui::MainWindow *ui;
    Map m_map;
    QMutex m_mutex;
};
#endif // MAINWINDOW_H
