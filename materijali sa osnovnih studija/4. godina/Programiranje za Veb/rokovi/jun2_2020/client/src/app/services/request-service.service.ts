import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Song } from '../models/song.model';

@Injectable({
  providedIn: 'root'
})
export class RequestServiceService {
  private readonly url = "http://localhost:3000/api/songs";

  constructor(private http : HttpClient) { }

  sortBy(sortParam : string) : Observable<Song[]>{
    const obs : Observable<Song[]> = this.http.get<Song[]>(this.url + "/" + sortParam);
    return obs;
  }

  incrementCountForSong(id : string) : Observable<Song>{
    const obs : Observable<Song> = this.http.patch<Song>(this.url, {id});
    return obs;
  }

  addNewSong(artist : string, title : string) : Observable<string>{
    const obs : Observable<string> = this.http.put<string>(this.url, {artist, title});
    return obs;
  }
}
