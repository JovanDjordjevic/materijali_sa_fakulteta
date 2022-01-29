import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Dessert } from '../models/dessert.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {

  private readonly url = "http://localhost:3000/api/desserts";

  constructor(private http : HttpClient) { }

  getAllDesserts() : Observable<Dessert[]>{
    const obs : Observable<Dessert[]> = this.http.get<Dessert[]>(this.url);
    return obs;
  }

  getDessertsWithCriterion(criterion : string) : Observable<Dessert[]>{
    const obs : Observable<Dessert[]> = this.http.get<Dessert[]>(this.url + "/" + criterion);
    return obs;
  }

  addNewDessert(dessert : Dessert) : Observable<Dessert>{
    const obs : Observable<Dessert> = this.http.post<Dessert>(this.url, {dessert});
    return obs;
  }
}

