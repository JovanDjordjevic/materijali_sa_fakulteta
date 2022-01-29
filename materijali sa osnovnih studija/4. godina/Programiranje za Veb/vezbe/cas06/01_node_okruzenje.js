// glavna razlika u izvrsavanju ja koda u node.js okruzenju i pretrazivacu
// je sto pretrazivaci nude neke stvari koje za njih imaju smisla, web api, DOM api itd...

// ovaj kod bi se najnormalnije izvrsio u pretrazivacu ali ako ga pokrecemo u terminalu
// pomocu node okruzenja, dobbicemo gresku 'document is not defined'
// document se odnosi na samu web stranicu na kojoj se ovaj js kod izvrsava
// u tom slucaju, global this objekat ima svojstvo document
        // const p = document.createElement('p');
        // document.body.append(p);

// neko komande koje smo korsitili pre, npr setTimeout nisu same po sebi deo JS
// ali ako imaju smisla da se izvrsavaju bez same web stranice (?) onda ce moci da se koriste u node
// npr fetch() nema smisla da se korsiti u node, a setTimeout moze
// npr u node-u (i chrome-u i raznim pretrazivacima), postoji ugradjena virtuelna masina (zove se v8) koja sluzi za zvrsavanje
// js koda. Ona je implementirana u c++

// mozemo da hvatamo argumente koje prosledimo u komandnoj liniji kada pokrenemo program
const name = process.argv[2]    
// podrazumevano argv[0] je apsolutna putanja do samog node.exe
// a argv[1] je samo ime naseg scripta, tj njegova apsolutna putanja
console.log(process.argv);
console.log(`hello ${name}`);    // pokrecemo kod sa npr:   node 01_node_okruzenje.js neki_argument

// mozemo da dohvatimo process ID
console.log(process.pid);

// env nam daje spisak svih promenljivih okruzenja (envirnonment variables) koje su definisane na 
// nasem sistemu, npr username, informacije o OS itd... izmedju ostalog ovde imamo i PATH
console.log(process.env);
// recimo da zelimo da pokrenemo nas program na nekom portu. Prvos sto nam pada na pamet je da 
// definisemo neki npr: const port = 5000 i onda  da pokrecemo na njemu. Ovo je okej kada pokrecemo ovako na nasoj masini
// ali lose je ako pokrecemo na nekom serveru jer tamo mozda vec ima nesto na portu 5000 (?)
// umesto toga mozemo da dodamo npr promenljivu PORT u environment (na linuxu moze iz terminala, komanda bude:   export PORT=5000)
// (na windwsu je:  set PORT=5000 ako hocemo da ta promenljiva bude vidjena lokalno, a   setx PORT=5000  ako hocemo da bude vidljiva globalno)
// i onda toj promenljivoj pristupimo iz programa sa:   process.env.PORT

