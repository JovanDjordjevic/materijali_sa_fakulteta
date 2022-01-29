import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, tap, map } from 'rxjs';
import { User } from '../models/user.model';
import { AuthService } from './auth.service';
import { JwtService } from './jwt.service';

@Injectable({
  providedIn: 'root'
})
export class UserService {
  private readonly urls = {
    patchUser: "http://localhost:3000/api/users",
    patchUserProfileImage: "http://localhost:3000/api/users/profile-image"
}

  constructor(private http: HttpClient,
              private jwt: JwtService,
              private auth: AuthService) {}

  public patchUserData(username: string, email: string, name: string): Observable<User> {
    const body = {username, email, name};
    const headers: HttpHeaders = new HttpHeaders().append("Authorization", `Bearer ${this.jwt.getToken()}`);

    // ovo treba da nam vrati azurirani token
    return this.http.patch<{token: string}>(this.urls.patchUser, body, {headers}).pipe(
        tap((response: {token: string}) => this.jwt.setToken(response.token)),
        map((response: {token: string}) => this.auth.sendUserDataIfExists()!)
    )
  }

  public patchUserProfileImage(file: File): Observable<User> {
    // Angualr ce za nas da serijalizuje info o fajlu i posalje kao FormData
    const body: FormData = new FormData();
    body.append("file", file);
    const headers: HttpHeaders = new HttpHeaders().append("Authorization", `Bearer ${this.jwt.getToken()}`);

    // za ovo nam je takodje potrebna autorizacija, pa ce izmena u odnosu na prethodni ovakav deo iz pathUser biti samo u putanji koja se poziva
    return this.http.patch<{token: string}>(this.urls.patchUserProfileImage, body, {headers}).pipe(
        tap((response: {token: string}) => this.jwt.setToken(response.token)),
        map((response: {token: string}) => this.auth.sendUserDataIfExists()!)
    )
}
}
