import { Component, Input, OnInit } from '@angular/core'; // dodato Input
import { Product, ProductPopularity} from 'src/app/models/product.model'; // dodato

@Component({
  selector: 'app-product-info',
  templateUrl: './product-info.component.html',
  styleUrls: ['./product-info.component.css']
})
export class ProductInfoComponent implements OnInit {

  // u ovu komponentu ce da udje jedan product iz parenta tako da nam treba jedno polje ovde
  @Input() product: Product;

  // u htmlu koristimo ovaj enum u ngSwitch, ali da bi to moglo da radi, mormao ovde u TS da navedemo sta je taj enum (jer se u htmlu ne vidi ako ga
  // samo importujemo gore), pa je potrebno da ga dodelimo nekom nasem enumu u ovoj komponenti (?)
  // moglo je i da se zove drugacije, da ne bude zabune  (npr   ProductEnum = ProductPopularity    pa onda u htmlu da stoji ProductEnum.vrednost)
  ProductPopularity = ProductPopularity;

  constructor() { 
    this.product = new Product('', '', 0, false, '', '', 8);
  }

  ngOnInit(): void {
  }

}
