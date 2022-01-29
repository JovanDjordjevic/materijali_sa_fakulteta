import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule} from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { KanbanListComponent } from './components/kanban-list/kanban-list.component';
import { NewKanbanComponent } from './components/new-kanban/new-kanban.component';
import { KanbanComponent } from './components/kanban/kanban.component';

@NgModule({
  declarations: [
    AppComponent,
    KanbanListComponent,
    NewKanbanComponent,
    KanbanComponent
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
