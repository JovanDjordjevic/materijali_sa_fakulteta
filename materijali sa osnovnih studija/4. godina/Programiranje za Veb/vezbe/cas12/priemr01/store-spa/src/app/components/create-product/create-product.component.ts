import { Component, ElementRef, EventEmitter, OnInit, Output, ViewChild } from '@angular/core'; 
import { FormBuilder, FormGroup, ValidationErrors, Validators } from '@angular/forms';
import { Product } from 'src/app/models/product.model';
import { ProductState } from 'src/app/models/product-state.model';
import { ProductNameValidator } from 'src/app/validators/product-name.validator';  // ne zaboravimo da ukljucimo nas validator

// radimo slicno formular kao user-profile

declare const $: any;

@Component({
  selector: 'app-create-product',
  templateUrl: './create-product.component.html',
  styleUrls: ['./create-product.component.css']
})
export class CreateProductComponent implements OnInit {

  // ovo nam vise ne treba jer cemo da radimo sve na novi lepsi nacin sa formularima
    // @ViewChild('inputName', {static:true}) inputName: ElementRef  = {} as ElementRef; 
    // @ViewChild('inputPrice', {static:true}) inputPrice: ElementRef  = {} as ElementRef;
    // @ViewChild('inputDescription', {static:true}) inputDescription: ElementRef  = {} as ElementRef;
    // @ViewChild('inputForSale', {static:true}) inputForSale: ElementRef  = {} as ElementRef;

  @Output() productCreated: EventEmitter<Product> = new EventEmitter<Product>();

  // visi u user-profiles detaljnija objasnjenja
  createProductForm: FormGroup;

  // onaj novi enum koji smo dodali za radio dugmice
  // ne zaboravimo da ga ovako dodelimo nekom lokalnom 
  ProductStateEnum = ProductState;

  // pokazacemo ovde onaj drugi nacin tako sto se koristi FormBuilder 
  constructor(private formBuilder: FormBuilder) {
    // konstruisemo objekat koji odgovara formularu
    this.createProductForm = this.formBuilder.group({
      // dodali smo nas custom validator za ime, vidi u fodleru validators
      name: ['', [Validators.required, Validators.minLength(10), ProductNameValidator]],
      price: [1, [Validators.required, Validators.min(1)]],
      description: ['', [Validators.required, Validators.maxLength(200)]],
      forSale: [false, [Validators.required]],
      state: [null, [Validators.required]],      
    });
  }

  ngOnInit(): void {
    $('.ui.checkbox').checkbox();
    // i za radio dugmice smo morali da nadjemo ovaj jquery kod 
    $('.ui.radio.checkbox').checkbox();
  }

  addNewProduct(){
    // ovo nam vise ne treba jer cemo da radimo sve na novi lepsi nacin sa formularima
      // const name: string = (this.inputName.nativeElement as HTMLInputElement).value;
      // const price: number = Number.parseFloat((this.inputPrice.nativeElement as HTMLInputElement).value);
      // const description: string = (this.inputDescription.nativeElement as HTMLInputElement).value;
      // const forSale: boolean = (this.inputForSale.nativeElement as HTMLInputElement).checked;   

      // if (name === '' || Number.isNaN(price) || description==='') {
      //   window.alert("Some required fields are missing");
      //   return;
      // }

    
    
    // const newProduct: Product = new Product(name, description, price, forSale, 'assets/default-product.png', 'Pera Peric', 90);

    //this.productCreated.emit(newProduct);
  }

  onCreateProductFormSubmit(){

  }

  nameHasErrors(): boolean{
    // FormGroup ima metod get kome prosledjujemo FormControl ime elementa koji nam je relevantan (za nas ce ovde to biti name)
    // get ce nam vratiti neki objekat koji izmedju ostalog ima i polje errors koji sadrzi validacione greske
    // ovaj ? sluzimo za dohvatanje polja koja mozda ne postoje (?). Nas validator vraca null ako je je sve proslo kako treba
    // tj objekat koji vrati get nece imati polje errors (?)
    const errors : ValidationErrors | undefined | null = this.createProductForm.get("name")?.errors;

    return errors !== null;
  }

  // ako imamo samo ovaj metod nameHasErrors, on ce da zacrveni polje kako treba, ali korisnik nece imati nikakvu informaciju o gresci, 
  // zato implementiramo ovo sto ce da nam vrati niz stringova greska koje su se desile
  nameErrors() : string[] {
    const errors : ValidationErrors | undefined | null = this.createProductForm.get("name")?.errors;

    if (errors === null || errors === undefined) {
      return [];
    }

    const errorMsgs: string[] = [];

    // nece svaki poratni tip iz validatora imati ista polja tako da moramo da ispitamo za sve sto nas zanima da li ta polja postoje
    // neki nemaju ni poruku o tome sta se desilo, npr ovaj required nema poruku pa pisemo mi nasu
    if(errors['required']) {
      errorMsgs.push('Product must have a name');
    }

    if(errors['minLength']) {
      errorMsgs.push('Product name too short');
    }

    if(errors['productName']) {
      errorMsgs.push('Error with product name');
    }

    return errorMsgs;
  }

}
