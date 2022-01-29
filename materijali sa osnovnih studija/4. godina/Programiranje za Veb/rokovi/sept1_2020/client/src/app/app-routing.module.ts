import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { MeteoDetailsComponent } from './components/meteo-details/meteo-details.component';
import { MeteoComponent } from './components/meteo/meteo.component';

const routes: Routes = [
{path: "", component: MeteoComponent},
{path: "details/:city", component: MeteoDetailsComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
