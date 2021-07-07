#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbStartCalculating, &QPushButton::clicked, this, &MainWindow::calculatePiValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//hocemo da aproksimiramo vrednost Pi pomocu Monte Karlo metode u 100 miliona iteracija
void MainWindow::calculatePiValue()
{
    //prvo smo radili bez niti. Primetili smo da se desava da ako se nase izracunavanje vrsi u istoj niti koja je zaduzena za GUI
    //desice se da to izracunavanje blokira GUI, us mislu nece se lepo ispisivati jedan po jedan item u progress nego sve odjednom
    //i npr ne mozemo da kliknemo na lineEdit da unesemo sami nesto. Resenje je da ove dve stvari razdvojimo u zasebne niti
    //.exec() metod u mainu zapravo pokrece "nit 0" u kojoj je GUI. Takodje, svaka nit koju napravimo moze imati svoju petlju dogadjaja, tj exec() metod
    //connect metod ima i opcioni peti argument koji je enum koji predstavlja tip konekcije (po defaultu je Qt::AutoConnection):
    //Qt::DirectConnection - slot se izvrsava odmah cim se signal emituje, i izvrsava se u istoj niti u kojoj se signal emituje
    //Qt::QueuedConnection - slot se poziva kada se kontrola vrati petlji dogadjaja niti u kojoj primalac postoji, i taj slot se izvrsava u okviru niti prihvataoca signala
    //ima ih jos, ostavio je na sajtu dokumentaciju, AutoConnect u sustini sam gleda afinitet niti i bira da li je Direct ili Queued ili neki drugi (?)

    auto hits = 0u, count = 0u;
    //apostrofima mozemo odvajati brojeve ovako radi citljivosti (od c++17(?))
    const auto iterations = 100'000'000u;

    //hocemo da updatujemo progress na svakih 10%
    const auto iterUpdate = 10'000'000;
    ui->lwProgress->clear();

    while(count < iterations)
    {
        //global je metod koji nam dohvata instancu klase QRandomGenerator kojoj je vec postavljen seed za nasumicne brojeve, ujedno je i bezbedna za niti
        //generateDouble vraca iz intervala [0,1), a nama treba [-1, 1) zato radimo *2-1
        const auto x = QRandomGenerator::global()->generateDouble() * 2 - 1;
        const auto y = QRandomGenerator::global()->generateDouble() * 2 - 1;

        if(x*x + y*y <= 1.0){
            ++hits;
        }

        ++count;

        if(count % iterUpdate == 10u)
        {
            const auto percent = QString::number(count / iterUpdate *10u) + "%";
            ui->lwProgress->addItem(percent);
        }
    }

    const auto pi = 4.0 * hits / count;
    ui->lePi->setText(QString::number(pi));
}

