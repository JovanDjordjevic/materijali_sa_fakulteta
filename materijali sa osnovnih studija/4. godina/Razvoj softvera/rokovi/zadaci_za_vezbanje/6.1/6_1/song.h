#ifndef SONG_H
#define SONG_H

#include <QObject>

class Song
{
public:
    Song();

    //iz/u QVriant
    void load(QVariant data);
    QVariant save() const;

    QString toString();
    void setRating(double newRating) { rating = newRating; }

public:
    QString artist;
    QString title;
    QString album;
    QVector<QString> features;
    double rating;
    QVector<QString> genres;
    unsigned int year;

};

#endif // SONG_H
