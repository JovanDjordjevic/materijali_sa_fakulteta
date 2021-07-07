#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include "workerthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbGenerate, &QPushButton::clicked, this, &MainWindow::generateNumbers);
    connect(ui->pbBeginCalculation, &QPushButton::clicked, this, &MainWindow::startThreads);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateNumbers()
{
    m_numbers.clear();
    m_capacity = 0;
    m_sum = 0;
    m_overflow = 0;
    m_maxCapacity = 0;

    bool success;
    int number = ui->leEnterNumber->text().toInt(&success);
    if(!success)
    {
        QMessageBox msg;
        msg.setText("You must enter a valid integer");
        msg.exec();
        ui->leEnterNumber->setText("");
        return;
    }

    QRandomGenerator rGen;
    for(int i = 0; i < number; i++)
    {
        int rand = rGen.global()->bounded(200, 1500);
        m_numbers.push_back(rand);
        m_capacity += rand;
    }

    updateRandomNumberList();

    ui->leCapacity->setText(QString::number(m_capacity));
}

void MainWindow::updateRandomNumberList()
{
    ui->wlRandomNumbers->clear();
    for(const auto& n : m_numbers)
    {
        ui->wlRandomNumbers->addItem( QString::number(n) );
    }
}

void MainWindow::startThreads()
{
    bool success;
    m_maxCapacity = ui->leMaxCapacity->text().toInt(&success);
    if(!success || (success && (m_maxCapacity > m_capacity) ))
    {
        QMessageBox msg;
        msg.setText("Number must be <= than capacity");
        msg.exec();
        ui->leMaxCapacity->setText("");
        return;
    }

    for(int i = 0; i<m_numbers.size(); i++)
    {
        WorkerThread *thread = new WorkerThread(this, i);

        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(thread, &WorkerThread::progressMade, this, &MainWindow::update);

        thread->start();
    }
}

void MainWindow::update(int n)
{
    //...
    if( (m_sum + n) <= m_maxCapacity)
    {
        m_sum += n;
    }
    else
    {
        m_overflow += n;
    }
    ui->leSum->setText( QString::number(m_sum) );
    ui->leOverflow->setText( QString::number(m_overflow) );

    updateRandomNumberList();
}

