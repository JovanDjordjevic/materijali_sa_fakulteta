import { Component, OnInit } from '@angular/core';     // ovde dodali OnInit
import { Product } from './models/product.model';   // dodali Product

// ovo je poterbno za jquery kod, vidi beleske
declare const $: any;

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {   //ovde dodali implements OnInit
  title = 'store-spa';

  // ovo smo radili posle direktiva
  // psoto i dalje nemamo server nego sve radimo na clientu, cuvacemo ovde neki niz. (vidi models/product.model.ts)
  productsFromRoot: Product[] = [
    new Product('New Lenovo laptop 2020', 'A very good laptop. Unpacked!', 450,
                true, 'assets/default-product.jpg', 'Pera Peric', 10),
    new Product('iPhone XS', 'Used for a year', 550, 
                true, 'assets/default-product.jpg', 'Pera Peric', 1),
    new Product('The Way of Kings Book One [SOLD!]', 'Fantasy novel by Brandon Sanderson', 10,
                false, 'assets/default-product.jpg','Pera Peric', 250),
  ];


  // ovaj jquery kod treba da se izvrsi ovde u konstruktoru (?)    (ovo je prvo sto smo napisali)
  constructor(){
    // izmesteno u funkc ispod
    // $('.menu .item').tab();  //jquery kod za selektovanje kartica koji smo izguglali
  }

  // metod koji moramo da implementiramo iz interfejsa
  ngOnInit(){
    // ono sto se poziva u okviru ovog metoda je ono sto ce se izvrsiti domah nakon sto se ucita sablon ove komponente
    // jquery poziv smo prebacili ovde zato sto u trenutku kada se pozove konstruktor, sablon za ovu komponentu i dalje nije ucitan
    // tako da tada ovaj jquery ne moze da se izvrsi
    $('.menu .item').tab();
  }


  // za dohvatanje podatka koji nam je poslao child element
  // pazimo samo sledece. Mi smo u childu poslali neki EventEmitter<Product>, ali ovde ne stize celo to nego samo konkretan Product!
  onProductCreated(product : Product) {
    this.productsFromRoot.push(product);
  }
}
