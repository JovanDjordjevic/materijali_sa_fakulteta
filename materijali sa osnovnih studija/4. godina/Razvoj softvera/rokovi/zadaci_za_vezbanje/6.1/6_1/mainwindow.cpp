#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "song.h"
#include "xmlserializer.h"
#include <iostream>

//note: nisam implementirao dijalog za selektovanje fajla
//note: citanje iz xml ne radi lepo, ali pisanje radi

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbUcitajPesmu, &QPushButton::clicked, this, &MainWindow::loadAndDisplay);
    connect(ui->pbSacuvajIzmene, &QPushButton::clicked, this, &MainWindow::saveChanges);

    connect(ui->leIzvodjac, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leNaziv, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leAlbum, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leRejting, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leGodina, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leGostujuci, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);
    connect(ui->leZanrovi, &QLineEdit::editingFinished, this, &MainWindow::changeSongFields);

    ui->pbSacuvajIzmene->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAndDisplay()
{
    XMLSerializer xmlser;
    QString filepath = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/6.1/6_1/song.xml";
    xmlser.loadFromFile(m_song, filepath);

    ui->leIzvodjac->setText(m_song.artist);
    ui->leNaziv->setText(m_song.title);
    ui->leAlbum->setText(m_song.album);
    ui->leRejting->setText(QString::number(m_song.rating));
    ui->leGodina->setText(QString::number(m_song.year));

    QString features = "";
    for(const auto &f : m_song.features)
    {
        features += f + "\n";
    }
    ui->leGostujuci->setText(features);

    QString genres = "";
    for(const auto &g : m_song.genres)
    {
        features += g + "\n";
    }
    ui->leZanrovi->setText(genres);

    ui->pbSacuvajIzmene->setEnabled(true);
}

void MainWindow::saveChanges()
{
    XMLSerializer xmlser;
    QString filepath = "C:/Users/Jovan/Desktop/RS/rokovi/zadaci_za_vezbanje/6.1/6_1/songNew.xml";
    xmlser.saveToFile(m_song, filepath, "Song");
}

void MainWindow::changeSongFields()
{
   m_song.artist = ui->leIzvodjac->text();
   m_song.title = ui->leNaziv->text();
   m_song.album = ui->leAlbum->text();
   m_song.rating = ui->leRejting->text().toUInt();
   m_song.year = ui->leGodina->text().toUInt();

   auto features = ui->leGostujuci->text().split(" ");
   m_song.features.clear();
   for(const auto& f : features)
   {
       m_song.features.append(f);
   }

   auto genres = ui->leZanrovi->text().split(" ");
   m_song.genres.clear();
   for(const auto& g : genres)
   {
       m_song.genres.append(g);
   }

}

