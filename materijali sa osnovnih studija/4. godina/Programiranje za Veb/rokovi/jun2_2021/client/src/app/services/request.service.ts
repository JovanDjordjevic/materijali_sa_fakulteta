import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Word } from '../models/word.model';

@Injectable({
  providedIn: 'root'
})
export class RequestService {

  private readonly url = "http://localhost:3000/api/words";

  constructor(private http : HttpClient) { }

  getAllWords() : Observable<Word[]>{
    const obs : Observable<Word[]> = this.http.get<Word[]>(this.url, {});
    return obs;
  }

  getWordsByLevel(level : string) : Observable<Word[]>{
    const obs : Observable<Word[]> = this.http.get<Word[]>(this.url + "/" + level);
    return obs;
  }

  updateWordExamples(id : string, example : string) : Observable<Word>{
    const obs : Observable<Word> = this.http.put<Word>(this.url, {id, example});
    return obs; 
  }

  // nije u tekstu zadatka, ja sam dodao jer sam hteo da vezbam routing
  getWordById(id : string) : Observable<Word>{
    const obs : Observable<Word> = this.http.get<Word>(this.url + "/id/" + id);
    return obs;
  }
}
