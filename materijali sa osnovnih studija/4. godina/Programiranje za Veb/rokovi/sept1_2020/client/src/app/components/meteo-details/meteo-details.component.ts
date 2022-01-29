import { THIS_EXPR } from '@angular/compiler/src/output/output_ast';
import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';
import { Meteo } from 'src/app/models/meteo.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-meteo-details',
  templateUrl: './meteo-details.component.html',
  styleUrls: ['./meteo-details.component.css']
})
export class MeteoDetailsComponent implements OnInit, OnDestroy {

  meteo : Meteo;
  sub : Subscription = new Subscription();

  temperatureForm : FormGroup;

  linkError : boolean = false;

  resetButtonEnabled : boolean = false;
  displayedTemperatures : number[] = [];

  updateSuccess : boolean = false;

  constructor(private requestService : RequestService, private formBuilder : FormBuilder,  private activatedRoute : ActivatedRoute) {
    this.meteo = new Meteo("", "", []);

    this.temperatureForm = this.formBuilder.group({
      filter : ['', [Validators.required]],
      num : ['', [Validators.required]]
    });
  }

  ngOnInit(): void {
    this.sub = this.activatedRoute.params.subscribe((data : any) => {
      const city = data.city;
      this.sub = this.requestService.getMeteoForCity(city).subscribe((meteo : Meteo) => {
        if(!meteo) {
          this.linkError = true;
        }
        else {
          this.meteo = meteo;
          this.displayedTemperatures = this.meteo.temperatures;
        }
      });
    });
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onSubmitTemperatureForm(){
    const num = parseInt(this.temperatureForm.value.num);
    if(!this.temperatureForm.valid || !num || num > this.displayedTemperatures.length || num < 0 ) {
      window.alert('Check the values');
      return;
    }

    this.resetButtonEnabled = true;
    
    const formData = this.temperatureForm.value;
    const filterStart = formData.filter;
    switch(filterStart) {
      case 'start':
        this.displayedTemperatures = this.displayedTemperatures.slice(0, num);
        break;
      case 'end':
        this.displayedTemperatures = this.displayedTemperatures.slice(-num);
        break;
      default:
        break
    }

  }

  onClickResetTemperatures(){
    // ne radi lepo, nesto lose radim sa slice iznad
    this.displayedTemperatures = this.meteo.temperatures;
  }

  onClickSaveResults(){
    //console.log(this.displayedTemperatures)
    this.sub = this.requestService.updateTemperaturesForCity(this.meteo.city, this.displayedTemperatures).subscribe((msg : string) => {
      this.updateSuccess = true;
      console.log(msg);
    });
  }
}
