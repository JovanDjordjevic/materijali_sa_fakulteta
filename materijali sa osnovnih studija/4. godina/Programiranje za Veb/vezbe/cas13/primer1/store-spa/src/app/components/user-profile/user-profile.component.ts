import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { User } from 'src/app/models/user.model';
import { AuthService } from 'src/app/services/auth.service';
import { UserService } from 'src/app/services/user.service';

@Component({
  selector: 'app-user-profile',
  templateUrl: './user-profile.component.html',
  styleUrls: ['./user-profile.component.css']
})
export class UserProfileComponent implements OnInit{
  
  user: User | null = null;
  userForm: FormGroup;
  shouldDisplayUserForm: boolean = false; 
  private imageForUpload: File | null = null;

  userSub : Subscription = new Subscription();

  constructor(private formBuilder: FormBuilder, private auth: AuthService, private userService: UserService) {

    this.userForm = new FormGroup({
      username: new FormControl('', [Validators.required, Validators.pattern(new RegExp("[a-zA-Z0-9_-]{8,}"))]),
      email: new FormControl('', [Validators.required, Validators.email]),
      name: new FormControl('', [Validators.required, Validators.minLength(2)]),
      imgUrl: new FormControl('')
    });

    this.userSub = this.auth.user.subscribe((user:User | null) => {
      this.user = user;
    });

    this.auth.sendUserDataIfExists();
  }

  ngOnInit(): void {
  
  }

  onChangeInfo() {
    this.shouldDisplayUserForm = true;
  }

  onSaveChanges() {
    this.shouldDisplayUserForm = false;
  }

  onUserFormSubmit() {
    if (this.userForm.invalid) {
      window.alert('Form is not valid!');
      return;
    } 

    const data = this.userForm.value;

    // ako je korisnik pravilno popunio formu, treba poslati zahtev za izmenu podataka
    this.userService.patchUserData(data.username, data.email, data.name).subscribe((user: User) => {
      if(!this.user) this.user = new User('','','','','');
      
      this.user.username = user.username;
      this.user.email = user.email;
      this.user.name = user.name;

      // treba proveriti da li je korisnik menjao i sliku
      if (this.imageForUpload !== null) {
          this.userService.patchUserProfileImage(this.imageForUpload).subscribe((user: User) => {
            this.user!.imgUrl = user.imgUrl;
        });
      }

      this.userForm.reset({
          username: this.user.username
      });

      console.log(this.user);

      this.onSaveChanges();
    });
  }

  getUserImage(): string {
    if(!this.user) {
      return 'assets/default-user.png';
    }
    return this.user.getImageUrl();
  }

  public onFileChange(event: Event): void {
    const files: FileList | null = (event.target as HTMLInputElement).files;

    // moze da se desi da je otvorio dijalog ali nije nista odabrao, pa to moramo proveriti
    if(!files || files.length === 0) {
        this.imageForUpload = null;
        return;
    }

    this.imageForUpload = files[0];
  }

}
