// i u okviru ovog fajla nam treba express jer se tu nalazi objekat za rutiranje zahteva
const express = require('express');

// NOTE: ovo smo zakomentarisali nakon razdvajanja ovog fajla na cisto rutiranje i implementaciju funkcija
// zatos to od tog trenutka, ovaj fajl gde rutiramo ne mora vise da zna nas model (?)
    // psoto vise ne uvozimo ovo u app.js, mora ovde, samo pazimo da relativna putanja bude dobra
    // const users = require('../../models/users');
// umesto modela ucitavamo kontroler gde su implementacije funkcija koje se pozivaju pri zahtevima
const userController = require('../../controllers/users');

const router = express.Router();

// OVDE SMO PREKOPIRALI SVE ONE RUTE KOJE SMO PRVO PISALI U app.js
// potrebna nam je jos jedna izmena, kada smo prvo pisali sve, zahtevi su nam bili oblika:   app.zahtev,
// moramo da promenimo u:   router.zahtev

// ne zaboravi na kraju aplikacije da exportujes router, zato sto sada moramo nekako da ga povezemo sa aplikacijom

// NOTE: ovde su stajali i ove rute i implementacije funkcija, ali su onda izdvojene u controllers/users.js
// zajedno sa komentarima

router.get('/api/users/', userController.getAllUsers);  // pazimo da ovde ne pozovemo funkcije (), nego samo prosledjujemo referencu na njih

router.get('/api/users/:username', userController.getUserByUsername);

router.post('/api/users/', userController.addNewUser);

router.put('/api/users/', userController.changeUserPassword);

router.delete('/api/users/', userController.deleteUser);



// da bi ovaj ruter sada mogli da korsitimo na drugim mestima moramo da ga exportujemo
module.exports = router;