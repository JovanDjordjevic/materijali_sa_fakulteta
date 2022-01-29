import { Component, Input, OnInit } from '@angular/core';  
import { Observable } from 'rxjs';
import { Product } from 'src/app/models/product.model';  

@Component({
  selector: 'app-product-list',
  templateUrl: './product-list.component.html',
  styleUrls: ['./product-list.component.css']
})
export class ProductListComponent implements OnInit {

  // izmenili smo da bude observable
  // vidi i html za ovo. Sada je problem sot je ovo observable a tamo iteriramo kroz ovo kao da je niz u pitanju
  // ne zaboravimo da inicijalizujemo 
  @Input() products : Observable<Product[]> = new Observable<Product[]>();


  constructor() { }

  ngOnInit(): void {
  }

}
