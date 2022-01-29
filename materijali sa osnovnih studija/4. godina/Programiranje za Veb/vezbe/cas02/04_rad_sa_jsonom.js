const studenti = [
    {
        ime: "Pera",
        prezime: "Peric",
        "ime i prezime" : "Pera Peric",
        indeks: "1/2021",
        predstaviSe : function() {return "Ja sam Pera Peric"},
        upisaoGodinu: true,
        adresa: {grad:"Beograd"}
    },
    {
        ime: "Mika",
        prezime: "Mikic",
        "ime i prezime" : "Mika Mikic",
        indeks: "2/2021",
        predstaviSe : function() {return "Ja sam Mika Mikic"},
        upisaoGodinu: false,
        adresa: {grad:"Novi Sad"}
    }
]

// od niza objekata mozemo da dobijemo json format ovako
// priemtimo da svojstva koja su funkcije NECE biti serijalizovane
console.log(JSON.stringify(studenti));

let JSONstring = JSON.stringify(studenti);

//deserijalizacija json reprezentacije u js objekte:
console.log(JSON.parse(JSONstring))



// ovo nadalje nije za json

const student1 = 
    {
        ime: "Pera",
        prezime: "Peric",
        "ime i prezime" : "Pera Peric",
        indeks: "1/2021",
        predstaviSe : function() {
            return this["ime i prezime"];             //sa this mozemo da referisemo na objekat iz koga se metod poziva i odatle da uzmemo neke vrednosti
        },
        upisaoGodinu: true,
        adresa: {grad:"Beograd"}
    }
;
console.log(student1.predstaviSe());



// mozemo funkc da definisemo i van objekta
function predstaviSe()
{
    return this["ime i prezime"];
}
// i onda to da dodelimo u objektima

const studenti2 = [
    {
        ime: "Pera",
        prezime: "Peric",
        "ime i prezime" : "Pera Peric",
        indeks: "1/2021",
        predstaviSe : predstaviSe,
        upisaoGodinu: true,
        adresa: {grad:"Beograd"}
    },
    {
        ime: "Mika",
        prezime: "Mikic",
        "ime i prezime" : "Mika Mikic",
        indeks: "2/2021",
        predstaviSe,
        upisaoGodinu: false,
        adresa: {grad:"Novi Sad"}
    },
    {
        ime: "Steva",       // neki treci koji nema predstavi se
        prezime: "Stevic",
        "ime i prezime" : "StevaStevic",
        indeks: "3/2021",
        upisaoGodinu: false,
        adresa: {grad:"Novi Sad"}
    }
]

// npr hocemo da iteriramo kroz sve objekte iz niza i da se svako prestavi ako ima to svojstvo
// studenti2 je niz pa mozemo kroz elemente sa for-of
for(const student of studenti2)
{   
    // kada nebi postojala ova provera, nebi dobili undefined nego gresku!
    if("predstaviSe" in student)
    {
        console.log(student.predstaviSe());   // primetimo da se poziva isto kao da je bio u objektu!
    }
}