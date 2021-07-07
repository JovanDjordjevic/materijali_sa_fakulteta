#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMutexLocker>

#include "RacerThread.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbRegister, &QPushButton::clicked,
            this, &MainWindow::registerRacers);
    connect(ui->pbStart, &QPushButton::clicked,
            this, &MainWindow::startRace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<Racer> &MainWindow::racers()
{
    return m_racers;
}

QMutex &MainWindow::racersMutex()
{
    return m_mutex;
}

void MainWindow::registerRacers()
{
    QString filename = QFileDialog::getOpenFileName(this, "Odaberite XML datoteku", "~",
                                 "XML files (*.xml)");
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        return;
    }

    m_racers.clear();
    ui->teRaceTrack->setText("");
    ui->groupBox->setEnabled(true);
    ui->leWinner->setText("");

    readFromXML(file);

    drawRaceTrack();

    file.close();
}

void MainWindow::startRace()
{
    ui->pbRegister->setEnabled(false);
    ui->groupBox->setEnabled(false);
    ui->leWinner->setText("");
    m_workingThreads = 0;

    for (auto i = 0; i < m_racers.size(); ++i)
    {
        auto thread = new RacerThread(i, this);
        // signali i slotovi
        connect(thread, &RacerThread::updatedPosition,
                this, &MainWindow::drawRaceTrack);
        connect(thread, &RacerThread::finishedRace,
                this, &MainWindow::onFinishedRace);
        connect(thread, &RacerThread::finished,
                thread, &RacerThread::deleteLater);
        thread->start();
        ++m_workingThreads;
    }
}

void MainWindow::onFinishedRace(int i)
{
    QMutexLocker lock(&m_mutex);

    QString name = m_racers[i].name();
    if (ui->leWinner->text().isEmpty()) {
        ui->leWinner->setText(name);
    }

    --m_workingThreads;

    if (!m_workingThreads) {
        ui->pbRegister->setEnabled(true);
        ui->groupBox->setEnabled(true);
    }
}

void MainWindow::readFromXML(QFile &file)
{
//    Racer r1;
//    r1.setName("Ghost");
//    r1.setSpeed(7);
//    r1.setPercent(0.0);
//    m_racers.push_back(r1);
//    Racer r2{"Blitz", 8, 0.0};
//    m_racers.push_back(r2);

    QXmlStreamReader xmlStream(&file);

    xmlStream.readNextStartElement(); // <racers>

    while (xmlStream.readNextStartElement()) { // <racer>
        Racer r;

        // deserijalizacija
        QVariantMap map;
        // popunjavanje mape...
        while (xmlStream.readNextStartElement()) { // Elementi unutar <racer>
            QString xmlName = xmlStream.name().toString();
            QString xmlValue = xmlStream.readElementText();

            if (xmlName == "name") {
                map.insert(xmlName, xmlValue);
            }
            else if (xmlName == "speed") {
                const auto speed = xmlValue.toUInt();
                map.insert(xmlName, speed);
            }
            else if (xmlName == "percent") {
                const auto percent = xmlValue.toDouble();
                map.insert(xmlName, percent);
            }
        }

        r.fromVariant(map);
        m_racers.push_back(r);
    }
}

void MainWindow::drawRaceTrack()
{
    QMutexLocker lock(&m_mutex);

    QString text;

    for (const auto & racer : m_racers)
    {
        text += racer.toQString() + "\n";
    }

    ui->teRaceTrack->setText(text);
}


















