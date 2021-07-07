#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "racer.h"
#include "serializer.h"
#include "racerthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbRegistruj, &QPushButton::clicked, this, &MainWindow::registerParticipants);
    connect(ui->pbZapocni, &QPushButton::clicked, this, &MainWindow::startThreads);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registerParticipants()
{
    ui->leRezultat->clear();
    ui->teUcesnici->clear();

    QString filepath = QFileDialog::getOpenFileName(this, "Odaberi datoteku", "", "Files (*.json *.xml)");

    if(filepath == nullptr)
    {
        QMessageBox msg;
        msg.setText("Odaberi validnu datoteku");
        msg.exec();
        return;
    }

    m_racers.clear();

    Serializer serializer;

    serializer.loadFromXML(m_racers, filepath);
    //serializer.loadFromJSON(m_racers, filepath);

    //QString path = "C:/Users/Jovan/Desktop/RS/rokovi/primer_ispita_2020/2 - Copy/racersNew.xml";
    //QString path = "C:/Users/Jovan/Desktop/RS/rokovi/primer_ispita_2020/2 - Copy/racers.json";
    //serializer.saveToXML(m_racers, path);
    //serializer.saveToJSON(m_racers, path);

    updateTextField();
}

void MainWindow::updateTextField()
{
    QMutexLocker lock(&m_mutex);

    ui->teUcesnici->clear();
    QString text = "";
    for(auto &r : m_racers)
    {
        text += r.toQString() + '\n';
    }

    ui->teUcesnici->setText(text);
}

void MainWindow::startThreads()
{
    m_startedThreads = 0;
    m_winnerFound = false;

    ui->pbRegistruj->setEnabled(false);
    ui->pbZapocni->setEnabled(false);
    ui->teUcesnici->setEnabled(false);
    ui->lbTrka->setEnabled(false);
    ui->lbRezultat->setEnabled(false);
    ui->leRezultat->setEnabled(false);

    QMutexLocker lock(&m_mutex);

    for(int i = 0; i < m_racers.size(); i++)
    {
        RacerThread* thread = new RacerThread(this, i);

        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(thread, &RacerThread::progressMade, this, &MainWindow::updateTextField);
        connect(thread, &RacerThread::racerFinished, this, &MainWindow::onRacerFinished);

        thread->start();
        m_startedThreads++;
    }
}

void MainWindow::onRacerFinished(int index)
{
    QMutexLocker lock(&m_mutex);

    if(!m_winnerFound)
    {
        m_winnerFound = true;
        ui->leRezultat->setText(m_racers[index].m_name);
    }

    m_startedThreads--;
    if(m_startedThreads == 0){
        ui->pbRegistruj->setEnabled(true);
        ui->pbZapocni->setEnabled(true);
        ui->teUcesnici->setEnabled(true);
        ui->lbTrka->setEnabled(true);
        ui->lbRezultat->setEnabled(true);
        ui->leRezultat->setEnabled(true);

    }
}

