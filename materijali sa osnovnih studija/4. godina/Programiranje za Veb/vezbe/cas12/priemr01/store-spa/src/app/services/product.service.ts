import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { map, Observable } from 'rxjs';
import { ProductPagiantion } from '../models/product-pagination.model';
import { Product } from '../models/product.model';

// Kada napravimo neki servis sa ng generate service, videcemo da je on dekorisan dekoratotm Injectable
@Injectable({
  providedIn: 'root'  // ovo nam kaze u kom trenutku ce se instancirati singleton objekat koji prestavlja servis, tj ovde konkretno u trenutku kada se napravi root komponenta
})
export class ProductService {

  // u ovaj nas servis ubrizgavamo HttpClient servis iz onog modula koji smo ucitali u app.module.ts
  constructor(private http: HttpClient) { 

  }

  // treba nam metod koji dohvata stvari sa servera. Imace ove parametre jer smo se tako dogovorili, tj na serveru imamo neki metod koji obradjuje zahtev
  // koji prima ove parametre zbog pagiante modula iz mongoosa
  // Ovaj metod nece vratiti objekat koji nam posalje server vec Observable, to je tok koji sluzi za emitovanje vrednosti. 
  // Kada dohvatimo podatke sa server, to se desava asinhrono i ne znamo kada  ce odgovor stici
  // Nad ovim tokom mozemo imati 'pretplatioce', tj funkcije koje ce se pozvati svaki put kada ovaj tok emituje neku vrednost
  // to cemo ratiti tako sto cemo ulancavati poziv (videcemo kasnije)  getProducts().subscribe(nesto...)
  getProducts(page: number=1, limit: number=10) : Observable<Product[]>{
    // preko psotmana smo poslali zahtev na  .../api/products  adresu. Vidimo da to vraca neki pagination objekat sa informacijama o proizvodima
    // u http servisu imamo metode za slanje zahteva. Ti svi metodu su sablonski. U nasem slucaju posto ocekujemo da se vrati neki pagination objekat, 
    // moramo sa klijentske strane da imamo neki interfejs ka tome, pa cemo da napravimo ProductPagination klasu  (dodali smo u models)
    // prvi arg za zahtev je i jedini obavezni i to je url, ostali si opcioni, imamo npr headere-videcmeo posle, observe-tu kazemo na koji dogadjaj cemo da reagujemo,
    // httpparams-to su query parametri itd
    // evo npr kako bi radili sa params, bitno je da zamapamtimo da je HttpParams imutabilan objekat, tako da pri konstrukciji odmah treba i da mu dodelimo vrednosti koje hocemo
    // ono sto bi se desilo u suprotnom je da kada uradimo append, napravi se novi objekat koji onda mozemo da uhvatimo (ali to nam nije od koristi)
    const params : HttpParams = new HttpParams().append('page', page).append('limit', limit);
    // malo zbunjujuce, ali params argument prima objekat koji ima polje params koji je HttpParams objekat (?)
    // ono sto get zahtev vraca nece biti ProductPagiantion nego Observable nad ProductPagiantion
    const obs : Observable<ProductPagiantion> = this.http.get<ProductPagiantion>("http://localhost:3000/api/products", {params});

    // priemtimo da sada imamo jedan observable nad ProductPagiantion a treba nam observable nad Product[]
    // za pretvaranje jednog observable toka u drugi imamo metod pipe(). U okviru njega mozemo da ulancamo razne rxjs operatore koj ce nesto raditi sa tim tokom
    // slicno kao funkcionalna paradigma
    return obs.pipe( 
      // imamo operator map, znamo da u pagination imamo poje docs koje sadrzi bas niz proizvoda sto nam i treba
      map( (pagination : ProductPagiantion) => {return pagination.docs} )
      // u ovom trenutku, obs je Observable<Product[]> pa mozemo da ga vratimo
    );
    
    
  }
  
}
