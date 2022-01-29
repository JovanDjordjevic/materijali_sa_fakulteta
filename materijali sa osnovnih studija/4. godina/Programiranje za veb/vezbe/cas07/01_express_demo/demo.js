// dohvatamo express modul
const express = require('express')

// ova funkcija pravi aplikaciju na kojoj se zasniva citav ovaj framework, nad ovom aplikacijom 
// cemo pozivati razne funkckije
const app = express();

// nasa aplikacija moze da salje  zahteve (pored get() imamo i post() i put())
// mi ovde za primer pravimo get zahtev za korenu putanju, to je npr kada kucamo: www.google.com/ , to je koren, ne idemo dalje od toga
// drugi arg je callback koji mora da primi ova 2 arg, koji se poziva svaki put kada neko posalje get zahtev na tu putnaju (?)
// req (skraceno od request), i res (response) su neki objekti sa nekim svojstvima (videcemo posle)
app.get('/', (req, res) => {
    // send salje odgovor kome ce prosledjena poruka biti u telu
    res.send('Hello express');
});

// hocemo da pokrenemo server, sa RM se secamo da server ne mora da zna svoj hostname ali mora da zna na kom se portu nalazi
// podsecanje sa proslog casa, ako kao promenljiva okruzenja postoji neki PORT koji smo definisali, mozemo njega da koristimo ili rucno da
// postavimo npr na 5000
const port = process.env.PORT || 5000;

// listen pokrece server. prvi arg je port na kom se pokrece i slusa zahteve, a drugi je funkcija koja ce se pozvati
// kada se server pokrene. Primetimo da nigde u get metodi iznad nismo naglasili da je to bas http zahtev
// listen pokrece http server i sve se desava u pozadini za nas
app.listen(port, () => {
    console.log("Server is listening on port " + port);
});