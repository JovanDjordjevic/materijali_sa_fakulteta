import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Area, Talk } from 'src/app/models/talk.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-all-talks',
  templateUrl: './all-talks.component.html',
  styleUrls: ['./all-talks.component.css']
})
export class AllTalksComponent implements OnInit, OnDestroy {

  allTalks : Talk[] = [];
  filteredTalks : Talk[] = [];
  sub : Subscription = new Subscription();
  AreaEnum = Area;

  constructor(private requestService : RequestService) { }

  ngOnInit(): void {
    this.sub = this.requestService.getAllTalks().subscribe((talks : Talk[]) => {
      this.allTalks = talks;
      // ovo sortiranje moze da se radi i na serverskoj strani
      this.allTalks.sort((a : Talk, b : Talk) => {return a.duration - b.duration});
      this.filteredTalks = this.allTalks;
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onAreaSelected(){
    const selectElement = document.getElementById('areaSelector');
    const selecorValue = (selectElement as HTMLSelectElement).value;
    //console.log(selecorValue);
    if(selecorValue === 'All') {
      this.filteredTalks = this.allTalks;
    }
    else {
      this.sub = this.requestService.getAllTalksInArea(selecorValue).subscribe((talks : Talk[]) => {
        this.filteredTalks = talks;
      });
    }
  }
}
