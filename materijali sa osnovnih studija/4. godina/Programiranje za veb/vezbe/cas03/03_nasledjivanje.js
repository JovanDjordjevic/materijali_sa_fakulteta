// posto js nije OOP jezik, nasledjivanje moramo da simuliramo na neki nacin
// jedan od tih nacina je 'lanac prototipova'

// recimo da imamo neke konstruktorske funkcije
function Shape(){
    this.name = "Shape";
    this.toString = function(){
        return this.name;
    }
}

function TwoDShape(){
    this.name = "2D Shape";
}

function Triangle(side, height){
    this.side = side;
    this.height = height;
    this.name = "Triangle";
    this.getArea = function() {
        return this.side*this.height/2;
    }
}

const shape2d = new TwoDShape();
console.log(shape2d.toString());   // dobijamo [object Object] ,to je toString iz Object.prototype
console.log(Object.getPrototypeOf(shape2d));  // vidimo prototip

// prirodno nam se namece da TwoDShape treba da nasledjuje Shape i da Triangle treba da nasledi TwoDShape
// ideja je da se povezu njihovi prototipovi
// primetimo da ne mozemo samo da kazemo   TwoDShape.prototype = Shape  jer je Shape funkcija a prototip mora da bude objekat
// ovo je u sustini gazenje prototipa
// kada pregazimo prototip, gubi se svojstvo 'constructor' pa mozemo sami da ga dodamo da bi mogli da korsitimo instanceof (?)
TwoDShape.prototype = new Shape();
TwoDShape.prototype.constructor = TwoDShape;
Triangle.prototype = new TwoDShape();
Triangle.prototype.constructor = Triangle;

console.log(shape2d instanceof Shape); // vraca false (jer je shape2d napravljen pre povezivanja prototipova)

const newShape2d = new TwoDShape();
console.log(newShape2d.toString());   // sada se poziva toString iz Shape
console.log(Object.getPrototypeOf(newShape2d));  // vidimo da je prototip instanca Shape, kao sto smo podesili

console.log(newShape2d instanceof Shape); // vraca true (jer je newShape2d napravljen posle povezivanja prototipova i podesavanja constructor svojstva (?) (NOTE: nzm jel bag, ali meni ovo ispisuje true i bez podesavanja constructor ali nebi trebalo))

const t = new Triangle(5, 10);
console.log(t.toString());      // ispisuje 'Triangle', kao sto ocekujemo




// DRUGI NACIN:
// od JS 6 psotoji mogucnost da koristimo i kljucnu rec class i da radimo kao da zapravo imamo klase (pazi na sintaksu)
// NOTE: sve ovo je samo syntax sugar, ovde nema nikakve nove funkcionalnosti i voos e u pozadini ponasa isto kao i da smo samo radili
// sa funkcijama kao u prvom nacinu!
class Shape6 {
    constructor() {
        this.name = "Shape";
    }
}

class TwoDShape6 extends Shape6{
    constructor() {
        super();                 // !!!!!
        this.name = "2D Shape";
    }
}

class Triangle6 extends TwoDShape6{
    constructor() {
        super();                      
        // ...
    }  
}

// NOTE: kada radimo ovako, konstruktorske funkcije ne mogu da se pozovu bez new (dakle pored 'use strict' i one if provere koju smo videli u 
// prvom primeru, ovo je treci nacin da se resi ovaj problem)