import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { CreateProductComponent } from './components/create-product/create-product.component';
import { LoginFormComponent } from './components/login-form/login-form.component';
import { LogoutComponent } from './components/logout/logout.component';
import { ProductDetailsComponent } from './components/product-details/product-details.component';
import { ProductListComponent } from './components/product-list/product-list.component';
import { RegistrationFormComponent } from './components/registration-form/registration-form.component';
import { UserProfileComponent } from './components/user-profile/user-profile.component';
import { UserAuthenticatedGuard } from './guards/user-authenticated.guard';

// na pocetku je ovaj niz prazan. To je niz instrukcija koje ce angular korsititi za rutiranje
// kada se kod aplikacije prevede, mi dobijamo index.html i neke dodatne js fajlove
// obicno kada udjemo na neku web stranicu, svaka stranica predstavlja nov get zahtev koji vratis tranicu,
// angular aplikacije su sve single page, tj kao da se na pcoetku posalje jedan veliki get zahtev koji dohvatis ve stranice, a onda se navigacija
// po stranicama simulira rutiranjem
// u routes nizu se nalaze objekti oblika {putanja, komponenta_koja_treba_da_se_prikaze}
// npr recimo da u korenoj putanji hocemo da se prikaze user-prifle (koerna putanja se navodi samo sa '', ako stavimo '/' angular ce se buniti)
// da bi se ovo prikazalo moramo i u htmlu za app component navedemo <router-outlet> tag
const routes: Routes = [
  {path: '', component: ProductListComponent},
  {path: 'register', component: RegistrationFormComponent},
  {path: 'login', component: LoginFormComponent },
  {path: 'logout', component: LogoutComponent},
  // za ovaj konkretno smo implementirali nas guard, i ti guardovi (niz guardova) mogu da se proslede
  // kao dodatni argumenti ovde, konkretno koristimo canActivate jer nas guard implmentira taj interfejs
  // kada se pokusa pritup ovoj adresi, prvo se prolazi kroz sve navedene guardove i samo ako su oni svi zadovoljeni, dopusta se prolaz
  {path: 'user', component: UserProfileComponent, canActivate: [UserAuthenticatedGuard]},           
  {path: 'create-product', component: CreateProductComponent, canActivate: [UserAuthenticatedGuard]},   // slicno i ovde ne zelimo da neko ko nije ulogovan napravi i okaci novi proizvod                                                                      
  // slicno kao u node-u, mozemo da imamo putanje sa parametrima, parametre oznacavmao ovako sa : 
  {path: 'products/:productId', component: ProductDetailsComponent}
];

@NgModule({
  // vidimo da ovaj app-routing module ukljucuje neki RouterModule koji koristi ovaj neki niz routes
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
