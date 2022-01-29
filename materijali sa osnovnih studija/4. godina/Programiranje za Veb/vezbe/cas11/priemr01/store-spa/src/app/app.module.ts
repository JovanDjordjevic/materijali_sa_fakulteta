import { analyzeAndValidateNgModules } from '@angular/compiler';
import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';     // pazi da se doda reactiveForms ovde
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';  // isto za ovaj

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { UserProfileComponent } from './components/user-profile/user-profile.component';
import { ProductListComponent } from './components/product-list/product-list.component';
import { ProductInfoComponent } from './components/product-info/product-info.component';
import { CreateProductComponent } from './components/create-product/create-product.component';

@NgModule({
  declarations: [
    AppComponent,
    UserProfileComponent,
    ProductListComponent,
    ProductInfoComponent,
    CreateProductComponent  // kada generisemo komponentu onako iz CLI alata ovde ce nam se automatski dodati potrebna stvar
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,         
    ReactiveFormsModule,   // dodali ReactiveFormsModule   (potreban nam je i FormsModule iznad)
    HttpClientModule,     // za http zahteve (?)
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
