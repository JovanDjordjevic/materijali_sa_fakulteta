// ideja je da kontroleri jedini barataju sa nasim modelom (?)
// i zato treba ovde da ucitamo model
const users = require('../models/users');

// NOTE: ne zaboravi export na kraju!

// (ovde opisujemo kako se ponasa koji zahtev koje smo rekli da zelimo da imamo (vidi readme fajl))
// GET         /api/users/                  Get all users 
// NOTE: ovo je na vezbama testirano tako sto smo pokrenuli prvo server sa:   node app.js
// i onda u browseru u adress bar upisali:   localhost:5000/api/users/
// response koji se salje je zapravo html koji ce biti prikazan na stranici
const getAllUsers = (req, res) => {
    const allUsers = users.getAllUsers();

    // PRVI NACIN:
    // pre send() metoda mozemo da konfigurisemo headere odgovora
    // ako ne konfigurisemo nista, bice psotavljene default vrednsoti, npr za content type bice stavljeno text/html
    // posto smo odlucili da zelimo da nas odgovor bude neki json, ovo nam ne odgovara jer ispis nece lepo biti formatiran
    //        res.setHeader('Content-Type', 'application/json');
    // po defaultu je status 200, ali mozemo i sami da postavimo neki
    //        res.status(201);
    // sada kada je podeseno u headeru da je u pitanju json, bice nam lep ispis
    // NOTE: meni kada pokrenem u chrome-u nije lep ispis
    //        res.send(JSON.stringify(allUsers));

    // DRUGI NACIN:
    // postoji metoda koja kao odgovor bas salje json, da nebi morali svaki put rucno da parsiramo
    // ona sama i postavi header na json i posalje zahtev
    //        res.json(allUsers);
    // moze i da se ulanca sa jos nekom operacijom, npr status
    res.status(201).json(allUsers);
}


// GET         /api/users/{username}        Get all users by username
// ove parametre u express-u navodimo sa :, dakle ono sto je posle : ce se tretirati kao parametar
// i mozemo da ga dohvatimo iz req objekta, gde ce se zvati isto tako
const getUserByUsername =  (req, res) => {
    // dohvatamo parametar iz req
    const username = req.params.username;

    // ukoliko je parametar los mozemo da vratimo npr prazan json
    if (username == undefined) {
        res.status(404).json();
    }
    
    const foundUser = users.getUserByUsername(username);
    // ovako smo odlucili da nam bude api kad taj korisnik ne postoji
    if(foundUser == null) {
        res.status(404).json();
    }

    res.status(200).json(foundUser);
}


// POST        /api/users/                  Add user
// kada saljemo PSOT zahtev parametre zahteva mozemo da stavimo u telo zahteva (?)
// generalno osetljive informacije (tipa passwordi i slicno) se salju u telu zahteva, a ne ovako u url-u kao neke
// manje bitne informacije, tipa username iz proslog zahteva
const addNewUser =  (req, res) => {
    // kada smo radili sa parametrima u GET, imali smo req.params, kad radimo sa POST, imamo req.body (?)
    // to ce biti objekat koji ima svosjtva koja se zovu isto kao ti parametri koji nam trebaju
    // na pcoetku, body nije isparsiran kao JS objekat vec neki json
    // za to mozemo da koristimo body-parser paket
    
    // konkretno, u ovom trenutku smo ubacili ono app.use(json()) i psoto je req sada prosao kroz json() funkciju (?)
    // od ovog trenutka je korektno isparsiran kao objekat i mozemo da hvatamo njegova svojstva

    // mozemo da dohvatimo sve rucno, a moze i ovako dekonstrukcijom
    const {username, email, password} = req.body; 

    // moramo da se osiguramo ako neki od podataka nije ispravan
    if (!username || !email || !password) {
        res.status(400).json();
    } 
    else {
        const isAdded = users.addNewUser(username, email, password);
        if(!isAdded) {
            res.status(403).json();
        }
        else {
            // cesta praksa za ovakvo dodavanje korisnika je da se bas taj korisnik i vrati u odgovoru
            const user = users.getUserByUsername(username);
            res.status(201).json(user);
        }
    }
}


// PUT         /api/users/                  Change user's password
// generalno put zahteve cemo koristiti za izmenu sadrzaja
const changeUserPassword = (req, res) => {
    const {username, oldPass, newPass} = req.body;

    if(!username || !oldPass || !newPass) {
        res.status(400).json();
    }
    else {
        const isChanged = users.changeUserPassword(username, oldPass, newPass);
        if(!isChanged) {
            res.status(403).json();
        }
        else {
            const user = users.getUserByUsername(username);
            res.status(201).json(user);
        }
    }
}


// DELETE      /api/users/                  Delete user by username
const deleteUser = (req, res) => {
    const {username} = req.body;

    if(!username) {
        res.status(400).json();
    }
    else {
        const isDeleted = users.deleteUserByUsername(username);
        if(!isDeleted) {
            res.status(403).json();
        }
        else {
            // neki random glup objekat smo vratili, cisto da ne bude prazno
            res.status(201).json({success: true});
        }
    }
}


module.exports = {
    getAllUsers,
    getUserByUsername,
    addNewUser,
    changeUserPassword,
    deleteUser
}