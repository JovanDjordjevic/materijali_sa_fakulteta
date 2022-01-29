import { Component, OnInit } from '@angular/core';
// dodali ovo:
import { User } from 'src/app/models/user.model';

@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {
  // Kada smo generisali komponentu, ovde je bilo samo ovo pod komentarom
  // constructor() { }

  // ngOnInit(): void {
  // }

  // u okviru ove klase treba za pocetak da definisemo svojstva relevantna za korisnika (posto je ovo user profile komponenta)
  // ali to raditi ovde vec posto su to nekako povezani podaci vezani za jednog korisnika, napravimo novu klasu (User) koja ce se generalno nazivati 'model'
  // pravimo folder gde cemo drzati modele, i nazivacemo ih ovako:    ime.model.ts
  // imacemo modele i na serveru i na klijentu i to ce se korsititi za preslikavanje (?), za sada ne spajamo nista, nego samo pravimo klijent
  // tamo napravimo klasu i eksportujemo je i onda ovde mozemo da je kristimo
  user: User;

  // ovo je neko polje koje smo uzeli za primer za vezivanje dogadjaja, hocemo da u onoj formi nesto bude enabled/disabled
  // zajedno sa funkciom onChangeInfo() ispod
  // ovo disabled field je iz semantic UI bilioteke
  inputFieldClass: string = "disabled field";

  constructor() { 
    this.user = new User("Pera Peric", "pera@gmail.com", "/assets/default-user.png");
  }

  ngOnInit(): void {
  }

  onChangeInfo() {
    // kada se klikne na dugme, desava se dogadjaj 'click', pozvace se ova funkcija koja ce izmeniti vrednost u modelu
    // od koje zavise oni input elementi u sablonu, tj njihovi atributi koji su vezani za kod
    this.inputFieldClass = "field"; // ovo je obicno polje na koje moze da se klikne
  }

  onSaveChanges() {
    this.inputFieldClass = "disabled field";
    // npr ove bi bilo slanje nekog  zahteva na serveru ako bi postojalo
  }

  // NOTE: event koji ce nam se poslati iz html-a mora da se navede ovde sa tipom Event
  onChangeName(event: Event) {
    // kada odstampamo event objekat videcemo da ima razna neka svojstva
    // console.log(event);

    // iz target mozemo da izvucemo value, ali ne mozemo samo da napisemo event.target.value zato sto TS ne zna ovde iz kog tacno elementa je ispaljen dogadjaj
    // change dogadjaj moze da se izvrsi na vise razlicitih html elemenata, pa je potrebno da ga kastujemo u HTMLInputElement i tek onda mozemo iz njega da 
    // izvucemo vrednost iz njega
    const name = (event.target as HTMLInputElement).value;
    this.user.name = name;
  }

  onChangeEmail(event: Event) {
    const email = (event.target as HTMLInputElement).value;
    this.user.email = email;
  }
}
