// u ovom primeru demonstriramo kako se prave nasi objekti gresaka i kako se barata njima

let error = new Error('desila se greska');
// console.log(error);


// u JS imamo try catch blok
try{
    // mozemo da se oslocnimo na vec ugradjeno ispaljivanje greske, kao npr ova linija ispod
    // console.log(nedeklarisana_promenljiva); 

    // mozemo i rucno da ispalimo neku gresku (ugradjenu ili nasu)
    // throw ReferenceError;
    //throw error;
} catch(e){
    // u catch se obicno radi neka analiza po tipu greske, npr:
    if (e instanceof ReferenceError)
    {
        //...
    }
    console.log(e.name);
    console.log(e.mesage);
    console.log(e.stack);
}


// mozemo da extendujemo neku error klasu i da je dopunimo kako zelimo
class FormatError extends Error
{
    constructor(...params){
        super(...params);
        this.time = new Date();
    }
}


try{
    const s = "hello!";
    if(s[0].toLocaleLowerCase() == s[0])
    {
        throw new FormatError("wrong format")
    }
} catch(e){
    console.log(e.name);
    console.log(e.mesage);
    console.log(e.stack);
}