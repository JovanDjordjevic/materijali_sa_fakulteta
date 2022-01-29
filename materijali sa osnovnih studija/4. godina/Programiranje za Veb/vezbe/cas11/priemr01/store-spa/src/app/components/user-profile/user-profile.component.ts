// izbrisani komentari od proslog casa

import { Component, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { User } from 'src/app/models/user.model';

@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {
  user: User;

  shouldDisplayUserForm: boolean = false;

  addresses: string[] = ['Street 1', 'Street 2', 'Street 3'];

  orderNumber: number = 1; 

  // za rekativne formulare
  // NOTE: ovde smo u formular dodali polje sa username tako da je potrebno da to dodamo i u User klasu   user.model.ts
  userForm: FormGroup;

  //DRUGI NACIN:
  // Postoji jos jedan nacin da se instancira userForm, a to je preko FormBuildera, to je jedan od servisa koji nam nude rekativni formulari
  // ako zelimo da ga korsiti nasa komponenta user-profile, moramo u ovde u konstruktoru da ubrizgamo taj servis
  // tj da ga prosledimo kao argument korisniku. Ako je servis vec negde koriscen u aplikaciji pre ovoga, angular ce se postarati da mi ovde dobijemo
  // bas taj vec korisceni objekat, a u suprotnom ce se za nas napraviti novi u pozadini
  constructor(private formBuilder: FormBuilder) { 
    this.user = new User("peraperic", "Pera Peric", "pera@gmail.com", "/assets/default-user.png");

    //PRVI NACIN:
    // u konstruktoru moramo da inicijalizujemo userForm  (ako ga stavimo u ngOnInit dobicemo gresku)
    // konstruktor za FormGroup mora da primi objekat koji ima svojstva koja se zovu isto kao input polja u htmlu
    // svako polje u formularu mora da bude predstavljeno kao instanca klase FormControl, konstruktor za to prima
    // inicijalnu vrednost tog polja (ono sto ce biti po defaultu prikazano u formularu), drugi arg je opcioni i to je niz validatora
    // validatori su funkcije koje ce proveravati da li je vrednosti ispravna. Implementiracemo ih negde dole  ( a mozemo i da korsitimo
    // neke koji su vec ugradjeni za neke common stvari) a onda samo ovde proslediti u niz
    // na nivou formulara cemo imati polje valid  (slicno kao value, vidi u funkciji ispod) koje ce biti true samo ako prodje sva validacija
    this.userForm = new FormGroup({
      // NOTE: primetimo da ovaj za pattern 'pozivamo' sa argumentom a treba nam referenca na funkc kao za required. 
      // Ono sto se za validatore sa argumentima desava u pozadini je da se pri ovom pozivu interno konstruise validatorska funkcija koja bas proverava za to
      // sto hocemo a onda se iz nje vrati referenca na taj novi validator
      username: new FormControl(this.user.username, [Validators.required, Validators.pattern(new RegExp("[a-zA-Z0-9_-]{8,}"))]),
      email: new FormControl(this.user.email, [Validators.required, Validators.email]),
      name: new FormControl(this.user.name, [Validators.required, Validators.minLength(2)]),
      imgUrl: new FormControl(''),
    });

    // DRUGI NACIN(nastavak)
    // pravimo nas formular pomocou group() metoda, i ovde je argument objekat koji ima svojstva koja se zovu kao
    // u samom formularu u htmlu, samo se prave drugacije. Vrednost im je niz gde je prvi element inicijalna vrednost
    // a drugi element je onaj niz validatora
    // Koristicemo i ovaj pristup negde drugde
          // this.userForm = this.formBuilder.group({
          //   username: [this.user.username, []],
          //   analogno za ostale...
          // })
  }

  ngOnInit(): void {
  }

  // metod koji se poziva kada se desi ngSubmit dogadjaj na dugme
  onUserFormSubmit() {
    // da bismo dohvatili koristimo value nad nasim formularom. Polja ce biti bas ona koja userForm ima
    // a vrednosti ce biti ono sto je u tom trenutku poslato u formularu
    const data = this.userForm.value;
    // console.log(data);

    // imamo i polje valid koje ce biti true samo ako su ispunjeni svi uslovi validatora
    // isto i polje invalid
    // posle u product formularu cemo da pokazemo kako se iz ovoga izvlaci i informacija sta tacno nije validno
    if(this.userForm.invalid) {
      window.alert('Form is not valid!');
      return;
    }

    // i sad dalje radimo sta god hocemo sa podacima, npr zelimo da izmenimo podatke iz naseg user polja
    this.user.username = data.username;
    this.user.name = data.name;
    this.user.email = data.email;

    // brisanje polja iz inputa iz  formulara nakon izmena se radi sa reset(), ALI pazimo da ako samo pozovemo reset() bez argumenta, 
    // vrednosti u formularu ce biti prazne, ali ne u smislu prazne niske nego bas NULL sto mozda ne zelimo (?)
    // ako zelimo da resetujemo tako da inputi imaju neke konkretne vrednosti, prosledjujemo objekat
    this.userForm.reset({
      username: '',
      name: '',
      email: '',
    });  

    this.onSaveChanges();
  }

  getColor(paranIndeks: boolean) : string {
    return paranIndeks ? "black" : "gray";
  }

  onChangeInfo() {
    this.shouldDisplayUserForm = true;
  }

  onSaveChanges() {
    this.shouldDisplayUserForm = false;
  }

  onChangeName(event: Event) {
    const name = (event.target as HTMLInputElement).value;
    this.user.name = name;
  }

  onChangeEmail(event: Event) {
    const email = (event.target as HTMLInputElement).value;
    this.user.email = email;
  }
}
