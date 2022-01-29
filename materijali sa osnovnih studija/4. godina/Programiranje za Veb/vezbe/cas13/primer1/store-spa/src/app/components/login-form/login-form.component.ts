import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { Observable, Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-login-form',
  templateUrl: './login-form.component.html',
  styleUrls: ['./login-form.component.css']
})
export class LoginFormComponent implements OnInit, OnDestroy {
  sub: Subscription = new Subscription();
  loginForm: FormGroup;

  constructor(private auth: AuthService, private router:Router) {
    this.loginForm = new FormGroup({
      username: new FormControl('', [Validators.required, Validators.pattern(/^[0-9a-zA-Z_-]{8,}$/)]),
      password: new FormControl('', [Validators.required, Validators.pattern(/^[0-9a-zA-Z_!@#$%^&*()+=-]{4,}$/)]),
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
    this.sub.unsubscribe();
  }

  login(): void {
    if (this.loginForm.invalid) {
      window.alert('Form is not valid!');
    }

    const data = this.loginForm.value;
    const obs: Observable<User | null> = this.auth.login(data.username, data.password);

    this.sub = obs.subscribe((user: User | null) => {
      this.router.navigateByUrl('/login')
    });

    this.auth.login(data.username, data.password);
  }

}
