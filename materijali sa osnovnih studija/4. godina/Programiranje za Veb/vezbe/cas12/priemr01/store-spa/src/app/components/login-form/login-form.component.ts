import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-login-form',
  templateUrl: './login-form.component.html',
  styleUrls: ['./login-form.component.css']
})
export class LoginFormComponent implements OnInit {

  loginForm : FormGroup;

  constructor() { 
    this.loginForm = new FormGroup({
      username : new FormControl('', [Validators.required, Validators.pattern(new RegExp("[0-9a-zA-Z_-]{4, }"))] ),
      password : new FormControl('', [Validators.required, Validators.pattern(new RegExp("[0-9a-zA-Z!@#$%^&*()_+-=]{4, }"))])
    });
  }

  ngOnInit(): void {
  }


  login(){
    // ...
  }
}
