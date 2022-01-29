import { Component, Input, OnInit } from '@angular/core';   // dodali Input
import { Product } from 'src/app/models/product.model';  // dodato

@Component({
  selector: 'app-product-list',
  templateUrl: './product-list.component.html',
  styleUrls: ['./product-list.component.css']
})
export class ProductListComponent implements OnInit {

  // u rpoduct list hocemo da izvedemo slanje niz hijerarhiju, niz Products se nalazi u root komponenti, a treba neko da ga vidimo ovde
  // prvo nam ovde u detetu treba svojstvo odgovarajuceg tipa, onda nam za to treba dekorator @Input(), nakon toga
  @Input() products : Product[] = [];


  constructor() { }

  ngOnInit(): void {
  }

}
