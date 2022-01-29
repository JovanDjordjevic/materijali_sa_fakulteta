import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { GoalFormComponent } from './components/goal-form/goal-form.component';
import { GoalListComponent } from './components/goal-list/goal-list.component';

const routes: Routes = [
  {path: '', component: GoalListComponent},
  {path: 'add-goal', component: GoalFormComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
