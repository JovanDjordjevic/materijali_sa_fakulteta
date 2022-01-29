// mongoose je biblioteka koaj radi mapiranje dokumenata/kolekcija iz baze u odgovarajuce objekte
// i to nam omogucava da jednostavno radimo sa njima u kodu

// NOTE: na vezbama je imala neki bag gde verzija node-a koju ima nije bas kompatibilna sa verzijom mongoose-a koju koristi
// i to je popravila tako sto je otisla u package.json i rucno unela stariju verziju mongoose-a, stavila je 5.0.0
// i onda je to proradilo, ali ti nije bas lepo resenje

// NOTE: pre ovog primera smo radili mongoimport iz proslog primera da bi imali nekakve podatke u bazi

const mongoose = require('mongoose');

// pre negos to uradimo bilo sta drugo moramo da se konektujemo na neku bazu
// podrazumevani port je 27017 (?)
// u nasem slucaju baza 'users' se nalazi na nasem racunaru pa je adresa mongodb://localhost:port/ime_baze
const dbString = 'mongodb://localhost:27017/users';

// ostvaruje se konekcija ka bazi, prvi arg je adresa baze, a drugi opcioni arg je 
// neki konfiguracioni parametar, obvicno se navodi ovo sto smo mi stavili ovde radi kompatibilnosti sa drugim verzijama (?)
mongoose.connect(dbString, {
    useNewUrlParser: true,
    useUnifiedTopology: true,
});

// shema baze nam govori o tome kog formata treba da budu dokumenti u bazi, tj koja svojstva moraju da imaju, koje su 
// njihove karakteristike, tip itd..
// pravimo novu schemu. Konstruktoru proslejdujemo objekat koji opisuje kako sta izgleda
// NOTE: obavezno tip u shemi za _id navodimo sa mongoose.Schema.Types....
const usersSchema = new mongoose.Schema({
    _id: mongoose.Schema.Types.ObjectId,
    username: {          // mozemo i na ovaj nacin, pri cemu mozemo da navedemo i da je polje obavezno
        type: String, 
        required: true,
    },
    email: {
        type: String, 
        required: true,
    },
    status: {
        type: String,
        default: 'active',  // ovako mozemo da naznacimo podrazumevanu vrednost prilikom unosa podatka u bazu za ovo polje
    },
    password: {
        type: String,
        required: true,
    },
    age: Number,   // ovako kada se navodi(isto smo imali i za id) je isto kao da smo pisali:    age: {type: Number}, samo je ovako krace
    progSkills: [String],   // niz stringova
});

// kada smo odredili shemu, potrebno je da je nekako povezemo sa samom kolekcijom dokumenata 
// prvi arg je ime kolekcije, a drugi je shema koju smo definisali
// Nadalje kada budemo hteli da radimo neke operacije sa bazom, koristicemo ovaj userModel
const userModel = mongoose.model('users', usersSchema);

// kada se ostvari konekcija, u mongoose.connection objektu imamo razne stvari
// npr once ce na dogadjaj koji prosledimo (npr 'open') da uradi funkciju koju mu prosledimo
// postoji i 'on' funkcija koja ne radi to jednom nego svaki put kada se dogadjaj desi
mongoose.connection.once('open', function(){
    console.log("uspesno povezivanje");
});

mongoose.connection.on('error', function (err){
    console.log("Greska: ", err);
});


// sve funkcije koje mongoose koristi su asinhrone i kao drugi arg im se uvek ocekuje neki callback
// i svi callbackovi moraju da imaju potpis  (greska, rezultat_izvrsenog_upita)

// imamo analogone za sve one funkcije koje smo imali u mongo shellu
// i slicno se koriste

// prvi nacin dohvatanja iz baze
userModel.findOne({username: 'john'}, (err, result) => {
    if (err) {
        console.log("Greska: ", err);
    }
    else {
        console.log(result);
    }
});

// drugi nacin, koristimo execute metod
// ovaj nacin cemo preferirati (?)
const printUserData = async function (username) {
    // umesto prosledjivanja callbacka, mozemo da ulancamo metod exec()
    // povratna vrednost ce biti Promise, i onda mozemo pre = da stavimo await
    // koji ce da nam otpakuje Promise i smesti ga u user
    // posto smo ovde koristili await, mormao da naglasimo da je funkcija async iznad
    const user = await userModel.findOne({username: username}).exec();
    console.log(user);
};
// aync i await su morali ovako u okviru neke funkcije, pa moramo da je pozovemo
printUserData("pavle");

// treci nacin
const printUserData2 = async function (username) {
    // imamo ovakve neke metode sto podseca malo na SQL, ovo isto moze sa exec
    const user = await userModel.findOne().where('username').equals(username).exec();
    console.log(user);
}
printUserData2("maja");
