import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AmountListComponent } from './components/amount-list/amount-list.component';
import { HomePageComponent } from './components/home-page/home-page.component';

const routes: Routes = [
  {path : "" , component : HomePageComponent},
  {path : "payment/:id" , component : AmountListComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
