import { Component, Input, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Kanban } from 'src/app/models/kanban.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-kanban',
  templateUrl: './kanban.component.html',
  styleUrls: ['./kanban.component.css']
})
export class KanbanComponent implements OnInit , OnDestroy{

  @Input() kanban : Kanban;
  sub : Subscription = new Subscription();

  ratio : number = 1;
  progressBarWidth : string = "30%";
  progressBarColor : string = "red";
  
  constructor(private requestService : RequestService) { 
    this.kanban = new Kanban('', '', 0, 0);
  }

  ngOnInit(): void {
    this.calculateRatio();
  }
  
  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  calculateRatio(){
    this.ratio = this.kanban.completedSubtasks / this.kanban.numOfSubtasks;
    //console.log(this.ratio)
    if(this.ratio < 0.3) {
      this.progressBarWidth = "30%";
      this.progressBarColor = "red";
    } 
    else if(this.ratio < 0.7){
      this.progressBarWidth = "70%";
      this.progressBarColor = "yellow";
    }
    else {
      this.progressBarWidth = "100%";
      this.progressBarColor = "green";
    }
  }

  onClickCompleteNextTask(){
    this.sub = this.requestService.updateKanbanWithId(this.kanban._id).subscribe((msg : string) => {
      console.log(msg)
      this.kanban.completedSubtasks++;
      this.calculateRatio();
      //azuriranje progress bara
    })
  }
}
