import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { Area, Talk } from 'src/app/models/talk.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-register-talk',
  templateUrl: './register-talk.component.html',
  styleUrls: ['./register-talk.component.css']
})
export class RegisterTalkComponent implements OnInit, OnDestroy {

  talkForm : FormGroup;
  EPS : number = 0.00000001;
  sub : Subscription = new Subscription();
  AreaEnum = Area;

  constructor(private formBuilder : FormBuilder, private requestService : RequestService) {
    this.talkForm = formBuilder.group({
      title : ['Your title', [Validators.required, Validators.maxLength(100)]],
      speaker : ['Your name', [Validators.required, Validators.maxLength(50)]],
      area : ['', [Validators.required]],
      duration : ['Talk duration', [Validators.required, Validators.min(this.EPS), Validators.maxLength(3)]],
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
    this.sub.unsubscribe();
  }

  onTalkFormSubmit(){
    if(!this.talkForm.valid) {
      window.alert('Form is invaluid, please check the inputs!');
      return;
    }

    const formData = this.talkForm.value;
    const newTalk = new Talk(formData.title, formData.speaker, formData.area, formData.duration);
    //console.log(newTalk);
    this.sub = this.requestService.addNewTalk(newTalk).subscribe((talk : Talk) => {
      //console.log(talk);
      window.alert('Your talk is successfuly registered!');
    });
  }
}
