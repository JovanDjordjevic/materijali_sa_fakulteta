// ovo je common JS nacin
// ovo ce da bude neki modul (kao neka bibliotekica) gde imamo neke funkcije
// da bi naglasili da nesto treba da se vidi i izvan samog modula koristimo exports
// tj mi ovde imamo neki 'exports' objekat i njemu pridruzujemo neke nase funkcije/vrednosti/klase
// exports je objekat koji predstavlja interfejs samog modula
exports.add = (a, b) => a + b;
exports.mul = (a, b) => a * b;
exports.PI = 3.14;


// jos jedan nacin je da ih definisemo najnormalnije i onda na kraju da exportujemo
const add_numbers = (a, b) => a + b;
const multiply_numbers = (a, b) => a * b;
const PI = 3.14;

// obavezno mora da se napise module.   da bi se pregazio exports objekat iz module interfejsa,
// ako samo stavimo exports, to je skroz drugi objekat
// NOTE: ovo sada sto smo napisali smo zapravo pregazili exports objekat koji smo modifikovali u one prve tri linije skroz gore
// tj poslednji exports u fajlu je relevantan ako ima vise ovakvih
module.exports = {
    add: add_numbers,
    mul: multiply_numbers,
    PI: PI
};