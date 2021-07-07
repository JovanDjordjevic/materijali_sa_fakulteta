#include "song.h"
#include <QVariant>
#include <iostream>

Song::Song()
    : artist(""), title(""), album(""), features(), rating(0.0), genres(), year(0)
{

}

void Song::load(QVariant data)
{
    features.clear();
    genres.clear();

    QVariantMap vmap = data.toMap();
    artist = vmap.value("Artist").toString();
    title = vmap.value("Title").toString();
    album = vmap.value("Album").toString();
    rating = vmap.value("Rating").toDouble();
    year = vmap.value("Year").toUInt();

    QVariantList featureList = vmap.value("Features").toList();
    for(auto &v : featureList )
    {
        QString feature = v.toString();
        features.append(feature);
    }

    QVariantList genreList = vmap.value("Genres").toList();
    for(auto &v : genreList )
    {
        QString genre = v.toString();
        genres.append(genre);
    }
}

QVariant Song::save() const
{
    QVariantMap vmap;
    vmap.insert("Artist", artist);
    vmap.insert("Title", title);
    vmap.insert("Album", album);
    vmap.insert("Rating", rating);
    vmap.insert("Year", year);

    QVariantList featureList;
    for(auto &f : features)
    {
        featureList.append(f);
    }
    vmap.insert("Features", featureList);

    QVariantList genreList;
    for(auto &g : genres)
    {
        genreList.append(g);
    }
    vmap.insert("Genres", genreList);

    return vmap;
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
