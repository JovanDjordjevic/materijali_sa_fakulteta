import { Injectable } from '@angular/core';
import { IJwtTokenData } from '../models/jwt-token-data.model';

// implementiramo servis koji ce da radi neke operacije sa json web tokenima
// konkretno set i get za token , brisanje iz local storagea, izvlacenje podataka iz samog tokena
// da bi transformisali tok moramo nekako iz tog tokena da izvucemo stvari koje su nam relevantne (tj iz payloada tokena izvucemo sta nam treba)
// taj token bi trebalo negde i da sacuvamo (?). Imamo 2 opcije, prva je da cuvamo u okviru ove klase kao polje klase, sto je lose
// druga je da koristimo Storage API koji nam nudi svaki (?) web pregledac. Storage api nam omogucava da cuvamo podatke u samom pregledacu
// i to na nivou sesije (dok se pregledac ne zatvori) ili trajno/lokalno (na racunaru, dostupno i nakon sto se pregledac zatvori)

@Injectable({
  providedIn: 'root'
})
export class JwtService {

  // izdvojili smo ga ovako jer se ponavljao dole 2 puta
  private static readonly USER_TOKEN_ID = 'USER_JWT_TOKEN';

  constructor() { }

  public setToken(jwt:string) : void {
    // imamo vec ugradjenu globalnu promenljivu localStorage
    // metod setItem prima kljuc(tj ime) promenljive koju hocmeod a psotavimo u nasem local storageu i njenu vrednost
    localStorage.setItem(JwtService.USER_TOKEN_ID, jwt);
  }

  public getToken() : string {
    // bice null ako ne postoji u local storageu
    const token: string | null = localStorage.getItem(JwtService.USER_TOKEN_ID);

    if (!token) {
      return '';
    } else {
      return token;
    }
  }

  public removeToken(): void {
    localStorage.removeItem(JwtService.USER_TOKEN_ID);
  }

  // vidi an dnu sta je ovaj return tip
  public getDataFromToken() : IJwtTokenData{
    const token = this.getToken();

    // token je oblika eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c
    // tj nesto.nesto.nesto i to odgovara    header.payload.signature
    // nama treba ovaj payload deo pa splitujemo nisku i uzimamo drugi elem niske
    const payloadString : string = token.split('.')[1];
    
    // taj string koji smo izvukli je neki json koji moramo da deserijalizujemo
    // posto je sifrovan moramo nekako da ga desifrujemo pa tek onda da radimo serijalizaciju
    // funkc za desifrovanje je ugradjena i zove se atob()
    const userDataJson : string =  atob(payloadString);

    // i sad mozemo deserijalizaciju
    // ono sto parse vrati je neki objekat. Pravimo model za taj objekat (vidimo na serveru sta se sve tacno stavlja u payload)
    const payload : IJwtTokenData = JSON.parse(userDataJson);

    return payload;
  }
}
