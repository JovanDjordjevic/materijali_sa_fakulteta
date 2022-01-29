import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Talk } from '../models/talk.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {

  private readonly url = "http://localhost:3000/api/talks";

  constructor(private http : HttpClient) { }

  getAllTalks() : Observable<Talk[]>{
    const obs : Observable<Talk[]> = this.http.get<Talk[]>(this.url);
    return obs;
  }

  getAllTalksInArea(area : string): Observable<Talk[]>{
    const obs : Observable<Talk[]> = this.http.get<Talk[]>(this.url + '/' + area);
    return obs;
  }

  addNewTalk(talk : Talk) : Observable<Talk> {
    const obs : Observable<Talk> = this.http.post<Talk>(this.url, {talk});
    return obs;
  }
}
