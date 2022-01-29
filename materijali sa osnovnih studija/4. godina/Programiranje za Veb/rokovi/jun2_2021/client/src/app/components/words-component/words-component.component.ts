import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Word } from 'src/app/models/word.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-words-component',
  templateUrl: './words-component.component.html',
  styleUrls: ['./words-component.component.css']
})
export class WordsComponentComponent implements OnInit, OnDestroy {

  allWords : Word[] = [];

  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService) { }

  ngOnInit(): void {
    this.sub = this.requestService.getAllWords().subscribe((words : Word[]) => {
      this.allWords = words;
      console.log(this.allWords)
    })
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}
