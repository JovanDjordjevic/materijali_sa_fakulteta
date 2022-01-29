let obj = {
    x: 10,
};

let arr = [1, 2, 3];
 
// posto nemamo klase i nasledjivanje i u JS nekako nebi ni ocekivali da poziv toString() za ovaj nas 
// objekat i niz ispisuju bilo sta, ali ispostavlja se da ispisuju. To je zbog koncepta prototipa
// kada pozivamo neki metod, prvo se proverava da li on postoji bas u objektu, a ako ne postoji gleda
// se da li postoji u prototipu objekta
console.log(obj.toString());   // ispisace [obejct Obejct]
console.log(arr.toString());   // ispisace 1, 2, 3

// ovako mozemo dohvartiti prototip nekog objekta, tu moze da se vidi da on ima neke podrazumevane metode
// kao to je toString()
// NOTE: na vezbama asistentkinja pokrece ovaj kod iz konzole u pretrazivacu
// ja kada pokrenem ovo u VS code terminalu uopste ne dobijam isti ispis!
// isto vazi i za sve prototipove itd nadalje. Svi komentari se odnose na ono sto se zapravo desavalo na vezbama, a ne na moj ispis iz VS code 
console.log(Object.getPrototypeOf(obj))   // typeof prototipa je 'object'

console.log(Object.prototype)
console.log(Object.getPrototypeOf(obj) === Object.prototype)  // ispisuje true

// probamo da vidimo sta je prototip prototipova
console.log(Object.getPrototypeOf(Object.prototype))    // ispisuje null   (null je takodje objekat i on sedi na vrhu 'hijerarhije' objekata u JS)
// null je prototip za sve, on je prototip od Obejct.prototype, a Object.prototype je prototip za neki nas objekat


function Stvar(ime, boja){
    this.ime = ime;
    this.boja = boja;
    this.info = function(){
        return `${this.ime} ${this.boja}`;
    };
}

const s1 = new Stvar("telefon", "beli");
const s2 = new Stvar("solja", "crna");

console.log(typeof s1);   // object 
console.log(s1 instanceof Stvar); // true
console.log(Object.getPrototypeOf(s1) === Object.getPrototypeOf(s2));  // true


console.log(s1.prodavnica); // undefined
console.log(s2.prodavnica); // undefined

// recimo da u oba objekta dodamo neko novo svojstvo (umesto da za oba kucamo s1.nesto = ...)
// to radimo tako sto to svojstvo dodamo u njihov zajednicki prototip
console.log(Stvar.prototype);
Stvar.prototype.prodavnica = "Neka prodavnica";
// ovos to smo sad uradili se zove 'augmentacija prototipa'. Moze da se radi i za fuknkcije 

// NOTE: ako pokusamo da ispisemo objekat samo sa console.log(s1), necemo videti ovo novo svojstvo koje smo dodali u prototip
console.log(s1.prodavnica);  // ovde se vidi prodavnica
console.log(s2.prodavnica);  // ovde se vidi prodavnica


console.log('---------------------------------')
// sve sto mozmeo da dodamo u prototip mozemo i da pregazimo da bude nesto drugo  ('gazenje prototipa')
console.log(Stvar.prototype);
Stvar.prototype = {
    prodavnica: "Neka prodavnica"
};
console.log(Stvar.prototype);

// kada ovako nesto uradimo, samo objekti napravljeni nakon promene prototipa ce imati odgovarajuca svojstva (?)
// dakle s1 i s2 ce imati svoje prototpove, ali ovaj s3 ce biti napravljen sa novim
// (note: u ovom kodu, iznad je vec rucno dodata prodavnica pa ce se zato videti u s1 i s2)
const s3 = new Stvar("stolica", "plava");
console.log(s3.prodavnica)

// kada pregazimo prototip, gubimo svojsvtvo 'constructor' (osim ako ga sami ne navedemo)
// a to svojstvo sluzi za poredjenje u instanceof

// NOTE:  na vezbama je pokazala i pristupanje prototipu objekta sa npr s1.__proto__ 
// ali je rekla da ovo ne treba da se radi zato sto __proto__ nije u standardu (?) tj ni ne mora da bude implementirano (?)


console.log('---------------------------------')
console.log(s1.toString()) // ispisace se onaj podrazumevani iz prototipa


// nacin kako da proverimo da li neko svojstvo dolazi iz prototipa ili je bas definisano u objektu
console.log(s1.hasOwnProperty('toString')); // false
console.log('toString' in s1);              // true
// razlika je u tome sto 'in' proverava da li se svojstvo nalazi bilo gde u hijerarhiji prototipova naseg objekta,
// dok hasOwnProperty gleda da li je bas definisano u objektu

console.log(Object.getPrototypeOf(s1)); // s1 je objekat koji se konstruise preko funkcije Stvar

// da bismo proverili da li je nesto prototip necega moramo da pozovemo nad objektima koji perdstavljaju prototipove (?)
// psoto je funkcija Stvar prototip od s2, to bismo proveravali na sledeci nacin:
console.log(Stvar.isPrototypeOf(s2));  // false    (???)


console.log('---------------------------------')
// recimo da hocemo da napravimo nei objekat sa nekim odredjenim prototipom
// ovo je nas prototip objekat
let protoZec = {
    govori(recenica){
        console.log(`Ovaj ${this.tip} zec kaze ${recenica}`);
    }
}

// Obejct.create pravi objekat po prosledjenom prototipu
let tuzniZec = Object.create(protoZec);
// naravno moramo da definisemo i tip zeca da bismo mogli da koristimo onaj metod iz prototipa
tuzniZec.tip = "tuzan";

tuzniZec.govori("nema vise sargarepe :(");