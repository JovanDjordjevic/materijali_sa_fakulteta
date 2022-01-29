import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Meteo } from '../models/meteo.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {
  private readonly url = "http://localhost:3000/api/meteos";

  constructor(private http : HttpClient) { }

  gelAllMeteo() : Observable<Meteo[]> {
    const obs : Observable<Meteo[]> = this.http.get<Meteo[]>(this.url);
    return obs;
  }

  getMeteoForCity(city : string) : Observable<Meteo> {
    const obs : Observable<Meteo> = this.http.get<Meteo>(this.url + '/' + city);
    return obs;
  }

  updateTemperaturesForCity(city : string, temps : number[]) : Observable<string> {
    const obs : Observable<string> = this.http.put<string>(this.url, {city, temps});
    return obs;
  }
}
