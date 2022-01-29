import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { WordsComponentComponent } from './components/words-component/words-component.component';
import { WordInfoWithFormComponent } from './components/word-info-with-form/word-info-with-form.component';
import { WordsByLevelComponentComponent } from './components/words-by-level-component/words-by-level-component.component';

@NgModule({
  declarations: [
    AppComponent,
    WordsComponentComponent,
    WordInfoWithFormComponent,
    WordsByLevelComponentComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    ReactiveFormsModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
