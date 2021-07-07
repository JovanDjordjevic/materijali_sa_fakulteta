#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>

class Racer;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<Racer>& getRacers() { return m_racers; }
    QMutex& getMutex() { return m_mutex; }


public slots:
    void registerParticipants();
    void updateTextField();
    void startThreads();
    void onRacerFinished(int index);

private:
    Ui::MainWindow *ui;
    QVector<Racer> m_racers;
    QMutex m_mutex;
    int m_startedThreads;
    bool m_winnerFound;
};
#endif // MAINWINDOW_H
