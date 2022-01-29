import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-user-info',
  templateUrl: './user-info.component.html',
  styleUrls: ['./user-info.component.css']
})
export class UserInfoComponent implements OnInit, OnDestroy{
  
  sub : Subscription = new Subscription();
  user : User | null = null;
  isLogin : boolean = false;

  // treba nam nas auth servis jer smo tu implementirali nacin kako da se komponenta obavesti o promeni korisnika
  // vidi etaljnije komentare u ostalim klasama
  constructor(private auth : AuthService) {
      this.sub = this.auth.user.subscribe( (user:User | null) => {
        this.user = user;
      }); 

      this.auth.sendUserDataIfExists();
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
    this.sub.unsubscribe();
  }
  
  switchBetweenLoginAndRegistration(){
    this.isLogin = !this.isLogin;
  }
}
