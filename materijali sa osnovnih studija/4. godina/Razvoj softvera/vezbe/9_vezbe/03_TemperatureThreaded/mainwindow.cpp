#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "room.h"
#include <QMessageBox> //za porukicu o nepravilnom unosu u nas lineEdit
#include "cellthread.h"

#include <QMutexLocker> //NOTE: u headru smo includovali QMutex, a ne QMutexLocker

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _timer(this)
{
    ui->setupUi(this);
    connect(ui->pbStartReading, &QPushButton::clicked, this, &MainWindow::onPbStartReading);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Room &MainWindow::getRoom()
{
    return *_room;
}

QMutex &MainWindow::getRoomMutex()
{
    return _roomMutex;
}

void MainWindow::onPbStartReading()
{
    const auto number_str = ui->leNumberOfRc->text();
    bool parsed;
    const auto rcNumber = number_str.toInt(&parsed);
    if(!parsed || rcNumber <= 0)
    {
        QMessageBox msgBox(this);
        msgBox.setText("Morate uneti ispravan pozitivan broj!");
        msgBox.exec();
        //msgBox ce blokirati glavni program dok se ne poruka ne zatvori
        //a kada se zatvori msg, radimo return jer ne zelimo da nastavimo izvbrsavanje jer je ulaz nepravilan
        return;
    }

    //da korisnik ne moze vise puta da klikce na ovo
    ui->groupBox->setDisabled(true);

    _room = new Room(rcNumber, this);
    populateTableWidget();

    startThreads();

    //hocemo da nakon sto se pokrene prva nit, na svakih 1.5 sekundi pokrenemo novi thread
    connect(&_timer, &QTimer::timeout, this, &MainWindow::startThreads);

    _timer.start(1500);
}

void MainWindow::populateTableWidget()
{
    //za ovu funkciju nije potrebna sinhronizacija jer se ona desi samo jednom na pocetku

    const auto rcNumber = _room->numberOfRowsAndColumns();

    ui->twRoomMatrix->setRowCount(rcNumber);
    ui->twRoomMatrix->setColumnCount(rcNumber);
    for(auto i=0; i< rcNumber; ++i)
    {
        for(auto j=0; j< rcNumber; ++j)
        {
            const auto cellValue = _room->cellValue(i, j);
            //ovako se pravilno dodaju itemi u onaj table widget sto imamo
            //Svaki clan tabele je jedan QTableWidgetItem
            //primetimo da se ovom kosntruktoru ne prosledjuje parent, jer on cim se doda u tabelu, ona mu postaje parent
            auto tableItem = new QTableWidgetItem(QString::number(cellValue));
            ui->twRoomMatrix->setItem(i, j, tableItem);

            //ovo bi bio pogresan pristup:
            //ui->twRoomMatrix->setItem(i, j, new QTableWidgetItem());
            //jer bismo tu imali curenje memorije, jer niko nebi bio parent tog new QTableWidgetItema koji smo napravili (?)
            //ako bismo ovaj poziv imali nakon proslog pravilnog poziva, tableItem pokazivac bi bio zauvek izgubljen
            //poenta je da ako zelimo da promenimo vrednost polja tabele, necemo pisati ui->twRoomMatrix->setItem(i, j, new QTableWidgetItem());
            //ui->twRoomMatrix->item(i, j)->setText("nova vrednost");
        }
    }
}

void MainWindow::startThreads()
{
    //mutekse mozemo direktno da koristimo, npr:   _roomMutex.lock();  ...naredbe... _roomMutex.unlock()
    //ali taj pristup nije pozeljan jer npr sta ako neki metod u zakljucanom delu koda izazove nekakav izuzetak
    //umsto toga koristimo QMutexLocker kom prosledimo adresu naseg mutexa
    //Potrebno je da ovaj objekat napravimo svugde gde imamo konkurentno citanje/pisanje
    QMutexLocker lock(&_roomMutex);

    //dovoljna je samo ova linija, ne moramo vise da imamo lock i unlock, zatos to prilikom konstrukcije ovog objekta bice zakljucan mutex
    //a otkljucace se kada se pozove destruktor QMutexLockerObjekta, tj na kraju ove funkcije, posto je to lokalni objekat
    //prednost ovoga je sto ce se destruktor sigurno pozvati, cak i u slucaju izuzetka

    const auto rcNumber = _room->numberOfRowsAndColumns();
    for(auto i=0; i< rcNumber; ++i)
    {
        for(auto j=0; j< rcNumber; ++j)
        {
            //setimo se da smo za cellThread rekli da cemo mu MainWindow proslediti kao parent, da bi imali pristuop getRoom metodi
            auto thread = new CellThread(i, j, this);
            connect(thread, &CellThread::threadFinished, this, &MainWindow::onThreadFinished);
            //ne zaboravimo da obrisemo thread kada se zavrsi (NOTE: posto je ovo samo connect, ne moramo da ga pisemo na kraju
            connect(thread, &CellThread::finished, thread, &CellThread::deleteLater);

            //pokrecemo thread
            thread->start();
        }
    }
}

void MainWindow::onThreadFinished(int i, int j)
{
    //sinhronizacija, vidi objasnjenje u starThreads() funkciji
    QMutexLocker lock(&_roomMutex);

    auto cellValue = _room->cellValue(i, j);
    //ovde radimo onu izmenu na pravilan nacin (sto ima komentar inzad)
    //mi znamo da ova tabela sigurno ima vec objekat na i,j poziciji pa nema potrebe da pravimo new QTableWidgetItem
    ui->twRoomMatrix->item(i, j)->setText(QString::number(cellValue));
}
