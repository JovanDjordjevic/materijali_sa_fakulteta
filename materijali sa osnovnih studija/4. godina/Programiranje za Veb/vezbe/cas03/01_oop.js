//'use strict'    // ovo ce biti objasnjeno posle (zakomentarisano je da bi se kod preveo)

function dohvatiJezike() {
    return this.jezici;
}

let osobe = [
    {
        ime: "Pera",
        godine: 21,
        jezici: ["srpski", "engleski"],
        zeliSladoled: true,
        dohvatiJezike: dohvatiJezike
    },
    {
        ime: "Mika",
        godine: 24,
        jezici: ["spanski"],
        zeliSladoled: false,
        dohvatiJezike: dohvatiJezike
    }
];

console.log(osobe['0']);


// konstruktorske funkcije su obicne funkcije u javascriptu koje pocinju 
// velikim slovom (to je samo konvencija da bi znali da je konstruktor)
// rade slicno kao konstruktori u OOP koje smo videli do sad
function Osoba(ime, godine, jezici, zeliSladoled)
{   
    // ovo se u sustini ponasa kao da smo ovde na pocetku funkcije napravili
    // prazan objekat:  this = {}

    console.log(this instanceof Osoba)    //ispisuje true, VIDI KOMENTAR ISPOD (*)

    if(!(this instanceof Osoba))                                // (**) kada nemamo 'use strict' ovo je jos jedan nacin da se osiguramo da se pravilno napravi
    {                                                           // objekat ako slucajno zaboravimo 'new'. U prvom pozivu posto nema 'new', ne pravi se this={} i samim
        return new Osoba(ime, godine, jezici, zeliSladoled);    // tim ovaj uslov u if je false i tada se ispravno opet poziva funkcija ali ovaj put posto ima 'new'
    }                                                           // if ce da se ignorise

    this.ime = ime;
    this.godine = godine;
    this.jezici = jezici;
    this.zeliSladoled = zeliSladoled;
    this.dohvatiJezike = dohvatiJezike;
    // i onda kao da ga vratimo na kraju sa  return this;
}


// kontrkutorske funkcije se pozivaju uz kljucnu rec new
// i to radi kako ocekujemo, dobijamo novi objekat
let osobe2 = [
    new Osoba("Pera", 21, ["srpski", "engleski"], true),
    new Osoba("Mika", 25, ["francuski"], false), 
]


// kada  pozovemo konstruktor bez new dobijamo undefined
// Kada funkcija u JS nema na kraju return komandu, po defaulutu ce vratiti undefined
// (a kada je pozovemo sa new, to je kao da postoje one implicnitne 2 linije na pocetku(this = {}) i na kraju (return this))
let osoba2 = Osoba("Pera", 21, ["srpski", "engleski"], true);
console.log(osoba2);
// posto hocemo da se obezbedimo da nam se izbaci nekakva greska 
// kada pokusamo da pozovemo konstruktor bez new, za to mozemo da koristimo 
// 'use strict' na pocetku pograma. On podrazumeva svasta nesto sto nama nije trenutno
// bitno, ali ako sada probamo da pozovemo kosntruktor bez new dobicemo gresku

// NOTE: kada kortstimo this van neke funkcije, zapravo referisemo na 
// 'globalni objekat', i naredne 2 linije su ekvivalente, thj u oba slucaja
// u globalni objekat dodajemo svojstvo 'a' i dajemo mu vrednost 10
// this.a = 10;
// const a = 10;
// dakle ako sad ovo ispisemo, posto smo pozvali Osoba() bez new, sva ona polja su se dodavala na globalni objekat
// jer nije implicitno napravljen novi, i sada globalni objekat ima svojstvo ime="Pera" i to ce se ispisati
//          console.log(ime)

// neka okruzenja (ne znam tacno koja) dozvoljavaju da se globalni objekat dohvata sa globalThis
// console.log(globalThis)

//ako ovo pokrenemo, dohvatice nam se jezici iz glboalnog this objekta
console.log(dohvatiJezike())
// primetimo da funkcija dohvatiJezike u sebi koristi this, 
// ako zelimo da za takve funkcije direktno kazemo koji tacno objekat ce postati this
// tokom izvrsavanja, mozemo da korsitimo apply. Prvi arg je objekat kij treba da postane this
// a ostali arg su argumenti same funkcije (ako postoje)
console.log(dohvatiJezike.apply(osobe[1]));

let osoba3 = new Osoba("Steva", 23, ["spanski"], true)
console.log(typeof Osoba)    // ispisace function
console.log(typeof osoba3)   // ispisace object

// mi u JS nekako simuliramo OOP paradigmu, nemamo mi ovde zapravo klase i isntnace klasa
// ali sa instanceof mozemo kao da proverimo da li je objekat nastao pozivom konstruktorske funkcije
console.log(osoba3 instanceof Osoba)    // ispisace true
// (*) console.log(this instanceof Osoba) u funkciji osoba ispisuje true. Posto pozivamo funkciju sa new, 
//pravi se implicitno onaj prazan objekat i posto je bas napravljen u konstruktorskoj funkciji, zadovoljava
// uslov za instanceof





// nadalje je dodat nov metod u osobu i razlikuje se ponasanje ali me mrzi da razdvajam u vise fajlova
console.log("---------------------------------------------------------------")
function NovaOsoba(ime, godine, jezici, zeliSladoled)
{   
    // if(!(this instanceof Osoba))
    // {
    //     return new Osoba(ime, godine, jezici, zeliSladoled);
    // }                                                          

    this.ime = ime;
    this.godine = godine;
    this.jezici = jezici;
    this.zeliSladoled = zeliSladoled;
    this.dohvatiJezike = dohvatiJezike;

    this.ispisiOceneJezika = function () 
    {   
        // PRVA VERZIJA FUNKCIJE:   
        // this.jezici.forEach(function(jezikE){  // forEach na svakom elementu niza primenjuje funkciju koju mu prosledimo
        //     console.log(`${this.ime} zna jezik ${jezikE.jezik} sa ocenom ${jezikE.ocena}`)
        // });
        // priemtimo sta se desi kada pozovemo console.log(noveOsobe[0].ispisiOceneJezika())
        // ispis ce biti "undefined zna jezil srpski sa ocenom 10". Desilo se da se izgubila referenca na objekat za kog pozivamo metod ispisiOceneJezika
        // ovo se desava zbog zatvorenja (? nadji u skripti objasnjenje sta je ovo ?)
        // Prvi nacin da se ovo resi je da pre poziva forEach napisemo liniju: const self=this; i onda da u ispisu umesto this.ime pisemo self.ime
        // taj nacin nam nekako nije lep, i skoro se nigde ni ne kristi

        // ovaj problem u sustini postoji za sve funkcije koje 'simuliraju' funkcionalnu paradigmu, tj koje primaju druge funkcije kao argumente
        // npr forEach, map itd...

        // drugi nacin je da umesto obicne anonimne funkcije koristimo lambda funkcije
        // one su ubacene od neke kasnije verzije i napravljene su tako da ne vezuju this za svoj kontekst
        // 'this' u lamba funkcijama se zove 'leksicko this'
        this.jezici.forEach((jezikE) => { 
            console.log(`${this.ime} zna jezik ${jezikE.jezik} sa ocenom ${jezikE.ocena}`)
        });
    }
}

// nizovi jezika su sada nizovi objekata
let noveOsobe = [
    new NovaOsoba("Pera", 21, [ 
        {jezik: "srpski", ocena: 10},
        {jezik: "engleski", ocena: 8}
    ], true),
    new NovaOsoba("Mika", 25, [
        {jezik: "francuski", ocena: 9},
    ], false),  //<--                           // NOTE: 'trailing comma' je skroz validna stvar u JS  skriptama (ali ne moze u JSON formatu)
];

console.log(noveOsobe[0].ispisiOceneJezika())