import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Payment } from '../models/payment.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {
  private readonly url = "http://localhost:3000/api/payments";

  constructor(private http : HttpClient) { }

  getPaymentByEmail(email : string) : Observable<Payment>{
    const obs : Observable<Payment> = this.http.get<Payment>(this.url + "/email/" + email);
    return obs;
  }

  getPaymentById(id : string) : Observable<Payment>{
    const obs : Observable<Payment> = this.http.get<Payment>(this.url + "/id/" + id);
    return obs;
  }

  addAmount(id : string, amount : number) : Observable<Payment>{
    const obs : Observable<Payment> = this.http.patch<Payment>(this.url, {id, amount});
    return obs;
  }
}
