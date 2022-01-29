import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HeaderComponent } from './components/header/header.component';
import { MeteoComponent } from './components/meteo/meteo.component';
import { MinTempPipe } from './pipes/min-temp.pipe';
import { MaxTempPipe } from './pipes/max-temp.pipe';
import { AvgTempPipe } from './pipes/avg-temp.pipe';
import { MeteoDetailsComponent } from './components/meteo-details/meteo-details.component';

@NgModule({
  declarations: [
    AppComponent,
    HeaderComponent,
    MeteoComponent,
    MinTempPipe,
    MaxTempPipe,
    AvgTempPipe,
    MeteoDetailsComponent,
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
