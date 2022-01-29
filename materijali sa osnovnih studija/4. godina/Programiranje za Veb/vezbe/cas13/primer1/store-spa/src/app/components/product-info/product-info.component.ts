import { Component, Input, OnInit } from '@angular/core';
import { Product, ProductPopularity } from 'src/app/models/product.model';

@Component({
  selector: 'app-product-info',
  templateUrl: './product-info.component.html',
  styleUrls: ['./product-info.component.css']
})
export class ProductInfoComponent implements OnInit {

  @Input() product: Product;

  PopularityEnum = ProductPopularity;

  constructor() { 
    this.product = new Product('', '', '', 0, false, null,  '', 50, '');
  }

  ngOnInit(): void {
  }

}
