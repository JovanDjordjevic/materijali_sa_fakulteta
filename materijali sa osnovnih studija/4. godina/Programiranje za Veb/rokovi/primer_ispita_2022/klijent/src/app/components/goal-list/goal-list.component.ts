import { COMPILER_OPTIONS, Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Goal, Importance } from 'src/app/models/goal.model';
import { GoalService } from 'src/app/services/goal.service';

@Component({
  selector: 'app-goal-list',
  templateUrl: './goal-list.component.html',
  styleUrls: ['./goal-list.component.css']
})
export class GoalListComponent implements OnInit, OnDestroy {

  ImportanceEnum = Importance;

  allGoals : Goal[] = [];

  filteredGoals : Goal[] = [];
  importanceFilter : number = 0;
  complexityFilter : number = 0;

  sub : Subscription = new Subscription();

  constructor(private goalService : GoalService) {

  }

  ngOnInit(): void {
    this.goalService.getAllGoals().subscribe((goals : Goal[]) => {
      console.log('goals:', goals);
      this.allGoals = goals;
      this.filteredGoals = goals;
    });
  }

  ngOnDestroy(): void {
    this.sub.unsubscribe();
  }

  clickedGoalInList(id : string){
    this.goalService.getGoalById(id).subscribe((goal: Goal) => {
      console.log(goal);
    });
  }

  importanceColor(importance : number) : string {
    let color : string = "";

    switch(importance){
      case 1:
        color = "red";
        break;
      case 2:
        color = "orange";
        break;
      case 3:
        color = "yellow";
        break;
      default:
        break;
    }

    return color;
  }

  filterAllGoals(importance : number, complexity : number) {
    this.filteredGoals = this.allGoals.filter((goal : Goal) => {
      let importanceCriterion : boolean = ( importance == 0 || goal.vaznost == importance? true : false);

      let complexityCriterion : boolean = false;
      switch (complexity){
        case 1:
          complexityCriterion = ( goal.koraci.length <= 1 ? true : false);
          break;
        case 2:
          complexityCriterion = ( goal.koraci.length == 2 || goal.koraci.length == 3 ? true : false);
          break;
        case 3:
          complexityCriterion = ( goal.koraci.length >= 4 ? true : false);
          break;
        default: // complexity = 0
          complexityCriterion = true;
          break;
      }

      return importanceCriterion && complexityCriterion;
    });
  }

  importanceFilterSelected(){
    const importanceSelectElement = document.getElementById('importanceFilter');
    const importanceValue = (importanceSelectElement as HTMLSelectElement).value;
    switch(importanceValue){
      case '1':
        this.importanceFilter = 1;
        break;
      case '2':
        this.importanceFilter = 2;
        break;
      case '3':
        this.importanceFilter = 3;
        break;
      default: 
        this.importanceFilter = 0;
        break;
    }

    this.filterAllGoals(this.importanceFilter, this.complexityFilter);
  }

  complexityFilterSelected(){
    const complexitySelectElement = document.getElementById('complexityFilter');
    const complexityValue = (complexitySelectElement as HTMLSelectElement).value;
    switch(complexityValue){
      case '1':
        this.complexityFilter = 1;
        break;
      case '2':
        this.complexityFilter = 2;
        break;
      case '3':
        this.complexityFilter = 3;
        break;
      default: 
        this.complexityFilter = 0;
        break;
    }

    this.filterAllGoals(this.importanceFilter, this.complexityFilter);
  }
}
