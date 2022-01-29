import { HttpClient, HttpClientModule } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Happening } from '../models/happening.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {

  private readonly url = "http://localhost:3000/api/events";

  constructor(private http : HttpClient) { }

  getAllInMonth(month : number) : Observable<Happening[]> {
    const obs : Observable<Happening[]> = this.http.get<Happening[]>(this.url + "/month/" + month);
    return obs;
  }

  getEventById(id : string) : Observable<Happening> {
    const obs : Observable<Happening> = this.http.get<Happening>(this.url + "/" + id);
    return obs;
  }

  addTodoForEvent(id : string, step : string) : Observable<Happening> {
    const obs : Observable<Happening> = this.http.put<Happening>(this.url, {id, step});
    return obs;
  }

}

