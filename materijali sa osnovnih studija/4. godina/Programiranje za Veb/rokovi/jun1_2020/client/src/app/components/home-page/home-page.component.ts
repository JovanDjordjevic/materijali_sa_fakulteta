import { Component, OnDestroy, OnInit } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { Subscription } from 'rxjs';
import { Payment } from 'src/app/models/payment.model';
import { RequestService } from 'src/app/services/request-service.service';

@Component({
  selector: 'app-home-page',
  templateUrl: './home-page.component.html',
  styleUrls: ['./home-page.component.css']
})
export class HomePageComponent implements OnInit, OnDestroy {
  payment : Payment;
  emailForm : FormGroup;
  amountForm : FormGroup;
  sub : Subscription = new Subscription();
  emailError : boolean = false;
  requestSuccessful : boolean = false;

  constructor(private formBuilder : FormBuilder,  private requestService : RequestService) {
    this.payment = new Payment("", "", "", []);

    this.emailForm = formBuilder.group({
      email : ['', [Validators.required, Validators.email]]
    });

    this.amountForm = formBuilder.group({
      id : ['', [Validators.required]],
      amount : ['', [Validators.required, Validators.min(1000)]]
    });
  }

  ngOnInit(): void {
  }

  ngOnDestroy(): void {
      this.sub.unsubscribe();
  }

  onEmailFormSubmit(){
    if(this.emailForm.invalid){
      window.alert('Email polje mora imati validnu unetu vrednost');
      return;
    }

    const email = this.emailForm.value.email;
    this.sub = this.requestService.getPaymentByEmail(email).subscribe((payment : Payment) => {
      if(payment == null) {
        this.emailError = true;
      }
      else {
        this.emailError = false;
        this.requestSuccessful = true;
        this.payment = payment;
        this.amountForm.setValue({'id': this.payment._id, amount: ''});
      }
    });
  }

  onAmountFormSubmit() {
    if(!this.amountForm.valid){
      window.alert('Formular nije validan! Ispravite podatke!');
      return;
    }

    const formData = this.amountForm.value;
    this.sub = this.requestService.addAmount(formData.id, formData.amount).subscribe((payment : Payment) => {
      //console.log(payment.amounts)
      window.alert('Uspesno dodat iznos');
    });
  }
}