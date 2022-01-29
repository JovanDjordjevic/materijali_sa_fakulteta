const express = require('express');
const {json, urlencoded} = require('body-parser');
const usersAPI = require('./routes/api/users');

// i ovde nam treba mongoose
const mongoose = require('mongoose');

const app = express();


// povezivanje na bazu
const dbString = "mongodb://localhost:27017/users";

mongoose.connect(dbString, {
    useUnifiedTopology: true,
    useNewUrlParser: true,
});

mongoose.connection.once('open', function () {
    console.log("Uspesno povezivanje na bazu!");
});

mongoose.connection.on('error', function (err) {
    console.log("Greska: ", err);
});

// ovo 'use' zapravo definise funkcije srednjeg sloja (?)
app.use(json());
// NOTE: vidi routes/api/users.js
app.use('/api/users', usersAPI);
// kada bismo imali jos nekih kolekcija u bazi, ovde bi moglo da bude i npr nesto ovako:
// app.use('/api/orders', ordersAPI);
// app.use('/api/products', productsAPI);
// ...

// NOTE: ovu funkc smo napisali posle one ispod
// moze da se desi i jedna specijalna greska koju nigde do sada nismo obradili, a to je pristup nekoj putanji za koju nismo definisali ponasanje (?)
// to se isto definise ovde na nivou aplikacije
// sigurni smo da ce se bas ova funkcija pozvati u slucaju nepravilnog zahteva zbog toka dogadjaja:
// serverus tigne zahtev  u server.js fajl,  on to prosledi u aplikaciju tj app.js, aplikacija se izvrsava i zahtev prolazi kroz funkcije srednjeg sloja koje smo definisali
// tj ono sto smo naveli u .use(). Tu prodju kroz json(), i onda redom po mogucim putanjama koje su navedene. Redom pokusava zahtev da se matchuje sa nekom putanjom, 
// i ako se ne pronadje gde treba da ode, naicice sa na use() gde je ova funkcija i ovde ce se uhvatiti svi pozivi koji nisu nasli dobru putanju
// NOTE: zbog ovog nacina rada treba da se pazimo da slucajno kao prvu putanju stavimo neku najopstiju mogucu koja ce da uhvati sve zahteve
// jer to moze da izazove da zahtevi odu na pogresnu lokaciju iako specificna putanja na koju idu mozda bude navedena u use() ispod te opste
app.use(function (req, res, next) {
    const error = new Error('Zahtev nije podrzan!');
    error.status = 405;

    next(error); // gresku koja nastaje u ovom slucaju mozemo samo da propagiramo dalje u onu finalnu obradu greske u aplikaciji
});

// ovo smo dodali nakon sto smo uveli try/catch blokove u controllers/user.js
// funkcija koju pravimo treba da ima paramatear error i sve one parametre koje su imale ostale funkcije (?)
app.use(function(error, req, res, next) {
    const statusCode = error.statusCode || 500;
    // cela ideja ove uniformne obrade gresaka je da mi ovde ako se desi greska posaljemo jedan odgovor sa informacijom o gresci
    res.status(statusCode).json({
        error: {
            message: error.message,
            status: statusCode,
            stack: error.stack,
        }
    });
});



module.exports = app;