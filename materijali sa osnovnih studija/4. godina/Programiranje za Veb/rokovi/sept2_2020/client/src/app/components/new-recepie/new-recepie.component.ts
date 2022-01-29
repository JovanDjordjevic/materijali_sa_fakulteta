import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { Dessert } from 'src/app/models/dessert.model';
import { RequestService } from 'src/app/services/request.service';

@Component({
  selector: 'app-new-recepie',
  templateUrl: './new-recepie.component.html',
  styleUrls: ['./new-recepie.component.css']
})
export class NewRecepieComponent implements OnInit , OnDestroy{

  recepieForm : FormGroup

  sub : Subscription = new Subscription();

  constructor(private requestService : RequestService, private formBuilder : FormBuilder) {
    this.recepieForm = this.formBuilder.group({
      name : ['', [Validators.required]],
      description : ['',[Validators.required, Validators.maxLength(200)]],
      complexity : ['',[Validators.required]],
      nutrition : ['',[Validators.required]],   //TODO: validator za ceo broj
      glutenFree : ['',[]],
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onRecepieFormSubmit(){
    if(!this.recepieForm.valid){
      window.alert("Form is invalid - please check the inputs!");
      return;
    }

    const formData = this.recepieForm.value;
    const gluten = (formData.glutenFree === "" || !formData.glutenFree ? false : true);

    const newDessert = new Dessert(formData.name, formData.description, formData.complexity, formData.nutrition, gluten);
    this.sub = this.requestService.addNewDessert(newDessert).subscribe((dessert : Dessert) => {
      console.log(dessert);
      window.alert("Recepie is successfuly added!");
    });
  }
}
