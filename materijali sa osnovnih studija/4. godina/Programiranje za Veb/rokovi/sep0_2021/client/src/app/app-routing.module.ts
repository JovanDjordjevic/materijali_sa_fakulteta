import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { EventComponent } from './components/event-component/event-component.component';
import { EventsComponent } from './components/events-component/events-component.component';

const routes: Routes = [
  {path: "", component: EventsComponent},
  {path: "event/:id", component: EventComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
