// modele cemo uglavnom ucitavati ovako sa velikim slovom od sad
const User = require('../models/users');
// treba nam i mongoose 
const mongoose = require('mongoose');

// izmenjujemo sve nase funkcije tako da rade sa modelom, a ne sa onim nizom koji smo imali do sad
// uglavnom ce se menjati samo redovi gde se radi sa nizom (u komentaru je kod koji je stajao tu pre) 
// NOTE: u ovim primerima pretpostavljamo da je username jedinstven da nebi komplikovali sa id-jevima u pretrazi (?) ali generalno treba da korsitimo id

//NOTE: posto radimo sa exec() ne smemo da zaboravimo async i await

// NOTE: prvo je bio ovaj potpuis funkcije kao u komentaru, ali onda smo zbog obrade gresaka
// svim funkcijama dodali i treci arg koji je ovo 'next'
// const getAllUsers = async (req, res) => {
const getAllUsers = async (req, res, next) => {
    // const allUsers = users.getAllUsers();

    // NOTE: prvo smo pisali bez obrade gresaka, tj bez try catch
    // async/await nam dozvoljava da koristimo try/catch blok
    // generalno sve ove komunikjacije sa bazom treba da ubaciumo u try/catch
    try {
        const allUsers = await User.find({}).exec();
    } catch(err) {
        next(err);  // ovako obradjujemo greske kada radimo sa mongoose (?) potrebno je da next dodamo u sve potpise funkcija
                    // next je funkcija srednjeg sloja (?), samo propagiramo gresku dalje, a onda cemo na nivou aplikacije imati jednu krajnju obradu greska (?)
    }
    res.status(201).json(allUsers);
}

// const getUserByUsername =  async (req, res) => {
const getUserByUsername =  async (req, res, next) => {
    try {   // nakndano dodat try/catch
        const _username = req.params.username;

        if (_username == undefined) {
            res.status(404).json();
        }
        
        //const foundUser = users.getUserByUsername(username);
        const foundUser = await User.find({username: _username}).exec();

        // if(foundUser == null) {
        //     res.status(404).json();
        // }

        res.status(200).json(foundUser);
    } catch(err){
        next(err);
    }
}

// const addNewUser = async (req, res) => {
const addNewUser = async (req, res, next) => {
    const {username, email, password} = req.body; 

    if (!username || !email || !password) {
        res.status(400).json();
    } 
    else {
        // const isAdded = users.addNewUser(username, email, password);

        try {   // nakndano dodat try/catch
            // ova funkcija ce imati malo vece izmene, prvo moramo da napravimo novog korisnika. Kosristimo konstruktor koji nam je definisan shemom (?)
            const newUser = new User({
                _id: new mongoose.Types.ObjectId(),     // BITNO: pazi ovde da pri konstrukcji objekta ovde zapravo napravis novi ObjectId objekat i da ne stavis nigde Schema!!! 
                username: req.body.username,
                email: req.body.email,
                password: req.body.password,
                // status ne moramo da navodimo jer smo u shemi rekli mda ce po defaultu da bude 'active'
                // note: u odnosu na primer sa proslog casa, u ovoj bazi sa kojom radimo imamo i age i progSkills, pa posto smo samo kopirali kod, unosimo ga rucno
                // da nebi komplikovali, ovo inace treba da se takodje prosledi preko req.body
                age: 20,
                progSkills: ['JS']
            }); 

            // dodavanje novog korisnika u bazu mozemo sa metodom save() koji je takodje asinhron
            // save tacno zna u koju kolekciju se ovo upisuje jer je newUser konstruisan da prati ovu konkretnu shemu (?)
            await newUser.save();

            //Gresku vise ne obradjujemo na ovaj nacin
            // if(!isAdded) {
            //     res.status(403).json();
            // }
            // else {
            //     const user = users.getUserByUsername(username);
            //     res.status(201).json(user);
            // }
            res.status(201).json(newUser);
        } catch(err){
            next(err);
        }
    }
};

// const changeUserPassword = async (req, res) => {
const changeUserPassword = async (req, res, next) => {
    const {_username, oldPass, newPass} = req.body;

    if(!_username || !oldPass || !newPass) {
        res.status(400).json();
    }
    else {
        //const isChanged = users.changeUserPassword(username, oldPass, newPass);
        // if(!isChanged) {
        //     res.status(403).json();
        // }
        // else {
        //     const user = users.getUserByUsername(username);
        //     res.status(201).json(user);
        // }
        try { // naknadno dodat try/catch
            const user = await User.find({username: _username}).exec();
            if(user.password != oldPass){
                res.status(400).json();
            }
            else {
                User.updateOne({username: _username}, {$set: {password: newPass}});
                res.status(200).json({success: true});
            }
        } catch(err){
            next(err);
        }
    }
}

// const deleteUser = async (req, res) => {
const deleteUser = async (req, res, next) => {
    try { // naknadno dodat try/catch
        //const {username} = req.body;
        const {id} = req.body;          // ovde cemo za primer da brisemo korisnika po id-ju a ne po usernameu

        // if(!username) {
        //     res.status(400).json();
        // }
        // else {
        //     const isDeleted = users.deleteUserByUsername(username);
        //     if(!isDeleted) {
        //         res.status(403).json();
        //     }
        //     else {
        //         res.status(201).json({success: true});
        //     }
        // }

        // mozemo da pretrazimo po id-ju, u tom slucaju ne navodimo objekat za pretragu vec samo id
        const user = await User.findById(id).exec();

        if(user){
            // imamo i ovaj metod koji brise iz baze po id-ju
            await User.findByIdAndDelete(id).exec();
            res.status(200).json({success: true});
        }
        else {
            res.status(404).json();
        }
    } catch(err){
        next(err);
    }
};


module.exports = {
    getAllUsers,
    getUserByUsername,
    addNewUser,
    changeUserPassword,
    deleteUser
}