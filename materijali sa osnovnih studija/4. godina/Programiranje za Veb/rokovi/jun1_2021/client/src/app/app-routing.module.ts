import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AllTalksComponent } from './components/all-talks/all-talks.component';
import { RegisterTalkComponent } from './components/register-talk/register-talk.component';

const routes: Routes = [
  {path : '', component : AllTalksComponent},
  {path : 'register', component : RegisterTalkComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
