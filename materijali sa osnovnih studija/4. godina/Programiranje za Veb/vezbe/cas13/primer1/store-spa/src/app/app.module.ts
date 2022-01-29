import { NgModule } from '@angular/core';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { UserProfileComponent } from './components/user-profile/user-profile.component';
import { ProductListComponent } from './components/product-list/product-list.component';
import { ProductInfoComponent } from './components/product-info/product-info.component';
import { CreateProductComponent } from './components/create-product/create-product.component';
import { LoginFormComponent } from './components/login-form/login-form.component';
import { RegistrationFormComponent } from './components/registration-form/registration-form.component';
import { NavMenuComponent } from './components/nav-menu/nav-menu.component';
import { LogoutComponent } from './components/logout/logout.component';
import { ProductDetailsComponent } from './components/product-details/product-details.component';
import { ProductSumPipe } from './pipes/product-sum.pipe';

@NgModule({
  declarations: [
    AppComponent,
    UserProfileComponent,
    ProductListComponent,
    ProductInfoComponent,
    CreateProductComponent,
    LoginFormComponent,
    RegistrationFormComponent,
    NavMenuComponent,
    LogoutComponent,
    ProductDetailsComponent,
    ProductSumPipe,
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
