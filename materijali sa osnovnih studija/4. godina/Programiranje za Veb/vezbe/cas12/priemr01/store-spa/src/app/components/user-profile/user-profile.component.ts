// izbrisani komentari od proslog casa

import { Component, Input, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';

@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {
  
  // ovaj user dolazi iz nove user-info komponente koja joj je parent
  @Input() user: User;

  shouldDisplayUserForm: boolean = false;

  addresses: string[] = ['Street 1', 'Street 2', 'Street 3'];

  orderNumber: number = 1; 

  userForm: FormGroup;

  //dodajemo i nas auth servis jer ce on da radi logout
  constructor(private formBuilder: FormBuilder, private autoh : AuthService) { 
    this.user = new User('1', "peraperic", "Pera Peric", "pera@gmail.com", "/assets/default-user.png");

   
    this.userForm = new FormGroup({
      username: new FormControl(this.user.username, [Validators.required, Validators.pattern(new RegExp("[a-zA-Z0-9_-]{8,}"))]),
      email: new FormControl(this.user.email, [Validators.required, Validators.email]),
      name: new FormControl(this.user.name, [Validators.required, Validators.minLength(2)]),
      imgUrl: new FormControl(''),
    });
  }

  ngOnInit(): void {
  }

  onUserFormSubmit() {
    const data = this.userForm.value;

    if(this.userForm.invalid) {
      window.alert('Form is not valid!');
      return;
    }

    this.user.username = data.username;
    this.user.name = data.name;
    this.user.email = data.email;

    this.userForm.reset({
      username: '',
      name: '',
      email: '',
    });  

    this.onSaveChanges();
  }

  getColor(paranIndeks: boolean) : string {
    return paranIndeks ? "black" : "gray";
  }

  onChangeInfo() {
    this.shouldDisplayUserForm = true;
  }

  onSaveChanges() {
    this.shouldDisplayUserForm = false;
  }

  onChangeName(event: Event) {
    const name = (event.target as HTMLInputElement).value;
    this.user.name = name;
  }

  onChangeEmail(event: Event) {
    const email = (event.target as HTMLInputElement).value;
    this.user.email = email;
  }

  logout() : void{
  }


  getUserImageUrl() :string {
    // implemenmtirali smo ovu funkc u user modelu
    return this.user.getImageUrl();
  }
}
