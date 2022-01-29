import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivate, Router, RouterStateSnapshot, UrlTree } from '@angular/router';
import { Observable } from 'rxjs';
import { AuthService } from '../services/auth.service';

// vidimo da je guard u sustini kao neki servis, ima dekorator Injectable
// guard koji napisemo cemo da iskoristimo u app-routing.module (?)

@Injectable({
  providedIn: 'root'
})

// implementira CanActivate interfejs
export class UserAuthenticatedGuard implements CanActivate {

  constructor(private auth : AuthService, private router : Router){}

  // metod iz interfejsa mora da primi router i state, oni nam govore neke informacije o url putanju
  // moze da vrati vise razlicitih stvari, za nas je bitan ovaj boolean, tj vraticem true ako zahtev zadovoljava neki nas kriterijum, false u suprotnom
  // mozed a vrati u UrlTree, to je drvo rutiranja koje moze da se formira na osnovu.. (?) 
  canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree {

      if(this.auth.isLoggedIn) {
        return true;
      } else {
        // ako korisnik nije ulogovan hocemod a ga preusmerimo na neku putanju, za to korsitimo
        // ovaj createUrlTree iz Router servisa kome prosledjujemo niz putanja (mi imamo samo jednu ovu za login)
        return this.router.createUrlTree(['/login']);
      }

    return true;
  }
  
}
