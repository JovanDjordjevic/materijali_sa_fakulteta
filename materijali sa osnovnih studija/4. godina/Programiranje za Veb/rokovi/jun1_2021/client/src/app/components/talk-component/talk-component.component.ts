import { Component, Input, OnInit } from '@angular/core';
import { Area, Talk } from 'src/app/models/talk.model';

@Component({
  selector: 'app-talk-component',
  templateUrl: './talk-component.component.html',
  styleUrls: ['./talk-component.component.css']
})
export class TalkComponentComponent implements OnInit {

  @Input() talk : Talk;
  AreaEnum = Area;
  durationColor : string = "purple";

  constructor() {
    this.talk = new Talk('', '', Area.Angular, 0);  
  }

  ngOnInit(): void {
    if (this.talk.duration <= 1) {
      this.durationColor = 'palevioletred';
    }
    else if (this.talk.duration >= 1 && this.talk.duration <= 2) {
      this.durationColor = 'palegoldenrod';
    }
    else {  // 2 do 3 h
      this.durationColor = 'paleturquoise';
    }
  }
}
