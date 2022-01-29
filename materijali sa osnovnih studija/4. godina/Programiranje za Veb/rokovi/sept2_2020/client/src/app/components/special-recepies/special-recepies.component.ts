import { Component, OnDestroy, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';
import { Dessert } from 'src/app/models/dessert.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-special-recepies',
  templateUrl: './special-recepies.component.html',
  styleUrls: ['./special-recepies.component.css']
})
export class SpecialRecepiesComponent implements OnInit, OnDestroy {

  specialRecepies : Dessert[] = [];
  criterion : string = "";
  linkError : boolean = false;
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService, private activatedRoute : ActivatedRoute) { }

  ngOnInit(): void {
    this.sub = this.activatedRoute.params.subscribe((data : any) => {
      this.criterion = data.criterion;
      if(this.criterion != 'glutenfree' && this.criterion != 'lowcalorie') {
        this.linkError = true;
      }
      else {
        this.sub = this.requestService.getDessertsWithCriterion(this.criterion).subscribe((desserts : Dessert[]) => {
          this.specialRecepies = desserts;
          console.log(desserts)
        });
      }
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}
