import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Happening } from 'src/app/models/happening.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-events-component',
  templateUrl: './events-component.component.html',
  styleUrls: ['./events-component.component.css']
})
export class EventsComponent implements OnInit, OnDestroy {

  allHappenings : Happening[] = [];
  currentMonth : number = new Date().getMonth() + 1;
  currentMonthName : string = new Date().toLocaleString('default', {month: 'long'});
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService) { }

  ngOnInit(): void {
    //console.log(this.currentMonth)
    this.sub = this.requestService.getAllInMonth(this.currentMonth).subscribe((happenings : Happening[]) => {
      this.allHappenings = happenings;
      console.log(this.allHappenings);
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}
