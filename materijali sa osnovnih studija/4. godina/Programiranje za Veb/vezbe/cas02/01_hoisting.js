// u js ovo da prvo stampamo pa onda definisemo promenljivu nece dati gresku,
// js prolazi 2 puta kroz kod, prvo jednom da vidi deklaracije promenljivih (samo za var promenljive)
// (ne na inicijalizacije) pa onda jednom za sve ostalo. To se zove "hoisting"
// hoisting NE RADI za let i const deklaracije
// ovo mozeom da zamislimo kao da je kod pretocen u ovo:
// var x;
// console.log(x);
// x=5;
// (naravno, ako ispod ovog console.log() u kodu nemamo deklaraciju x, dobicemo gresku)
console.log(x);  // ispis ce biti undefined vrednost, ali nece dati gresku
var x = 5;


// slicno i za funkciju, okej je da je prvo negde pozovemo pa da 
// posle imamo deklaraciju funkcije, tj imamo hoisting i za funkcije
printName("Beans")
function printName(name){
    console.log(name)
}

// kada pravimo funkcijski izraz, hoisting ne radi, prvo ce se izdvojiti deklaracija za printName
// tj videce se kao promenljiva, a ne kao funkcija, pa cemo dobiti error da prontName nije funkcija 
// kada pokusamo da pozovemo 
// printName("Beans")
// var printName = function printName(name){
//     console.log(name)
// }


// hosting radi na nivou svakog opsega, i u globalnom i u nekom bloku,
// ovde cemo u ispisu za c videti 3,4,undefined posto ce ova funkcija 
// videti c iz svog opsega, a ne onu globalnu koja je deklarisana ispod
function f(a,b){
    console.log(a);
    console.log(b);

    console.log(c);
    var c = 5;
    var a = 11; // ovo ce da se hoistuje ali nece biti undefined ispis jer se prosledjuje 3 kao argument za 'a' (?)
}

var c = 10;
f(3,4);


// NOTE: kada se desava hoisting, redosled kojim deklarisemo ce da se ocuva