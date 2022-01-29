import { Component, OnDestroy, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';
import { Happening } from 'src/app/models/happening.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-event-component',
  templateUrl: './event-component.component.html',
  styleUrls: ['./event-component.component.css']
})
export class EventComponent implements OnInit, OnDestroy {

  happening : Happening;
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService, private activatedRoute: ActivatedRoute) {
    this.happening = new Happening("", new Date(), 0, []);
  }

  ngOnInit(): void {
    let happeningId = "";
    this.sub = this.activatedRoute.params.subscribe((data : any) => {
      happeningId = data.id;
      this.requestService.getEventById(happeningId).subscribe((happening : Happening) => {
        this.happening = happening;
      });
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onUpdatedTodos(todos : string[]){
    this.happening.todo = todos;
  }
}
