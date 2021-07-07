#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "vectorthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbUcitaj, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->pbIzadji, &QPushButton::clicked, this, &QApplication::exit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Odaberi fajl", "", "TXT (*.txt)");

    VectorThread *thread = new VectorThread(this, filepath);

    thread->connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->connect(thread, &VectorThread::calculationFinished, this, &MainWindow::displayResult);

    thread->start();
}

void MainWindow::displayResult(double res)
{
    ui->leIntenzitet->setText( QString::number(res) );
}

