#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "StudentSerialization_global.h"
#include "Serializable.h"

class STUDENTSERIALIZATION_EXPORT Serializer
{
public:
    virtual ~Serializer() = default;

    //ovo je nas interfejs prema objektima koji mogu d ase serijalizuju (nasledjuju Serializable klasu)
    //za svaki od xml, json, binary formata  napravicemo novu klasu koja implementira ovaj interfejs

    //posto XML zahteva neki kao koreni tag, imamo 2 opcije, jedna je da ga fiksiramo, a druga je da ga prosledimo
    //iako binary i json nece koristiti to, dodacemo taj opcioni treci argument u potpis nase funkcije
    virtual void save(const Serializable &serializable, const QString &filepath, const QString &rootName = "") = 0;

    virtual void load(Serializable &serializable, const QString &filepath);

};

#endif // SERIALIZER_H
