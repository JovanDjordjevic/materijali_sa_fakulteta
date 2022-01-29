import { Component, OnDestroy, OnInit } from '@angular/core';
import { Subscription } from 'rxjs';
import { Meteo } from 'src/app/models/meteo.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-meteo',
  templateUrl: './meteo.component.html',
  styleUrls: ['./meteo.component.css']
})
export class MeteoComponent implements OnInit, OnDestroy {

  allMeteo : Meteo[] = [];
  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService) { }

  ngOnInit(): void {
    this.sub = this.requestService.gelAllMeteo().subscribe((meteos : Meteo[]) => {
      this.allMeteo = meteos;
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

}
