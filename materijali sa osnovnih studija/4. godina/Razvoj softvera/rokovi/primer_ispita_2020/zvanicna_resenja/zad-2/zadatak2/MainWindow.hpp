#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QFile>
#include <QMutex>

#include "Racer.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<Racer> &racers();
    QMutex &racersMutex();

private slots:
    void registerRacers();
    void startRace();
    void onFinishedRace(int i);

    void readFromXML(QFile &file);
    void drawRaceTrack();

private:
    Ui::MainWindow *ui;

    QVector<Racer> m_racers;
    QMutex m_mutex;

    int m_workingThreads;
};
#endif // MAINWINDOW_HPP
