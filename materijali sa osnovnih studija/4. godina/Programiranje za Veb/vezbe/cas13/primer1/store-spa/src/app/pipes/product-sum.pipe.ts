import { Pipe, PipeTransform } from '@angular/core';
import { Product } from '../models/product.model';

//ovaj pajp smo koristili u product-list

@Pipe({
  name: 'productSum'   // ovo je ime koje se koristi u sablonu, kao npr. | async
})
export class ProductSumPipe implements PipeTransform {

  // ovo u komentaru je ono sto generate pipe napravi automatski
  //transform(value: unknown, ...args: unknown[]): unknown {
  // ocekivano je da izmenimo. Prvi arg je ono na sta se pajp primenjuje, a ostali opcioni argumenti su opcije koje mozemo da navedemo 
  // kao one opcije sto smo koristili kod currency filtera
  transform(products: Product[], defaultValue: number=0) : number  {
    if (products.length ===0 ) {
      return defaultValue;
    }

    // sumuiramo sve cene niza
    return products.map((product:Product) => product.price)
                   .reduce((left:number, right:number) => left + right);
  }

}
