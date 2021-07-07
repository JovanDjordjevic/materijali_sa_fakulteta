#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMutex> //za sinhronizaciju niti

class Room;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Room &getRoom();
    //mutex nam je ptoreban i u mainwindow.cpp i u cellthread.cpp pa nam treba geter,
    //ALI obavezno po referenci, a ne kao kopiju, jer bi onda mutex bio nezavisan od niti, tj svaka nit bi zakljucavala neki svoj mutex
    //a to nema smisla
    QMutex &getRoomMutex();

public slots:
    void onPbStartReading();
    void startThreads();
    void onThreadFinished(int i, int j);

private:
    void populateTableWidget();

private:
    Ui::MainWindow *ui;
    Room *_room;
    //ideja mutexa je da za svaki resurs koji se koristi u nitima mozemo da zakljucamo i otkljucamo,
    //takodje, potrebno je da za svaki resurs definisemo zaseban mutex, a ne da imamo jedan mutex za sve
    QMutex _roomMutex;
    QTimer _timer;
};
#endif // MAINWINDOW_H
