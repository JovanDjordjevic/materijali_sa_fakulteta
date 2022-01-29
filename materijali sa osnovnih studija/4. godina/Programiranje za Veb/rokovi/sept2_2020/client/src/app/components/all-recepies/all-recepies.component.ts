import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Dessert } from 'src/app/models/dessert.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-all-recepies',
  templateUrl: './all-recepies.component.html',
  styleUrls: ['./all-recepies.component.css']
})
export class AllRecepiesComponent implements OnInit, OnDestroy {

  allRecepies : Dessert[] = [];
  sub : Subscription = new Subscription();

  displayDetails : boolean = false;
  currentRecepie : Dessert;

  constructor(private requestService : RequestService) { 
    this.currentRecepie = new Dessert('', '', '', 0, false);
  }

  ngOnInit(): void {
    this.sub = this.requestService.getAllDesserts().subscribe((desserts : Dessert[]) => {
      this.allRecepies = desserts;
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  showDetailsAndSetCurrentRecepie(recepie : Dessert){
    this.displayDetails = true;
    this.currentRecepie = recepie;
  }

  hideDetails(){
    this.displayDetails = false;
  }
}
