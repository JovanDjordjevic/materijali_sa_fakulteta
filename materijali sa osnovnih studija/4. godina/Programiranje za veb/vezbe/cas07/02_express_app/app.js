const express = require('express');

// na pocetku, pre razdvajanja fajlova kada je sve bilo napisano u app.js, morali smo da importujemo ovo
//const users = require('./models/users');

// ovaj body-parser mozemo da ukljucimo u promenljivu kao do sada, ali on ima samo ova 2 metoda pa mozemo dekonstrukcijom
// danas ce nam trebati samo ova json
const {json, urlencoded} = require('body-parser');

// importujemo ruter nakon razdvajanja
const usersAPI = require('./routes/api/users');

const app = express();

// ovu liniju smo dodali kada smo radili POST zahtev, ima veze sa ovom fukcijom iz body parser koju smo importovali
// rekla je da ce objasnjavati ovo use() i na kasnijim vezbama
// ovim kazemo da cemo koristiti ovu json() funkciju za parsiranje svih zahteva ili odgovora koji prolaze kroz nasu aplikaciju (?)
app.use(json());

// postavljanje ruta
//OVDE SMO PRVO PISALI KAKO SE KOJI ZAHTEV PONASA PA JE POSLE PREBACENO U ROUTES FOLDER 

// nakon razdvajanja je potrebno da povezemo nas app sa rutama
// opet koristimo use(), argumenti koje navodimo su   putanja do rutera (ovde je to samo / zato sto vec sve adrese zahteva pocinju sa api/users)
// i ruter objekat
// jos jedna cesta praksa je da mi ovde kao putanju bas napisemo /api/users i onda da to izbrisemo iz svih onih zahteva u users.js
// da bismo smanjili ponavljanje. Time dobijamo i na jasnoci ovde sta znaci sta u app.js
// nisam to uradio ovde, ali ona na vezbama jeste
app.use('/', usersAPI);


// pokretanje servera je na pocetku stajalo ovde, ali smo ga izbrisali(zakomentarisali) nakon sto smo napisali server.js
    // const port = process.env.PORT || 5000;
    // app.listen(port, () => {
    //     console.log(`Server listening on port ${port}`);
    // });

// ovaj export smo uradili kada smo krenuli da pisemo server.js
module.exports = app;