import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';
import { Level, Word } from 'src/app/models/word.model';
import { RequestService } from 'src/app/services/request.service';
import { ExampleValidator } from 'src/app/validators/example.validator';

@Component({
  selector: 'app-word-info-with-form',
  templateUrl: './word-info-with-form.component.html',
  styleUrls: ['./word-info-with-form.component.css']
})
export class WordInfoWithFormComponent implements OnInit, OnDestroy{

  word : Word;
  sub : Subscription = new Subscription();
  exampleForm : FormGroup;

  constructor(private formBuilder : FormBuilder, private requestService : RequestService, private activatedRoute : ActivatedRoute) {
    this.word = new Word("", "", Level.A, []);

    this.exampleForm = this.formBuilder.group({
      example : ['Share your example!', [Validators.required, Validators.maxLength(100), ExampleValidator]]
    });
  }

  ngOnInit(): void {
    // ruzno
    this.activatedRoute.params.subscribe((data : any) => {
      const wordId = data.wordId;
      //console.log(this.wordId);
      this.requestService.getWordById(wordId).subscribe((word : Word) => {
        this.word = word;
      });
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onSubmitExample(){
    if(this.exampleForm.invalid) {
      window.alert('Check your example!');
      return;
    }

    const formData = this.exampleForm.value;
    //zahtev
    this.sub = this.requestService.updateWordExamples(this.word._id, formData.example).subscribe((updatedWord : Word) => {
      console.log(updatedWord.examples);
      window.alert("New example is succesfuly added!");
      this.word = updatedWord;
    });
  }
}
