import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-nav-menu',
  templateUrl: './nav-menu.component.html',
  styleUrls: ['./nav-menu.component.css']
})
export class NavMenuComponent implements OnInit, OnDestroy {
  user : User | null = null;
  sub : Subscription = new Subscription();

  constructor(private auth: AuthService) { 
    this.sub = this.auth.user.subscribe((user:User | null) => {
      this.user = user;
    });
    this.auth.sendUserDataIfExists();
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
    if(this.sub){
      this.sub.unsubscribe();
    }
  }

  getLoginOrLogoutRouterLink() : string{
    return this.user ? '/logout'  : '/login';
  }

  public getLoginOrLogoutRouterString() : string{ 
    return this.user ? 'Logout'  : 'Login';
  }

}
