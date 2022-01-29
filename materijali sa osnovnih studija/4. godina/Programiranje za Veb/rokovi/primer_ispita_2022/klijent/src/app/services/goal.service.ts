import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { Goal } from '../models/goal.model';

@Injectable({
  providedIn: 'root'
})
export class GoalService {
  private readonly urls = {
    getAllGoals : 'http://localhost:3000/api/goals',
    getGoalById : 'http://localhost:3000/api/goals',  // pa se nadoveze
    addNewGoal : 'http://localhost:3000/api/goals',
    
  };

  constructor(private http : HttpClient) { }

  public getAllGoals() : Observable<Goal[]> {
    //console.log('getAllGoals');
    const obs : Observable<Goal[]> = this.http.get<Goal[]>(this.urls.getAllGoals, {});
    return obs;
  }

  public getGoalById(id : string) : Observable<Goal>{
    //console.log('getGoalById', id);
    const obs : Observable<Goal> = this.http.get<Goal>(this.urls.getGoalById + '/' + id, {});
    return obs;
  }

  public addNewGoal(goal : Goal) : Observable<Goal>{
    //console.log("addNewGoal", goal);
    const obs : Observable<Goal> = this.http.post<Goal>(this.urls.addNewGoal, {goal});
    return obs;
  }
}
