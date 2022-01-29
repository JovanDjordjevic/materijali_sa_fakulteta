'use strict';

// ovde vidimo neke 'tihe greske' tj previde na koje JS engine ne reaguje
// koristimo 'use strict' mod da nas obavesti o ovakvim greskama, on moze da se pise na pocetku fajla (ovo je najbolje)
// negde u sred fajla (onda vazi od tog trenutka nadalje) ili u okviru funkcije (vazi samo u opsegu funkcije)

// ako ne koristimo var/let/const prilikom deklaracije promenljive, striktni rezim ce izbaciti gresku
x = 10;
console.log(x);


// funkcija koja gazi vrednsot u globalnom opsegu
// let i = 23;
// function print_numbers(n){
//     for(i=0; i<n; i++){
//         console.log(i);
//     }
// }
// print_numbers(6);
// console.log(i);


// ako navedemo duplo parametre u funkciji, strict ce da nas spreci
// (ako enmao strict, ovde ce drugi  argument da pregazi vrednost prvog i ispis ce biti 10)
var b = 5;
function f(a, a, c){
    return a + b + c;
}
console.log(f(1,2,3));



// ako napravimo objekat kom je neko svojstvo read-only, tj writeable=false
// linija obj.x nece imati nikakvog efekta, ali to je sigurno previd programera koji je to napisao
// i strict mode ce da nas obavesti o tome
let obj = {}
Object.definePropertiey(obj, 'x', {
    value: 5,
    writeable: false     //    <==
});
console.log(obj.x);
obj.x = 10      //    <==
console.log(obj.x);