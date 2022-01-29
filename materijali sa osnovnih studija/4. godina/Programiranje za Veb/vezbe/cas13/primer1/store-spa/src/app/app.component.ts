import { AfterViewChecked, Component, OnInit } from '@angular/core';
import { Observable, Subscription } from 'rxjs';
import { Product } from './models/product.model';
import { User } from './models/user.model';
import { AuthService } from './services/auth.service';
import { ProductService } from './services/product.service';

declare const $: any;

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit, AfterViewChecked {
  title = 'store-spa';

  user: User | null = null;
  sub: Subscription;

  constructor(private auth: AuthService) { 
    this.sub = this.auth.user.subscribe((user: User | null) => {
      this.user = user;
    })
  }

  ngOnInit(): void {

  }

  ngAfterViewChecked () {
    $('.menu .item').tab();
  }

  onProductCreated(product: Product) {
    // this.productsFromRoot.push(product);
  }
}
