import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { ProductPagination } from '../models/product-pagination';
import { Product } from '../models/product.model';
import { Observable, map } from 'rxjs'; 

@Injectable({
  providedIn: 'root'
})
export class ProductService {

  constructor(private http: HttpClient) { }

  // GET /
  public getProducts(page: number = 1, limit: number = 10): Observable<Product[]> {
    const params: HttpParams = new HttpParams().append('page', page).append('limit', limit);
    const obs: Observable<ProductPagination> = this.http.get<ProductPagination>("http://localhost:3000/api/products", { params });

    return obs.pipe(
      map((pagination: ProductPagination) => {
        return pagination.docs;
      })
    );
  }


  // get zahtev na /:productId
  public getProductById(productId: string) : Observable<Product>{
    return this.http.get<Product>('http://localhost:3000/api/products/' + productId);
  }

}
