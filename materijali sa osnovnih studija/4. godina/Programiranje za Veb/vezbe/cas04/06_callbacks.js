const simplePrint = (message) => { console.log(message); }
const prettyPrint = (message) => { console.log(`*~*${message}*~*`); }

// funkcije mogu da budu argumenti drugih funkcija
const showMessage = (a, b, callback) => {
    const result = a + b;
    if (result > 10) {
        callback(result);
    } else {
        simplePrint(result);
    }
};

showMessage(2, 1, prettyPrint);

//----------------------------------------------------

const message = 'Hello there';

function second() {
    console.log(message);
}

function first(){
    const message = 'Hi there';
    console.log(message);

    second();

    function third(){
        console.log(message);
    }

    third();
}


first();   // ispis ce biti:   Hi there     Hello there    Hi there
           // za svaku funkciju odrzava se kontekst izvrsavanja, tj objekat koji cuva vrednost this reference
           // koja vodi racuna sta je scope te funkcije itd   (vidi sliku u folderu)



//----------------------------------------------------

// ostvarivanje asinhronosti
// priemtimo da ce redosled ispisa ovde biti: start end hello
console.log('start');
// timeout, prvi arg je funkcija koja se poziva posle nekog vremena
// drugi arg je vreme cekanja u milisekundama
setTimeout( ()=>{console.log("hello!");} , 2000 );
console.log('end');

// asinhrone funkcije se ne izvrsavaju paralelno vec postoji event loop u koji se smeste posle
// odredjenog vremena (?)

// kada je timeout trajanje =0, opet cemo dobiti isti ispis iako mozda deluje logicno da ce redosled
//biti start hello end. Detaljnioje ce se o ovome pricati na predavanjima, 
// ali sustina je da je sam poziv setTimeout asinhron (?) i tu mora da se prebaci iz nekog konteksta makrozadataka
// na kontekst mikrozadataka (?)
console.log('-start');
setTimeout( ()=>{console.log("-hello!");} , 0 );
console.log('-end');