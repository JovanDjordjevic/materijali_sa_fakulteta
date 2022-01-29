class Person {
    constructor(public name:string){}
}

const p = new Person("Pera");

// NOTE: ovo samo po sebi nema smisla u node okruzenju, ali mi hocemo da ovaj TS kod prevedemo u neki JS
// koji cemo da pokrenemo u okviru nekog html-a
document.body.innerHTML = p.name;