import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NewRecepieComponent } from './components/new-recepie/new-recepie.component';
import { AllRecepiesComponent } from './components/all-recepies/all-recepies.component';
import { DetailsComponent } from './components/details/details.component';
import { SpecialRecepiesComponent } from './components/special-recepies/special-recepies.component';

@NgModule({
  declarations: [
    AppComponent,
    NewRecepieComponent,
    AllRecepiesComponent,
    DetailsComponent,
    SpecialRecepiesComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    ReactiveFormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
