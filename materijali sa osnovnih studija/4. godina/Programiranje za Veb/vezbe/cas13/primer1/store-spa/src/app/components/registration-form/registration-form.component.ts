import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { Router } from '@angular/router';
import { Observable, Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-registration-form',
  templateUrl: './registration-form.component.html',
  styleUrls: ['./registration-form.component.css']
})
export class RegistrationFormComponent implements OnInit, OnDestroy {
  registerForm: FormGroup;
  sub: Subscription = new Subscription();

  constructor(private auth: AuthService, private router:Router) {
    this.registerForm = new FormGroup({
      username: new FormControl('', [Validators.required, Validators.pattern(/^[0-9a-zA-Z_-]{8,}$/)]),
      password: new FormControl('', [Validators.required, Validators.pattern(/^[0-9a-zA-Z_!@#$%^&*()+=-]{4,}$/)]),
      name: new FormControl('', [Validators.required]),
      email: new FormControl('', [Validators.required, Validators.email]),
    });
  }

  ngOnDestroy(): void {
    if (this.sub) {
      this.sub.unsubscribe();
    }
  }

  ngOnInit(): void {
  }

  register(): void {
    if(this.registerForm.invalid) {
      window.alert("Not valid!");
      return;
    }
    
    const data = this.registerForm.value;
    const obs: Observable<User | null> = this.auth.register(data.username, data.password, data.email, data.name);

    this.sub = obs.subscribe((user: User | null) => {
      // Router servis ima u sebi razne metode za navigaciju, ovaj navigateByUrl() nas vodi na putanju koju navedemo
      this.router.navigateByUrl('/')
    });
  }

}
