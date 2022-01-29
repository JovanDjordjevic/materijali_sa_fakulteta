// pravimo prazan niz
let prazanNiz = [];
console.log(prazanNiz.length);  //length je svojstvo, ne metod

// elementi u nizu ne moraju biti istog tipa
let niz = [-3, 4.5, "niska", BigInt(223556226), {}];
console.log(niz.length);
console.log(niz);

// mozemo niz da prodjemo standarnom for petljom
for(let i=0; i<niz.length; i++)
{
    console.log(niz[i]);    // indeksiranje standardno sa [], krece od 0
}

// imamo jos 2 nacina, for-in petlju i for-of petlju
// for in ne prolazi po elementima nego po indeksima
for(const indeks in niz)
{
    console.log(indeks, '->', niz[indeks]);
}

// for-of proalzi bas kroz elemente nizova, kao for-each petlja na koju smo navikli
for(const el of niz)
{
    console.log(el);
}

// primetimo da kada referisemo indeks koji ne postoji, dobijamo undefined
// nbece nam puci program
console.log(niz[6]);

// sortiranje se radi leksikografski, ispis ce biti [ 10, 17, 23, 46, 5 ]
// to je zato da bismo mogli da poredimo stringove i brojeve
niz = [10, 5, 46, 23, 17];
niz.sort();
console.log(niz);

// kada zelimo bas da sortiramo npr rastuce po vrednsoti
//, moramo da prosledimo i neki komparator
niz.sort((a,b) => a-b);
console.log(niz);

// dodavanje elementa na kraj niza
niz.push(67);
console.log(niz);

// imamo i pop koji izbacuje element sa kraja
// moze i ne mora da se cuva u promenljivoj
let element = niz.pop();
console.log(element, ",", niz);



niz = [1,2,3,4];
console.log(typeof niz);    // vidimo da je tip niza  object
// tj niz je specijalni tip objekta cijim svojstvima mozemo da pristupamo sa [index] (i ima ona neka dodatna svojstva tipa push, pop...)

// konstrukcija praznog objekta
const prazanObj = {};

// neprazan objekat, svako svojstvo objekta je par kljuc:vrednost
// mozemo da kazemo i da su objekti kao lista parova kljuc:vrednost
// svaku kljuc je po defaultu string ali ne mroamo uvek da pisemo "",
// ali moramo kada to nije validni js identifikator, npr mora "ime i prezime" ako je to kljuc
// sve i svasta moze da bude vrednsot svojstva, npr funkcije itd,
// moze cak i vrednost da bude drugi objekat
const student = {
    ime: "Pera",
    prezime: "Peric",
    "ime i prezime" : "Pera Peric",
    indeks: "1/2021",
    predstaviSe : function() {return "Ja sam Pera Peric"},
    upisaoGodinu: true,
    adresa: {grad:"Beograd"}
};

// pristupanje svojstvima
console.log(student.ime);
console.log(student.predstaviSe());
console.log(student["ime i prezime"]);  // NOTE: mora ovako sa [] kada imamo svojstva cija imena nisu validni js identifikatori
                                        // broj nije js identifikator, pa zato mora u nizu da se pristupa elemtima sa []
                                        // u nizu je takodje validno npr niz["1"], to 1 je isto indeks
// sve sto je u [] je neki izraz koji se izracunava pre nego sto pristupimo objektu
console.log(student["ime" + " i " + "prezime"]);

// moze i funkcija
function getRandomAttribute()
{
    if(Math.random() > 0.5) return "indeks";

    return "ime i prezime";
}
console.log(student[getRandomAttribute()]);

// recimo da nekom vec postojecem objektu hocemo da dodamo novo svojstvo
// mozemo samo da ga dodelimo sa .
student.godine = 20;
console.log(student);

// mozemo i da brisemo svojstva, to radimo ovako sa operatorom delete
delete student.godine;
console.log(student);
// ako pokusamo da pristupimo nepostojecem svojstvu/svojstvu koje je izbrisano
// dobijamo undefined
console.log(student.godina);
// to nam se cini da je isto kao da je isto da kazemo student.godine = undefined, ali nije
// delete ga bas brise iz objekta i solobodi memoriju, a = samo postavlja vrednost polja

// operator in oproverava da li neko svojstvo postoji u objektu
console.log("indeks" in student);
console.log("godine" in student);

const indeks = "2/2021";
const studen2 = {
    indeks,     // kada imamo neku pormenljivu od ranije koja se zove isto kao i kljuc svojstva, 
                // mozemo da koristimo ovu skracenu notaciju, ali naravno ispravno je i:   indeks: indeks

};

// sa for-in mozemo da iteriramo kroz kljuceve objekta
for(const kljuc in student)
{
    console.log(kljuc, '->', student[kljuc]);
}

// sa for-of NE mozemo da iteriramo kroz objekat jer nije iterabilan
// for(const el of student)
// {
//     console.log(el);
// }
// tj ovo moze da se radi, ali moramo prvo sami za objekat da definisemo kako se 
// iterira kroz njega, sto po defaultu ne postoji za objekte

//ovako mozemo dobiti sve kljuceve objekta
Object.keys(student);
// ovako mozemo da dobijemo sve parove kljuc:vrednsot, i ovo mozemo da korsitimo
// da iteriramo kroz nas objekat
Object.entries(student);

//NOTE: ovaj deo koda mi baca gresku, debaguj posle casa!
// // nacin da objektu dodamo neka svojstva koja imaju neka specijalna svojstva
// // prvi arg je objekat, drugi arg je ime kljuca, treci je objekat deskriptor
// Object.defineProperty(student, "godine", {
//     enumerable: true,   // svojstvo ce se pojaviti pri iteraciji kroz objekat
//     writable: true,     // da li svojstvo moze da se menja
//     configurable: true,  // da li svojstvo moze da se brise
//     value: 20,          // u okviru deskriptora mozemo da kazemo i koja je vrednost svojstva
//     set: function() { console.log("set: "); },
//     get: function() { console.log("get: "); return 20; }
// });
// // ako definisemo get i set u dektiptoru, kada kazemo npr student.godina, nece se dohvatitis vojstvo nego ce se
// // pozvati ovaj get, i slicno za student.godina=21 nece se samo dodeliti 21 nego ce se pozvati set
// // set i get mozemo da definisemo i unutar samog objekta kao i sva druga svojstva

let a = {x:10};
let b = {x:10};
// kada imamo 2 objekta koji deluju isto i poredimo ih sa === dobicemo false
// prvo ce se na hip memoriji napraviti jedan, pa na steku ce se napraviti promenljiva a koja cuva referencu na taj objekat
// onda ce novi objekat sa istoms trukturom na hipu, pa onda promenljiva b na steku koja cuva referencu na taj drugi objekat
// i onda kada se porede a i b videce se da reference nisu iste, tj objekti su razliciti
console.log(a === b);

// ovo ce biti true jer pokazuju na isti objekat
let c = a;
console.log(a === c);

// psoto c pokazuje na objekat u memoriji na koji pokazuje a, imena u a ce se videti i u c
a.x = 20;
console.log(c)

// u js nemamo bas lep naicn da pravimo kopije objekata, ali mozemo da konstruisemo novi
// obj pa onda da mu dodeljujemo ista svosjtva i vrednsoti kao onaj prvi objekat

// objekti na hipu se brisu kada nema vise referenci koje pokazuju na njih
// pominje termin 'zatvorenje' ali nije bas objasnjeno sta je (mozda je receno prosli cas(?))

function f()
{
    const obj1 = {a:10};
    const obj2 = {b:20};

    // ovo je lose jer i obj1 i obj2 moraju negde da se sacuvaju (?)
    //    return function(){ return obj1.a + obj2.b };
    // ovo je bolje
    let c = obj1.a + obj2.b;
    return c;
}



// funckije sa proizvoljnim brojem parametara
// koristimo `...ime_argumenta`, to je niz preostalih parametara koji
// nisu upali u prethodno nabrojane
function nabrojSve(a, b, ...stvari)
{
    for(let stvar of stvari)
    {
        console.log(stvar);
    }
}
nabrojSve('torba', 'sesit', 'majica', 'pantalone');

// ako imamo neki niz a zelimo da ga 'raspakujemo' tj da svaki element prosledimo
// kao zaseban argument:
let stvariZaPut = ['torba', 'sesit', 'majica', 'pantalone'];
// slicna je sintaksa, raspakuje se sa ...ime
// mozemo da ga navedemo na proizvoljnom mestu
nabrojSve('kupaci', 'punjac', ...stvariZaPut, 'naocare');