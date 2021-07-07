#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "pithread.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //opet radimo conenct smao sto ovaj put koristimo petu argument
    //za ovaj koristimo DirectConenction jer i UI i main window zive u istoj petlji niti (mogli smo i bez jer bi AutoConnect sam zakljucio ovo za nas)
    connect(ui->pbStartCalculating, &QPushButton::clicked, this, &MainWindow::calculatePiValue, Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculatePiValue()
{
    //pripremimo UI, hocemo da koirsnik samo jednom mzoe da klikne dugme, i da se na pocetku ocisti list widget
    ui->pbStartCalculating->setEnabled(false);
    ui->lwProgress->clear();

    //kreiramo nit. OBZAVEZNO Instanciramo je na heap-u (sa *x =  new x()) a ne na steku, da nit nebi zavisila od stek okvira funkcije u kojoj se instancira)
    PiThread *thread = new PiThread(this);

    connect(thread, &PiThread::progressIsMade, this, &MainWindow::onProgressIsMade);
    connect(thread, &PiThread::piIsCalculated, this, &MainWindow::onPiIsCalculated);

    //kada se nit zavrsi treba da je obrisemo iz memorije, tos e isto radi ugradjenim signalima i slotovima(koje ima svaka klasa koja nasledjuje QThread)
    connect(thread, &PiThread::finished, thread, &PiThread::deleteLater);

    //zapocinejmo nit, u pozadini, ovo prvo salje signal ( zove se started() (?)), zatim on poziva nas run() metod i na kraju emituje signal finished()
    thread->start();
}

void MainWindow::onProgressIsMade(QString percentage)
{
    ui->lwProgress->addItem(percentage);
}

void MainWindow::onPiIsCalculated(double pi)
{
    ui->lePi->setText(QString::number(pi));
    ui->pbStartCalculating->setEnabled(true);
}

