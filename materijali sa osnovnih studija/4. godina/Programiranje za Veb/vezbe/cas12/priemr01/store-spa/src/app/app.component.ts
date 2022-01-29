import { AfterViewChecked, Component, OnInit } from '@angular/core';     // ovde dodali OnInit
import { Observable } from 'rxjs';
import { Product } from './models/product.model';   // dodali Product
import { User } from './models/user.model';
import { AuthService } from './services/auth.service';
import { ProductService } from './services/product.service';

// ovo je poterbno za jquery kod, vidi beleske
declare const $: any;

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit, AfterViewChecked {   //dodali AfterViewChecked!!
  title = 'store-spa';

  // dodali
  user : User | null = null;
  
  productsFromRoot: Observable<Product[]>;

  // napravili smo servis koji ce dohvatati rpoizvode, tako da treba da ga ubrizgamo ovde
  // treba nam i nas auth servis 
  constructor(private productService : ProductService, private auth : AuthService){
    // dakle pri kosntrukciji app komponente ce se poslati get zahtev i sacuvace se ovde podaci
    // posto smo ove podatke prosledjivali u product-list, i tamo treba da dodamo da bude oBservable
    this.productsFromRoot = this.productService.getProducts(1, 10);

    // treba da se pretplatimo na njega
    this.auth.user.subscribe((user:User | null) => {
      this.user = user;
    });
  }

  // primetimo problem koji je nastao kada smo napisali ovo iznad. Mi hocemo da se add product tab ne prikazuje dok se user ne uloguje, ali
  // kada se uloguje i tab bude vidljiv, ne moze da se klikne na njega. Da bi moglo da se klikne na njega mora da se pozove onaj jquery kod iz ngOnInit
  // ali on je izvrsen samo jendom na pocetku pre nego sto je tab postao vidljiv
  // resenje za ovo je da taj kod pozivamo svaki puta kada se izmeni html, za to pored OnInit mozemo da implementiramo i interfejs AfterViewChecked
  ngAfterViewChecked(){
    $('.menu .item').tab();
  }

  ngOnInit(){
    $('.menu .item').tab();
  }

  onProductCreated(product : Product) {
  }
}
