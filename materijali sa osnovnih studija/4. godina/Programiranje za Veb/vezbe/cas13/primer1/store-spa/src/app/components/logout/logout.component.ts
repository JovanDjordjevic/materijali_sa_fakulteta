import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-logout',
  templateUrl: './logout.component.html',
  styleUrls: ['./logout.component.css']
})
export class LogoutComponent implements OnInit {

  constructor(private auth : AuthService, private router : Router) {
    // ova komponenta nece nista ni da prikazuje, samo sluzi za logout
    this.auth.logout()
    this.router.navigateByUrl('/');
   }

  ngOnInit(): void {
  }

}
