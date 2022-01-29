import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { EventsComponent } from './components/events-component/events-component.component';
import { EventComponent } from './components/event-component/event-component.component';
import { ToDoComponentComponent } from './components/to-do-component/to-do-component.component';

@NgModule({
  declarations: [
    AppComponent,
    EventsComponent,
    EventComponent,
    ToDoComponentComponent
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
