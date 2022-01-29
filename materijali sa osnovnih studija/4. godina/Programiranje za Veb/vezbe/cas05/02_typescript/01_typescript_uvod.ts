//promenljive se uvode i ovde sa var/let/const
//tip se navodi ovako sa :
// tsc ovo prevodi tako sto samo izbaci tip
let broj:number = 5;
console.log(broj);


// NOTE: ova dodela ispod nije validna u TS, ali posto to nije zapravo JS greska, tsc ce nam ipak napraviti
// dati JS script koji ce se izvrsavati onako kako ocekujemo, tj da se ispise 5 i asdfg
    // a = "asdfg";
    // console.log(a);

// ako ne navedemo tip, prilikom deklaracije, podrazumevano ce dobiti tip 'any'
let variable = 5;    //  -->  let variable:any = 5;


// u JS nemamo enumeratore, ali imamo u TS
// tsc ovo prevodi u neku samopozivajucu funkciju , vidi izlaz
enum TipPrevoza{
    Automobil,
    Autobus,
    Tramvaj,
    Ostalo
};

// podrazumevano elementi enuma su brojevi tako da mozemo da kazemo prevSredstvo = 0  npr
// ali naravno ovo ne treba tako da se radi 
let prevSredstvo:TipPrevoza = TipPrevoza.Automobil;
console.log(prevSredstvo);


// TS uvodi i unije
// tsc ovo prevodi tako sto ignorise ovo iza :
let unija:boolean | number;
unija = true;
unija = 5;
//  u = "asd";     -> ovo nije validno
console.log(unija);


// nizovi
// tsc ignorise i ovo boolean[]
let niz:boolean[] = [true, false];


// parametrima funkcije mora da se navede tip. funkciji se tip povratne vrednosti
// navodi na kraju  (tsc u prevodu i ovde samo ignorise tipove)
// ako funkcija nema povratni tip, pisacemo :void
// ako hocemo da neki parametar bude opcioni, navodimo sa ?  (ako se ne prosledi bice undefined)
// mozemo da zadamo i da parametar ima defult vrednost, npr pisali bi:    ... c:number = 0 ... 
function avg(a:number, b:number, c?:number) :number {
    let total:number;
    let count:number;

    // === operator postoji i u TS iako ovde bas nema neku funkciju jer vec svemu znamo tip
    if(typeof c === 'undefined'){
        total = a + b;
        count = 2;
    } else {
        total = a + b + c;
        count = 3;
    }

    return total / count;
}

console.log(avg(3, 4, 5));
// console.log(avg(3, 4));    ovo narvno nece raditi ni u TS ni u JS