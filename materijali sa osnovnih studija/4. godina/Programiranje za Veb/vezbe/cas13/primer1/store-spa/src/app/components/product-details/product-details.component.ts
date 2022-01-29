import { Component, OnDestroy, OnInit } from '@angular/core';
import { ActivatedRoute, ParamMap } from '@angular/router';
import { Observable, Subscription } from 'rxjs';
import { switchMap } from 'rxjs/operators';
import { Product } from 'src/app/models/product.model';
import { ProductService } from 'src/app/services/product.service';

@Component({
  selector: 'app-product-details',
  templateUrl: './product-details.component.html',
  styleUrls: ['./product-details.component.css']
})
export class ProductDetailsComponent implements OnInit, OnDestroy {

  product : Observable<Product> = new Observable<Product>();
  sub : Subscription = new Subscription();

  // ActivatedRoute 
  constructor(private activatedRoute : ActivatedRoute, private productService : ProductService) {
    // ovaj komentar je prvi nacin
    // paramMap je observable nad kolekcijom parametara koji se dobijaju sa putanje
    // konkretno Observable<ParamMap>
    // this.sub = this.activatedRoute.paramMap.subscribe((params:ParamMap) => {
    //   // string koji proseldimo get metodu mora da se poklapa sa imenom tog parametra koje smo naveli u app-routing.module u putanji
    //   const productId : string | null = params.get('productId');
    //   this.product = this.productService.getProductById(productId!);     // sa ! mozemo da oznacimo da promenljiva sigurno nece biti null (ovde nam se zalio kompajler) (ali ovaj 'hack' treba da izbegavamo)
    // })

    // drugi nacin, preko pipe 
    this.product = this.activatedRoute.paramMap.pipe(
      switchMap((params:ParamMap) => {  // ovaj switchMap je operator, slicno kao sto smo radili u servisima
        const productId : string | null = params.get('productId');
        return this.productService.getProductById(productId!);
      })
    );


  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}
