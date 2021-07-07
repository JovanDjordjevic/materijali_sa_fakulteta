#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include "song.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadAndDisplay();
    void saveChanges();
    void changeSongFields();

private:
    Ui::MainWindow *ui;
    Song m_song;

};
#endif // MAINWINDOW_H
