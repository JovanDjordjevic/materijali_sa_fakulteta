import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Word } from 'src/app/models/word.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-words-by-level-component',
  templateUrl: './words-by-level-component.component.html',
  styleUrls: ['./words-by-level-component.component.css']
})
export class WordsByLevelComponentComponent implements OnInit {

  level : string = "";
  allWords : Word[] = []; 

  linkError : boolean = false;

  constructor(private requestService : RequestService, private activatedRoute : ActivatedRoute) { }

  ngOnInit(): void {
    this.activatedRoute.params.subscribe((data : any) => {
      this.level = data.level;
      if(this.level != 'A' && this.level != 'B' && this.level != 'C') {
        this.linkError = true;
      }

      this.requestService.getWordsByLevel(this.level).subscribe((words : Word[]) => {
        this.allWords = words;
      });
    });
  }

}
