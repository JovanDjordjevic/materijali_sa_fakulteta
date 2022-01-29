import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NavigationComponent } from './components/navigation/navigation.component';
import { TalkComponentComponent } from './components/talk-component/talk-component.component';
import { AllTalksComponent } from './components/all-talks/all-talks.component';
import { RegisterTalkComponent } from './components/register-talk/register-talk.component';

@NgModule({
  declarations: [
    AppComponent,
    NavigationComponent,
    TalkComponentComponent,
    AllTalksComponent,
    RegisterTalkComponent
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
