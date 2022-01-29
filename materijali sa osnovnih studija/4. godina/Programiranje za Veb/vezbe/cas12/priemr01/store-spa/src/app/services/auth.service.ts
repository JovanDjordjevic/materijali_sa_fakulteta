import { HttpClient } from '@angular/common/http';
import { THIS_EXPR } from '@angular/compiler/src/output/output_ast';
import { Injectable } from '@angular/core';
import { map, Observable, Subject, tap } from 'rxjs';
import { IJwtTokenData } from '../models/jwt-token-data.model';
import { User } from '../models/user.model';
import { JwtService } from './jwt.service';

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  // za autentifikaciju nam trebaju i neki url-ovi
  // vidimo na serveru u usersAPI
  private readonly urls = {
    registerUrl: "http://localhost:3000/api/users/register",
    loginUrl: "http://localhost:3000/api/users/login",    
  }


    // Treba nekako da obavestimo i ostale komponente u aplikaciji da je korisnik prijavljen, npr ne zelimo da se add a product tab prikaze ako nije ulogovan
    // npr nama ovde ta informacija terba u user-info komponenti
    // to mzoemo na onaj glup nacin da radimo, da saljemo do korene komponente pa onda onda da prosledi ostalima 
    // bolji ncain je preko servisa, npr u okviru auth servisa, na sledeci nacin
    // pravimo jendno polje tipa Subject<> koje cuva informaciju o trenutnom korisniku. 
    // (da li je razlog sto koristimo bas Subject sto mzoemo da pozovemo metod asObservable()   (???)  )
    // dole pri dnu smo pozvali next da se promeni vrednost subjecta
    // kada god se userSubject promeni, observable ce emitovati vrednsot koja je taj novi korisnik
    // svako ko se prijavi na ovaj 'user' tok bice obavesten kada je doslo do promene korisnika
    // na kraju smo dodali ovo User | null zbog logout funkcionalnosti
    public readonly userSubject : Subject<User | null> = new Subject<User | null>();
    public readonly user : Observable<User | null> = this.userSubject.asObservable();



  // pored http servisa, ubrizgacemo i nas jwt servis
  constructor(private http: HttpClient, private jwt :JwtService) { }

  // sve ovo pravimo da bi ga korsitili u register formularu

  public registerUser(username:string, password:string, name:string, email:string) : Observable<User> {
    // vidimo na serveru da su login i registracija post zahtevi, za registraciju vidimo da se vraca neki objekat koji ima jwt token (?)
    // mozemo u <> da bas navedemo takav objekat umesto da koristimo vec neki ugradjen objekat (?)
    // kod post zahteva telo zahteva je OBAVEZNO
    const body = { 
      username,
      password, 
      name,
      email
    };

    // tokeni su jedan od nacina da se cuva informacija o konkretnom korisniku (drugi je da server sam pamti sve sto mu treba, a ovako sa tokenom zapravo server klijentu
    // posalje neki token i svaki put kada klijent hoce da urad ineku operaciju, on mora d a posalje taj token)
    // vidi na netu detaljno kako izgleda objekat koji predstavlja jwt-json web token
    const obs : Observable<{token:string}> = this.http.post<{token : string}>(this.urls.registerUrl, body);

    //u ovom trenutku smo napravili jwt auth servis, vidi to
    // dodali smo i id u user model (i da ga dodamo u poziv konstruktora za usera u user-profile, za sad smo ga fiksirali na '1')
    // ponovo pozivamo pipe 
    // metod tap() nam sluzi da pristupimo emitovanoj vrednosti, nesto uradimo sa njom i samo je pustimo dalje
    return obs.pipe(
      // response je objekat koji sadrzi token, kao gore sto smo naveli
      tap((response: {token:string}) => this.jwt.setToken(response.token)),   // sacuvamo token lokalno
      map((response: {token:string}) => this.sendUserDataIfExists()),
    );
  }

  sendUserDataIfExists() : User {
    const payload : IJwtTokenData = this.jwt.getDataFromToken();  // ne prosledjuemo token jer je sad sacuvan u local storageu
    const user:User = new User(payload.id, payload.username, payload.name, payload.email, payload.imgUrl);
    this.userSubject.next(user);    // prosledjujemo podatak Subject-u 
    return user;
  }

  // za logout je potrebno da izbrisemo token koji je sacuvan i da obavestimo ostale komponente o promeni
  public logout(): void {
    this.jwt.removeToken();
    this.userSubject.next(null);
  }
}
