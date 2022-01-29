// cesta praksa je da deo koji pokrece server i deo koji obradjuje zahteve odvoje ovako u 2 dela
// ovaj fajl smo napisali tek nakon sto smo napisali ceo app.js

const http = require('http');  // ugradjen modul
const app = require('./app');  // nasa aplikacija

// detaljna objasnjenja sta sve ima u ovom http modulu moze da se nadje na netu ili u onoj skripti
// ovde samo neke stvari koristimo

const port = process.env.PORT || 5000;

// createServer funkciji moze da se proseldi svasta, ali mi hocemo da prosledimo funkc koja ce da se pozove
// kada se server pokrene. Mozemo da ovde prosledimo ceo app koji smo napisali pre ovoga i onda ce on iskoristiti
// sve funkcionalnosti koje smo u njemu implementirali (?)
const server = http.createServer(app);

// pokretanje servera
server.listen(port, () => {
    console.log(`Server is active and listening...`);
});

// nakon sto smo izdvojili ovo u server.js, pokretanje servera nam vise ne treba u app.js pa ga odatle brisemo