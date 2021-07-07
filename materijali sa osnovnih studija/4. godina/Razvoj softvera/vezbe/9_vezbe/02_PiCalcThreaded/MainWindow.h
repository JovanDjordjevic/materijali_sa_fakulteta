#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
       void calculatePiValue();
       void onProgressIsMade(QString percentage);
       void onPiIsCalculated(double pi);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H