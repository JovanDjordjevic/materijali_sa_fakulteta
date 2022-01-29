import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class ProductService {

  // u ovaj nas servis ubrizgavamo HttpClient (?)
  constructor(private http: HttpClient) { 

  }

  // treba nam metod koji dohvata stvari sa servera. Ovaj metod nece vratiti objekat koji nam posalje server 
  // vec Observable, to je tok koji sluzi za emitovanje vrednosti. Kada dohvatimo podatke sa server, to se desava asinhrono i ne znamo kada
  // ce odgovor stici
  // kraj casa...
}
