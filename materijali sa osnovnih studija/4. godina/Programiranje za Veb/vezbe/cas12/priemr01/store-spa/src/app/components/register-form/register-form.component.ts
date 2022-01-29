import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { Observable, Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-register-form',
  templateUrl: './register-form.component.html',
  styleUrls: ['./register-form.component.css']
})
export class RegisterFormComponent implements OnInit, OnDestroy { // ne zaboravimo da dodamo OnDestroy

  registrationForm : FormGroup;
  sub : Subscription;   // vidi ispod sta je ovo
                        // cesto moze da se desi da u jednoj komponenti imamo vise subscriptiona, u tim slucajevima mozemo da imamo i niz ovih

  // ubrizgavamo na auth servis
  constructor(private auth : AuthService) { 
    this.registrationForm = new FormGroup({
      username : new FormControl('', [Validators.required, Validators.pattern(new RegExp("[0-9a-zA-Z_-]+"))] ),
      password : new FormControl('', [Validators.required, Validators.pattern(new RegExp("[0-9a-zA-Z!@#$%^&*()_+-=]+"))]),
      name : new FormControl('', [Validators.required]),
      email : new FormControl('', [Validators.required, Validators.email]),
    });

    this.sub = new Subscription;
  }

  ngOnInit(): void {
  }

  // slicno kao za ngOnInit, mozemo da reagujemo i na ngOnDestroy, sto se poziva kada se ova komponenta unisti
  // moramo samo u liniji iznad pored implements OnInit da dodamo i OnDestroy, i to je interfejs
  ngOnDestroy() : void {
    // vidi ispod komentar zasto ga radimo ovde
    this.sub.unsubscribe();
  }


  register(){
    if (this.registrationForm.invalid) {
      window.alert('Form is not valid');
      return;
    } 

    const data = this.registrationForm.value;
    const obs : Observable<User> = this.auth.registerUser(data.username, data.password, data.name, data.email);

    // ovde moramo rucno da radimo subscribe, a ne sa  | async kao u html-u
    // subscribe kaci jednog pretplatnika na tok. Pretplatnik je funkcija koja ce da se pozove kada tok emituje vrednost
    // Argument ove funkcije mora da bude tipa koji tok emituje, ovde je to User
    // subscribe metod vraca objekat tipa Subscription. Moramo da ga cuvamo zato sto u nekom trenutku nad njim moramo da korsitimo metod unsubscribe
    // subscription se uglavnom prekida pri unistavanju objekta. Nije dobro da ovde ispod odmah stavimo unsubscribe zato sto tok na koji subscribujemo
    // emituje vrednosti asinhrono. Vidi gore ngOnDestroy()
    this.sub =  obs.subscribe( (user : User) => {
      console.log(user);
    });
  }

}
