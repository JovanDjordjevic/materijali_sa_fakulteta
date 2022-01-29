// izbrisani komentari od proslog casa

import { Component, OnInit } from '@angular/core';
import { User } from 'src/app/models/user.model';

@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit {
  user: User;

  // za demonmstriranje ngIf
  // ovo nam vise ne treba jer smo promenili format tako da korisitmo ngIf direktivu
  //inputFieldClass: string = "disabled field";
  shouldDisplayUserForm: boolean = false;

  // za demonstriranje ngFor
  addresses: string[] = ['Street 1', 'Street 2', 'Street 3'];

  // za demonstriranje ngSwitch
  orderNumber: number = 1; 

  constructor() { 
    this.user = new User("Pera Peric", "pera@gmail.com", "/assets/default-user.png");
  }

  ngOnInit(): void {
  }

  // za ngStyle
  getColor(paranIndeks: boolean) : string {
    return paranIndeks ? "black" : "gray";
  }

  onChangeInfo() {
    //this.inputFieldClass = "field"; 
    this.shouldDisplayUserForm = true;
  }

  onSaveChanges() {
    //this.inputFieldClass = "disabled field";
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
}
