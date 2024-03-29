import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AllRecepiesComponent } from './components/all-recepies/all-recepies.component';
import { NewRecepieComponent } from './components/new-recepie/new-recepie.component';
import { SpecialRecepiesComponent } from './components/special-recepies/special-recepies.component';

const routes: Routes = [
  {path : '', component : NewRecepieComponent},
  {path : 'all', component : AllRecepiesComponent},
  {path : 'criterion/:criterion', component : SpecialRecepiesComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
