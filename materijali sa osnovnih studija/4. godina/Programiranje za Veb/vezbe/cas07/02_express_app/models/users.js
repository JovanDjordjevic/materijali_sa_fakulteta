const uuid = require('uuid');

// uuid je modul koji moze da nam generise neki jedinstveni identifikator
// imamo razlicite metode za ovo:
// uuid.v1()     // npr v1 generise id tako sto uzima u obzir trenutno vreme i MAC adresu racunara
// uuid.v4()     // v4 koristi neki generator slucajnih brojeva 

// ne moramo ovo da pamtimo, ovaj modul cemo da koristimo da pravimo id-jeve za korisnike,
// ova prva 4 u ovoj nasoj 'bazi' su neko hardcodovano djubre

const users = [
    {
        id: 'dh1-awd898-912fh-98f12j89-d2190',
        username: 'john',
        email: 'john@matf.bg.ac.rs',
        password: 'john123',
        status: 'active',
    },
    {
        id: '81u2-9012-90j1r3-j13r-112414ewd',
        username: 'pavle',
        email: 'pavle@matf.bg.ac.rs',
        password: 'pavle123',
        status: 'active',
    },
    {
        id: '0-901fj0-f1gk12-gk12rk3f-a3fa3',
        username: 'maja',
        email: 'maja@matf.bg.ac.rs',
        password: 'maja123',
        status: 'inactive',
    },
    {
        id: '789-ah9rjm-afaga2g2a-ga-2farttoi3hr0',
        username: 'klara',
        email: 'klara@matf.bg.ac.rs',
        password: 'klara123',
        status: 'active',
    },
];

// posto ovaj js fajl predstavlja 'bazu', treba da napravimo i neki API sa kojim ce baza da komunicira sa ostalim
// modulima
// ovde cemo za primer sve funkcije da pravimo kao promenljive kojima je dodeljena neka lambda (ovo naravno ne mora ovako)
const getAllUsers = () => {
    return users;
}

const getUserByID = (id) => {
    // filter uzima predikatsku funkciju kao arg, vraca se niz elemenata koji zadovoljavaju predikat
    const findUsers = users.filter((user) => user.id == id);
    // pazimo samo da ne vratimo undefined nego null u slucaju da ovaj user ne postoji, jer je null u JS objektnog tipa
    // ovo je okej posto cemo da se postaramo da user id bude jedinstven
    return findUsers.length > 0 ? findUsers[0] : null;
}

const getUserByUsername = (username) => {
    const findUsers = users.filter((user) => user.username == username);
    return findUsers.length > 0 ? findUsers[0] : null;
}

const getUserByStatus = (status) => {
    const findUsers = users.filter((user) => user.status == status);
    return findUsers;
}

const addNewUser = (username, email, password) => {
    const newUser = {
        id: uuid.v4(), // koristimo uuid samo za demonstraciju, naravno moze i drugacije, npr kada budemo radili sa mongo bazom, koristicemo njene metode
        username: username,
        email: email,
        password: password,
        status: 'active'
    };

    // recimo da smo se dogovorili da username mora da bude jedinstven
    const user = getUserByUsername(newUser.username);
    if (user != null) {
        return false;
    }

    users.push(newUser);
    return true;
}   

const changeUserPassword = (username, oldPassword, newPassword) => {
    const foundUser = getUserByUsername(username);
    
    if (!foundUser) {
        return false;
    }

    // recimo da se stara sifra zahteva da bi se postavila nova
    if(foundUser.password != oldPassword) {
        return false;
    }

    foundUser.password = newPassword;
    return true;
}   

const deleteUserByUsername = (username) => {
    const userIndex = users.findIndex((user) => user.username == username);
    if(userIndex == -1) {
        return false;
    }

    // koristili smo trazenje po indeksu, da bi mogli ovde da iskoristimo splice
    // prvi arg je neki indeks niza, drugi arg je broj elemenata nakon od indeksa koji treba da se obrisu
    // (taj indeks se uracunava, ovde 1 znaci da ce se samo taj obrisati)
    users.splice(userIndex, 1);
    return true;
}   

module.exports = {
    getAllUsers: getAllUsers,
    getUserByUsername,   // moze ovako skraceno jer se zovu isto
    getUserByID,
    getUserByStatus,
    addNewUser,
    changeUserPassword,
    deleteUserByUsername
}