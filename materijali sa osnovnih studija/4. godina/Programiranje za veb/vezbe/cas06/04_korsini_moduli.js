// u ovom primeru vidimo neke korisne module koje ne moramo sami da instaliramo
// jer vec postoje kada skinemo node (?)
// path, os, fs, url, events


// modul za izgradnju putanja, apstrahuje nam OS
const path = require('path');

//console.log(__dirname);
// join spaja proizvoljan broj argumenata validnim separatorom za nas OS
const myFile = path.join(__dirname, '04_sample_file.txt')
console.log(myFile)

// path.basename() vraca ime fajla do kog vodi putanja
console.log(path.basename(myFile));

// ekstenzija fajla do kog vodi putanja
console.log(path.extname(myFile));

// putanja do direktorijuma u kom se nalazi fajl (tj sve ono pre basename)
console.log(path.dirname(myFile));

// dace nam objekat u kom je putanja koju smo prosledili razlozena, vidi ispis
console.log(path.parse(myFile));



//-------------------------------------
// modul za izvalcenje nekih informacija iz operativnog sistema
const os = require('os');

// vraca nam OS na kom se nalazimo
console.log(os.platform());

// kolicina ukupne slobodne memorije u bajtovima
console.log(os.totalmem());

// kolicina slobodne memorije u bajtovima
console.log(os.freemem());

// arhutektura procesora
console.log(os.arch());

// informacije o procesoru (on izgleda svaki thread vidi kao zaseban (?) npr za 
// 8 core 16 thread dobijam 16 ispisa)
console.log(os.cpus());

// LE - litte endian ili BE - big endidan, 
// govori nam o redosledu cuvanja podatakau memoriji
console.log(os.endianness());



//-------------------------------------
// file system modul
const fs = require('fs');

// za cirtanje fajlova imamo readFile i readFileSync, razlika je u tome sto je readFileSync
// blokirajuc poziv, tj ceka se dok se fajl ne procita, a readFile je asinhrona i moze da primi callback
// funkciju koja se pozove kada se fajl procita (mi cemo preferirati readFile)
// drugi argument je objekat sa nekim dodatnim opcijama, npr encoding itd
// readFileSync nam vraca ceo sadrzaj fajla kao jedan string
const sadrzaj = fs.readFileSync(myFile, {encoding:'utf8'});
console.log(sadrzaj);

// readFile nema povratnu vrednost. Prosledjujemo joj callback funkciju kojoj je prvi argument informacija o
// greskama a drugi arg je fileContents u koji ce nam se sacuvati sadrzaj
fs.readFile(myFile, {encoding:'utf8'}, (err, fileContents) => {
    if(err) {
        console.log("greska! " + err);  // npr ako fajl za citanje ne psotoji, ili npr nemamo pristup fajlu, ovo err nece biti null kao sto je sada
        return;
    }
    else{
        console.log(fileContents);
    }
});

// za pisanje u fajl imamo writeFile i writeFileSync, slicne su razlike izmedju njih kao za pisanje
// callback funkcija koja se salje za writeFile treba da sadrzi samo err
// NOTE: ovaj write kako smo ga mi napisali obrise sve sto postoji u postojecem fajlu i pise od pocetka
const poruka = "Hello from code!";
fs.writeFile(myFile, poruka, (err) => {
    if(err){
        console.log(err);
        return;
    }
    console.log("sve okej");
});



//-------------------------------------
// modul za rad sa URL 
const url = require('url');

// URL objekat za nas moze da parsira adresu koju mu prosledimo
const testURL = new url.URL("http://test.com:3000/info/users.html?firstName=Pera&lastName=Peric")
// ispis celog url
console.log(testURL.href);
// host, ovde ce to biti test.com
console.log(testURL.hostname);
// port, nama 3000, ako u url nema port, ovo ce biti prazno polje
console.log(testURL.port);
// pathname je putanja do resursa  koji smo trazili, nama je: /info/users.html
console.log(testURL.pathname);
// search je query koji smo zadali u URL
console.log(testURL.search);
// objekat koji sadrzi sve parametre iz queryja
console.log(testURL.searchParams);

// mozemo da ispisemo i pomocu forEach (zasto su parametri za foreach u JS
// prvo value pa name boga pitaj)
testURL.searchParams.forEach((value, name)=>{
    console.log(name, value);
});



//-------------------------------------
// modul za upravljanje dogadjajima
const events = require('events');

// ideja je da napravimo nasu klasu koja nasledjuje EventEmitter klasu iz modula
class SweerEmitter extends events.EventEmitter {

    constructor(maxNumOfSweets){
        super(); // ne zaboravimo konstruktor nadklase
        this.maxNumOfSweets = maxNumOfSweets;
        this.numOfServedSweets = 0;
    }
}

const sweetEmitter = new SweerEmitter(3);

// cesto se ove 'handler' funkcije za dogadjaje ovako izdvajaju da bi se posle lakse baratalo sa njima
// npr u kodu ispod, ako je izdvojena mozemo lako da prestanemo da osluskujemo
// za jedan dogadjaj moze da se registruje vise ovakvih funkcija
const newSweetHandler = (sweetName) => {
    console.log(`${sweetName} is served!`);
    sweetEmitter.numOfServedSweets++;
    if(sweetEmitter.numOfServedSweets === sweetEmitter.maxNumOfSweets){
        // ovako emitujemo neki dogadjaj
        sweetEmitter.emit('enoughSweets');
    }
}

// nasem objektu mozemo da kazemo da osluskuje neki dogadjaj pomocu .on()
// prosledjujemo ime dogadjaja i funkc koja se poziva kada se dogadjaj desi
sweetEmitter.on('newSweet', newSweetHandler);

// NOTE: prvi argument emit-a je naziv dogadjaja a ostali ocpioni argumenti su argumenti za callback funkciju
// koja se poziva kada se dogadjaj registruje. Primeti da mora da se poklapa, npr ispod emit newSWeet salje jedan argument
// pa callback za to mora i da primi jedan arg, a emit enoughSweets ne salje nikakav dodatni argument tako da callback
// za to ne sme da ima argumente 

sweetEmitter.on('enoughSweets', () => {
    console.log("we cant serve any more");
    // ovako kazemo da treba da prestane da se osluskuje za neki dogadjaj
    sweetEmitter.removeListener('newSweet', newSweetHandler);
});

sweetEmitter.emit('newSweet', 'chocolate');
sweetEmitter.emit('newSweet', 'cake');
sweetEmitter.emit('newSweet', 'ice cream');  // posle ovog treba da prestane da se osluskuje newSweet
sweetEmitter.emit('newSweet', 'milkshake');  // ovaj nece biti registrovan