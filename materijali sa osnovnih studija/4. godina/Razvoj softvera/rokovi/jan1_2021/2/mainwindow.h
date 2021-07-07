#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    QVector<int>& getNumbers() { return m_numbers; }
    QMutex& getMutex() {return m_mutex; }

public slots:
    void generateNumbers();
    void updateRandomNumberList();
    void startThreads();
    void update(int n);

private:
    Ui::MainWindow *ui;
    QVector<int> m_numbers;
    QMutex m_mutex;
    int m_capacity;
    int m_maxCapacity;
    int m_sum;
    int m_overflow;
};
#endif // MAINWINDOW_H
