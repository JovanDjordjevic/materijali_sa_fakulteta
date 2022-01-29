// da bi koristili neki modul koji smo definisali moramo da njegovu putanju navedemo u require()
// to mozemo sacuvati u okviru neke promenljive i onda iz nje pozivati funkcije

const arithmetics = require('./04_01_arithmetics_module.js');

// pozivanje funkcija
console.log(arithmetics.add(2, 3));
console.log(arithmetics.mul(2, 3));
console.log(arithmetics.PI);


// nismo u obavezi da uvedemo sve iz modula, mozemo da korsitimo dekonstrukciju
//      const {add, mul, PI} = require('./04_01_arithmetics_module.js');
// i onda ih nadalje koristimo kao da su pisane u ovom fajlu:
//      console.log(add(2, 3));
//      console.log(mul(2, 3));
//      console.log(PI);
