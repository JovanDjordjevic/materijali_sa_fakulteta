import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Kanban } from 'src/app/models/kanban.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-kanban-list',
  templateUrl: './kanban-list.component.html',
  styleUrls: ['./kanban-list.component.css']
})
export class KanbanListComponent implements OnInit, OnDestroy {

  kanbans : Kanban[] = []
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService) { }

  ngOnInit(): void {
    this.sub = this.requestService.getAllUnfinished().subscribe((kanbans : Kanban[]) => {
      this.kanbans = kanbans;
      console.log(this.kanbans)
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}