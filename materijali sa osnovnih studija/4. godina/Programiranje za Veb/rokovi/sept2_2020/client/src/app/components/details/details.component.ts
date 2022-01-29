import { Component, Input, OnInit } from '@angular/core';
import { Dessert } from 'src/app/models/dessert.model';

@Component({
  selector: 'app-details',
  templateUrl: './details.component.html',
  styleUrls: ['./details.component.css']
})
export class DetailsComponent implements OnInit {

    @Input() recepie : Dessert;

  constructor() {
    this.recepie = new Dessert('', '', '', 0, false);
  }

  ngOnInit(): void {
  }

}
