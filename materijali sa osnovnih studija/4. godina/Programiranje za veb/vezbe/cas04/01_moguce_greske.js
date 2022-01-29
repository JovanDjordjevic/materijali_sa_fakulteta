// ovde samo pokazujemo 5 predefinisanih gresaka koje mogu da se jave prilikom pisanja JS koda

console.log(promenjiva);         // reference error, koristimo promenljivu koja nigde nije deklarisana


const x = 10;
x();        // type error - pogresan nacin koriscenja promenljive
console.log(x.name)   // isto


const f = (a,b) => a + b;
f(2 3);   // syntax error, fali nam zarez


//u js imamo funkciju toString() koja broj prebacuje u stringovnu reprezentaciju
// ali jos imamo opcioni argument da prosledimo brojevni sistem (maksimalni je sa osnovom 36)
// ovo ce da odstampva 42 u binarnom sistemu
console.log((42).toString(2));
// range error - u drugim jezicima to je obicno kada pristupamo elementu niza koji nije u nizu
// ali posto je to validno da se radi u JS, ovde se range error odnosi na nesto drugo
console.log((42).toString(50));  // range error - argument funkcije je u pogresnom opsegu


// necemo sada demonstrirati ali mogu da nastanu greske prilikom parsiranja URI-ja
// tj URI encode error i URI decode error 