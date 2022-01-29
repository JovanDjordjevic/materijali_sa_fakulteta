import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Payment } from 'src/app/models/payment.model';
import { RequestService } from 'src/app/services/request-service.service';

@Component({
  selector: 'app-amount-list',
  templateUrl: './amount-list.component.html',
  styleUrls: ['./amount-list.component.css']
})
export class AmountListComponent implements OnInit {

  payment : Payment;

  constructor(private requestService : RequestService, private activatedRoute : ActivatedRoute) {
    this.payment = new Payment('', '', '', []);
  }

  ngOnInit(): void {
    this.activatedRoute.params.subscribe((data : any) => {
      let id = data.id;
      this.requestService.getPaymentById(id).subscribe((payment : Payment) => {
        // ovaj ce imati samo _id i amounts
        this.payment = payment;
      });
    });
  }

}
