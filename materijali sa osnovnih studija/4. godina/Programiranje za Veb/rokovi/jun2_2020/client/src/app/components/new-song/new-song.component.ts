import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { RequestServiceService } from 'src/app/services/request-service.service';

@Component({
  selector: 'app-new-song',
  templateUrl: './new-song.component.html',
  styleUrls: ['./new-song.component.css']
})
export class NewSongComponent implements OnInit, OnDestroy {

  newSongForm : FormGroup
  sub : Subscription = new Subscription();

  constructor(private formBuilder : FormBuilder, private requestService : RequestServiceService) {
    this.newSongForm = formBuilder.group({
      artist : ['', [Validators.required]],
      title : ['', [Validators.required]]
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onNewSongFormSubmit(){
    if(!this.newSongForm.valid){
      window.alert("The form is not valid!");
      return;
    }

    const formData = this.newSongForm.value;
    this.sub = this.requestService.addNewSong(formData.artist, formData.title).subscribe((msg : string) => {
      if(msg) {
        window.alert(msg);
      }
    });
  }

}
