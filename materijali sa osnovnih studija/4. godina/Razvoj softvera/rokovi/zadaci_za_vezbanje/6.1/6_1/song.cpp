#include "song.h"
#include <QVariant>
#include <iostream>

Song::Song()
{

}

void Song::load(QVariant data)
{
    QVariantMap map = data.toMap();
    artist = map.value("artist").toString();
    title = map.value("title").toString();
    album = map.value("album").toString();
    rating = map.value("rating").toDouble();
    year = map.value("year").toUInt();

    QVariantList featureList = map.value("feature").toList();
    for(const auto &feature : featureList)
    {
        features.push_back(feature.toString());
    }

    QVariantList genreList = map.value("genres").toList();
    for(const auto &genre : genreList)
    {
        genres.push_back(genre.toString());
    }
}

QVariant Song::save() const
{
    QVariantMap map;

    map.insert("artist", artist);
    map.insert("title", title);
    map.insert("album", album);
    map.insert("rating", rating);
    map.insert("year", year);

    QVariantList featureList;
    for(const auto& feature : features)
    {
        featureList.append(feature);
    }
    map.insert("feature", featureList);

    QVariantList genreList;
    for(const auto& genre : genres)
    {
        genreList.append(genre);
    }
    map.insert("genres", genreList);

    return map;
}


QString Song::toString()
{
    QString res = "Artist: " + artist + "\n";
    res += "Title: " + title + "\n";
    res += "Album: " + album + "\n";
    res += "Rating: " + QString::number(rating) + "\n";
    res += "Year: " + QString::number(year) + "\n";
    res += "Featuring: ";
    for(const auto& f : features){ res+= f + " "; }
    res += "\nGenres: ";
    for(const auto& g : genres){ res+= g + " "; }
    res += "\n";

    return res;
}
