import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { KanbanListComponent } from './components/kanban-list/kanban-list.component';
import { NewKanbanComponent } from './components/new-kanban/new-kanban.component';

const routes: Routes = [
  {path : '', component : KanbanListComponent},
  {path : 'add-a-kanban', component : NewKanbanComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
