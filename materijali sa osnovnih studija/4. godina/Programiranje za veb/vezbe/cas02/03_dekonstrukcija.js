let niz = [54, 60, 32, 1, 25, 7]

// neka funkcija iz koje zelimo da se vrati i neki broj i indeks, jedan nacin
// je da vratimo neki objkeat, ali mozemo i slicno kao u pjatonu, vratimo niz i onda
// ga uhvatimo i dekonstruisemo pri pozivu funkcije
function nadjiBrojManjiOd(niz, granica)
{
    for(let i=0; i<niz.length; ++i)
    {
        tekuciBroj = niz[i];
        if(tekuciBroj < granica)
        {
            return [tekuciBroj, i];
        }
    }

    return [null, -1];
}

//console.log(nadjiBrojManjiOd(niz, 40));
[broj, indeks] = nadjiBrojManjiOd(niz, 40);
console.log(broj, indeks)