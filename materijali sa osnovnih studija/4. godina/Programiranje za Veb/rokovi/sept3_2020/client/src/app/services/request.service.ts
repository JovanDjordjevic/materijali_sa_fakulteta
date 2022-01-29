import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Kanban } from '../models/kanban.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {
  private readonly url = "http://localhost:3000/api/kanban";

  constructor(private http : HttpClient) { }

  getAllUnfinished() :Observable<Kanban[]> {
    const obs : Observable<Kanban[]> = this.http.get<Kanban[]>(this.url);
    return obs;
  }

  addNewKanban(kanban : Kanban) : Observable<string>{
    const obs : Observable<string> = this.http.post<string>(this.url, {kanban});
    return obs;
  }

  updateKanbanWithId(id : string) : Observable<string>{
    const obs : Observable<string> = this.http.patch<string>(this.url + '/' + id, {});
    return obs;
  }
}
