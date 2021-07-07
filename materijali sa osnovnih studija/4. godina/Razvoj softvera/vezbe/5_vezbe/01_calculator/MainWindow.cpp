#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //sve iznad ovoga je automatski generisano. Trenutno se nalazimo u konstruktoru klase MainWindow
    //setupUi je funkc koja ce nam podesiti prozor tako da mozemo pristupati njegovim elementima

    //u konstruktoru je potrebno da povezemo signal/slot
    //to radimo sa connect( ko_salje_signal, koji_je_signal_u_pitanju, ko_prima_signal, koji_metod/funkc_ce_se_pozvati )
    //taj metod koji se poziva mora biti definisan u 'slots:' odeljku klase (?)
    connect(ui->pbIncA, &QPushButton::clicked, this, &MainWindow::onIncA);
    connect(ui->pbIncB, &QPushButton::clicked, this, &MainWindow::onIncB);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onIncA()
{
    /* NOTE: prvo smo napisali ovo u komentaru pa smo izdvojili u zasebnu funkciju
    //kada se pritisne ++a dugme, zelimo da parsiramo ono sto se nalazi u odgovarajucem LineEdit polju
    //ui je pokazivac na klasu MainWindow (?) gde imamo pokazivace na sve elemente (labele, buttone itd) kojima pristupama preko imena koje
    //za njih navedemo kada ih pravimo. Metod text() ce iz odgovarajuceg elementa izvuci QString sadzaj
    auto frac = parseFraction(ui->leA->text());
    m_a = frac; //m_a smo definisali kao polje klase MainWindow
    ++m_a;
    //zelimo sad npr inkrementirani rezultat da upisemo u isti LineEdit iz kojeg smo ga procitali
    ui->leA->setText( static_cast<QString>(m_a) );
    */
    incrementFractionFromLineEdit(ui->leA, m_a);
}

//slicno za ++b
void MainWindow::onIncB()
{
    incrementFractionFromLineEdit(ui->leB, m_b);
}

Fraction MainWindow::parseFraction(QString fracInput) const
{
    // -1/2   -> dobicemo listu  {"-1" , "2"}
    auto strList = fracInput.split('/');
    if (strList.size() != 2){
        //ako smo ovde znaci da unos nije dobar
        return Fraction();  //npr vratimo prazan razlomak
    }
    int numerator;
    unsigned denominator;
    bool success;
    numerator = strList[0].toInt(&success);  //ugradjeni toInt() metod trazi bool argument u koji ce smestiti da li je konverzija iz stringa u broj prosla OK
    if(!success){
        return Fraction();
    }
    denominator = strList[1].toUInt(&success);   //toUInt je isto samo za unsignedd
    if(!success){
        return Fraction();
    }

    return Fraction(numerator, denominator);
}

void MainWindow::incrementFractionFromLineEdit(QLineEdit *le, Fraction &f)
{
    auto frac = parseFraction(le->text());
    f = frac;
    ++f;
    le->setText( static_cast<QString>(f) );
}

