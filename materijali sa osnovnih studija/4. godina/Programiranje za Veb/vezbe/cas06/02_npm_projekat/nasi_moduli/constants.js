// ovaj nacin eksportovanja koristimo kada radimo sa node

module.exports.a = 10;
module.exports.b = 5;
// validno je i samo exports.nesto = nesto
// exports.c = 2

// ugradjeni mehanizam u node-u je da kada izvrsavamo neki script, to je kao
// da se on obmota nekom samopozivajucom funkcijom, u nasem slucaju, kao da se desi ovo:
// (function(exports, require, module, __filename, __dirname) {
//     // implicitno se ovde pravi prazan exports objekat
//     // module.exports = {}    
//     module.exports.a = 10;
//     module.exports.b = 5;
// })
// primetimo da se ova samopozivajuca funkcija poziva sa nekim argumentima
//NOTE: primetimo da ce se ove 2 linije izvrsiti kada u main.js dovucemo ovaj modul, slicno kao u pajtonu
console.log(__filename);
console.log(__dirname);